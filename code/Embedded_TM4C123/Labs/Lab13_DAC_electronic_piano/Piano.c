// Piano.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// There are four keys in the piano
// Daniel Valvano
// December 29, 2014

// Port E bits 3-0 have 4 piano keys

#include "Piano.h"
#include "..//tm4c123gh6pm.h"
#include "DAC.h"
#include "Sound.h"


void PortE_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000010;     // 1) F clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTE_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTE_CR_R = 0x0F;           // allow changes to PF3-0       
  GPIO_PORTE_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTE_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTE_DIR_R |= 0xF0;          // 5)  PE3,PE2,PE1, PE0 output    0000 1111
  GPIO_PORTE_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTE_PUR_R = 0x00;          // enable pullup resistors on PF4,PF0       
  GPIO_PORTE_DEN_R = 0x0F;          // 7) enable digital pins PF4-PF0        
}

// **************Piano_Init*********************
// Initialize piano key inputs
// Input: none
// Output: none
void Piano_Init(void){ 
  PortE_Init();
}
// **************Piano_In*********************
// Input from piano key inputs
// Input: none 
// Output: 0 to 15 depending on keys
// 0x01 is key 0 pressed, 0x02 is key 1 pressed,
// 0x04 is key 2 pressed, 0x08 is key 3 pressed
unsigned long Piano_In(void){
	
	//Piano key 3: G generates a sinusoidal DACOUT at 783.991 Hz -> 102042 ticks (1 tick = 12.5 ns): 80Mz/783.991Hz -> 102042
	//Piano key 2: E generates a sinusoidal DACOUT at 659.255 Hz -> 121349 ticks (1 tick = 12.5 ns)
	//Piano key 1: D generates a sinusoidal DACOUT at 587.330 Hz -> 136209 ticks (1 tick = 12.5 ns)
	//Piano key 0: C generates a sinusoidal DACOUT at 523.251 Hz -> 1911128 ticks
	unsigned long period = 0;
	unsigned int divider = 32; //or 16;

	//Depending on the input we output a syskey
	switch(GPIO_PORTE_DATA_R)
	{
		case 1:
 //Piano key 0: C generates a sinusoidal DACOUT at 523.251 Hz -> 1911128 ticks  152890
 //if for 523-> 519... then 523*152890/16/519 = 
		  period =   150300/divider; //152890/16; // 152963/16;
		  Sound_Tone(period);
		  break;
		case 2:
 //Piano key 1: D generates a sinusoidal DACOUT at 587.330 Hz -> 136209 ticks (1 tick = 12.5 ns)
		//reail case got:
			period =   134709/divider; //136209/16;
			Sound_Tone(period);
			break;
		case 4:
 //Piano key 2: E generates a sinusoidal DACOUT at 659.255 Hz -> 121349 ticks (1 tick = 12.5 ns)
		//real case got:
			period =   120100/divider; //121349/16;
	   	Sound_Tone(period);
		  break;
		case 8:
 //Piano key 3: G generates a sinusoidal DACOUT at 783.991 Hz -> 102042 ticks (1 tick = 12.5 ns)
		//real case got:
			period =   100700/divider; //102042/16; //102171/16;
		  Sound_Tone(period);
			break;
		case 0:
			period = 0; //special value
		  Sound_Off();
		  break;
		default:
			period = 0; // special value
		  Sound_Off();
			break;
	}
  
  return period; // remove this, replace with input
}
