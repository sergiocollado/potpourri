// Sound.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Use the SysTick timer to request interrupts at a particular period.
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// This routine calls the 4-bit DAC

#include "Sound.h"
#include "DAC.h"
#include "..//tm4c123gh6pm.h"

const unsigned char SineWave[16] = {4,5,6,7,7,7,6,5,4,3,2,1,1,1,2,3};
const unsigned char SineWave32[32] = {8,9,11,12,13,14,14,15,15,15,14,14,13,12,11,9,8,7,5,4,3,2,2,1,1,1,2,2,3,4,5,7};

unsigned char Index=0;           // Index varies from 0 to 15
unsigned long period = 0;			
unsigned char output = 0;	
unsigned long init_period = 5000;	
	
// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Also calls DAC_Init() to initialize DAC
// Input: none
// Output: none
void Sound_Init(void){
  
	Index = 0;
  DAC_Init();          // Port B is DAC 
	output = 0;
	
	NVIC_ST_CTRL_R = 0;         // disable SysTick during setup
  NVIC_ST_RELOAD_R = init_period-1;// reload value
  NVIC_ST_CURRENT_R = 0;      // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x20000000; 
  // priority 
  NVIC_ST_CTRL_R = 0x0007; // enable,core clock, and interrupts
}

// **************Sound_Tone*********************
// Change Systick periodic interrupts to start sound output
// Input: interrupt period
//           Units of period are 12.5ns
//           Maximum is 2^24-1
//           Minimum is determined by length of ISR
// Output: none
void Sound_Tone(unsigned long data){
// this routine sets the RELOAD and starts SysTick
	period = data;
	//sets the reload and starts Systick
	/*
	NVIC_ST_CTRL_R = 0;         // disable SysTick during setup
	Index=0;										// reset sine wave
	NVIC_ST_RELOAD_R = period-1;// reload value
	NVIC_ST_CURRENT_R = 0;      //to force SysTick to restart the countdown from RELOAD value.
	NVIC_ST_CTRL_R = 0x0007; // enable,core clock, and interrupts
	*/
}


// **************Sound_Off*********************
// stop outputing to DAC
// Output: none
void Sound_Off(void){
 // this routine stops the sound output	
	DAC_Out(0);
	Index = 0;
	output = 0;
	//NVIC_ST_CTRL_R = 0;         // disable SysTick during setup
}


// Interrupt service routine
// Executed every 12.5ns*(period)
void SysTick_Handler(void){
	
	if (period !=0 ) // this case is only 
	{
		Index = (Index+1)& 0x1F;      // 4,5,6,7,7,7,6,5,4,3,2,1,1,1,2,3... 
		DAC_Out(SineWave32[Index]);  // output one value each interrupt  
	
		NVIC_ST_CTRL_R = 0;         // disable SysTick during setup
		NVIC_ST_RELOAD_R = period-1;// reload value
		NVIC_ST_CURRENT_R = 0;      // any write to current clears it
		NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000;           
		NVIC_ST_CTRL_R = 0x07; // enable SysTick with core clock and interrupts
		// finish all initializations and then enable interrupts
 	}
	else
	{
		Index = 0;
		DAC_Out(0);
	}
	
}
