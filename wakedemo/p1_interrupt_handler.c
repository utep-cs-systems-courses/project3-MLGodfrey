#include <msp430.h>
#include "switches.h"

void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) { //is a button causing an interrupt
    P2IFG &= ~SWITCHES;   //clears pending interrupts   
    switch_interrupt_handler();//handles all switches
  }
}
