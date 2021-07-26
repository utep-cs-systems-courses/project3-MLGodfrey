#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

char interruptTime;
char button_four;

void blink_button_advance(){
 
  if(switch_state_down_1){ //full bright and high buzz
    interruptTime=0;
    turn_on_red();
    buzzer_set_period(2551);
  }
  else if(switch_state_down_2){ //half dim and mid buzz
    interruptTime=2;
    turn_on_red();
    buzzer_set_period(3214);
  }
  else if(switch_state_down_3){ //full dim and low buzz
    interruptTime=0;
    turn_on_red();
    turn_off_red();
    buzzer_set_period(3822);
  }
  else if(switch_state_down_4){ // count to 3

    button_four = 1;
    interruptTime = 250;
    buzzer_set_period(0);
    static char state = 0;
    switch(state){
    case 0: buzzer_set_period(3822); red_on=0; green_on=0; state++; break; //count 0
    case 1: buzzer_set_period(2551); red_on=0; green_on=1; state++; break; //count 1
    case 2: buzzer_set_period(3822); red_on=1; green_on=0; state++; break; //count 2
    case 3: buzzer_set_period(2551); red_on=1; green_on=1; state=0; break; //count 3
    default: state = 0; //redundantly ensures state resets to 0
    }
    led_changed=1;
    led_update();
  } else { // makes sure that board goes quiet once no buttons are pressed
    button_four=0;
    turn_off_red();
    turn_off_green();
    buzzer_set_period(0);
  }
}
  


void turn_on_red(){ //quick way to turn on/off red/green
  red_on=1;
  led_changed = 1;
  led_update();
}

void turn_off_red(){
  red_on=0;
  led_changed=1;
  led_update();
}
void turn_on_green(){
  green_on=1;
  led_changed = 1;
  led_update();
}
void turn_off_green(){
  green_on=0;
  led_changed=1;
  led_update();
}
