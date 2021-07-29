#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"
#include "switches.h"
#include "led.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

#define LED BIT6		/* note that bit zero req'd for display */



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

    
