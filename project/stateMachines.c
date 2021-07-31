#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "../lcdLib/lcdutils.h"
#include "../lcdLib/lcddraw.h"

char interruptTime;
char button_four;

void state_advance(){

  my_shape(COLOR_BLUE);
  // Turn on Normal light

  if(state==1){
    buzzer_set_period(3822);
    my_color=COLOR_RED;
   }
  
  // Turn on half DIM light
  else if(state==2){
    buzzer_set_period(3214);
    my_color=COLOR_YELLOW;
   }
  
  // Turn on Full DIM light
  else if (state==3){
    buzzer_set_period(2551);
    my_color=COLOR_BLACK;
}
  
  else if (state==4){
    buzzer_set_period(2551);
    my_color=COLOR_BROWN; //this is actually pink?
}
  buzzer_set_period(0);
 
}

// Helper functions unused for this project
void turn_on_red(){ 
  red_on=1;
  led_changed = 1;
  led_update();
}
void turn_on_green(){ 
  green_on=1;
  led_changed = 1;
  led_update();
}
void turn_off_red(){
  red_on=0;
  led_changed=1;
  led_update();
}
void turn_off_green(){
  green_on=0;
  led_changed=1;
  led_update();
}
