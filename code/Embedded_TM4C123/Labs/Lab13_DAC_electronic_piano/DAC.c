// DAC.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Implementation of the 4-bit digital to analog converter
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// Port B bits 3-0 have the 4-bit DAC

#include "DAC.h"
#include "..//tm4c123gh6pm.h"
#include <stdio.h>

// **************DAC_Init*********************
// Initialize 4-bit DAC 
// Input: none
// Output: none
void DAC_Init(void){
//here the code to initialize the DAC
	unsigned long volatile delay;
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB; // activate port B
  delay = SYSCTL_RCGC2_R;    // allow time to finish activating
  GPIO_PORTB_AMSEL_R &= ~0x1F;      // no analog
  GPIO_PORTB_PCTL_R &= ~0x000FFFFF; // regular GPIO function
  GPIO_PORTB_DIR_R |= 0x1F;      // make PB5-0 out
  GPIO_PORTB_AFSEL_R &= ~0x1F;   // disable alt funct on PB5-0 
  GPIO_PORTB_DEN_R |= 0x1F;      // enable digital I/O on PB5-0
	GPIO_PORTB_DR8R_R  |= 0x1F;      // enable on PB5-0
}


// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
void DAC_Out(unsigned long data){
		 GPIO_PORTB_DATA_R = data;
}
