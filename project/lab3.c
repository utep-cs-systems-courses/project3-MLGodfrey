#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"
#include "switches.h"
#include "led.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

#define LED BIT6		/* note that bit zero req'd for display */


<<<<<<< HEAD
=======
#define SWITCHES 15

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
   /*update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  }

int switches = 0;

void
switch_interrupt_handler()
{
   char p2val = switch_update_interrupt_sense();
   switches = ~p2val & SWITCHES;
  }


 axis zero for col, axis 1 for row
short drawPos[2] = {10,10}, controlPos[2] = {10,10};
short velocity[2] = {3,8}, limits[2] = {screenWidth-36, screenHeight-8};
>>>>>>> 6a331d21cdf9546bc3b519a8a609c7a691458550

short redrawScreen = 1;
u_int controlFontColor = COLOR_GREEN;

char state1 = 1;

void wdt_c_handler() //controls the speed at which the image is drawn
{
  static int secCount = 0;
  secCount ++;
  if (secCount == 2) {		/* 10/sec @ 25  */
    secCount = 0;
    redrawScreen = 1;
    switch(state1){
    case 1: move_shape_Left(15); state1++; break;
    case 2: move_shape_Down(15); state1++; break;
    case 3: move_shape_Right(15); state1++; break;
    case 4: move_shape_Up(15); state1++; break;
    default: state1 = 1; break;
    }
  }
}


void main(){
  
  configureClocks();
  lcd_init();
  switch_init();
  buzzer_init();
 

  enableWDTInterrupts();      /**< enable periodic interrupt */
  //  or_sr(0x8);	              /**< GIE (enable interrupts) */

  P1DIR |= LED;
  P1OUT |= LED;
  
  //clearScreen(COLOR_GREEN);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      and_sr(~8);  //Disables interrupts
      clearScreen(COLOR_GREEN);
      my_shape(COLOR_BLUE);
      or_sr(8);
    }
  P1OUT &= ~LED;	/* led off */
  or_sr(0x10);	/**< CPU OFF */
  P1OUT |= LED;	/* led on */
  }
}

    
