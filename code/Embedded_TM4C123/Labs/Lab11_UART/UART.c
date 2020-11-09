// UART.c
// Runs on TM4C123 or LM4F120
// Lab 11 involves switching this from UART1 to UART0.
//                 switching from PC5,PC4 to PA1,PA0
// Daniel Valvano
// December 29, 2014

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2014

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// this connection occurs in the USB debugging cable
// U0Rx (PA0) connected to serial port on PC
// U0Tx (PA1) connected to serial port on PC
// Ground connected ground in the USB cable

#include "tm4c123gh6pm.h"
#include "UART.h"
#include "ctype.h" //to use the isalnum fun
 
//------------UART_Init------------
// Initialize the UART for 115200 baud rate (assuming 80 MHz UART clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART_Init(void){
// as part of Lab 11, modify this program to use UART0 instead of UART1
//                 switching from PC5,PC4 to PA1,PA0
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0; // activate UART0
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // activate port A
	
//	The UART0_CTL_R control register contains the bits that turn on the UART.
//	TXE is the Transmitter Enable bit, and RXE is the Receiver Enable bit.
//	We set TXE, RXE, and UARTEN equal to 1 in order to activate the UART device.
//	However, we should clear UARTEN during the initialization sequence.
  UART0_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
	
//  The IBRD and FBRD registers specify the baud rate.
  UART0_IBRD_R = 43;                    // IBRD = int(80,000,000 / (16 * 115200)) = int(43.402778)
  UART0_FBRD_R = 26;                    // FBRD = round(0.402778 * 64) = 26
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
	
//  The three registers LCRH, IBRD, and FBRD form an internal 30-bit register.
//	This internal register is only updated when a write operation to LCRH is performed,
//	so any changes to the baud-rate divisor must be followed by a write to 
//  the LCRH register for the changes to take effect. Out of reset, both FIFOs
//	are disabled and act as 1-byte-deep holding registers. The FIFOs are 
//  enabled by setting the FEN bit in LCRH.	
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
	
  UART0_CTL_R |= UART_CTL_UARTEN;       // enable UART
	
  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1,PA0
  GPIO_PORTA_DEN_R |= 0x03;             // enable digital I/O on PA1,PA0
                                        // configure PA1,PA0 as UART0
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTA_AMSEL_R &= ~0x03;          // disable analog functionality on PA1,PA0
}

//------------UART_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
unsigned char UART_InChar(void){
// as part of Lab 11, modify this program to use UART0 instead of UART1 (DONE)
  while((UART0_FR_R&UART_FR_RXFE) != 0);
	
	// The Receive FIFO empty flag, RXFE, 
	// RXFE, is clear when new input data are in the receive FIFO.
	// When the FIFO becomes empty, the RXFE flag will be set,(set to value 1...)
	
	
	// The transmit data register is UART0_DR_R
	// bits are transmited in order: b0 b1 b2 b3 b4 b5 b6 b7 
	// b0 is LSB
	// b7 is MSB
	// The transmission software can write to its data register if its TXFF (transmit FIFO full) flag is zero.
  // TXFF equal to zero means the FIFO is not full and has room. 
	// The receiving software can read from its data register if its RXFE (receive FIFO empty) flag is zero.
  // RXFE equal to zero means the FIFO is not empty and has some data. 
  return((unsigned char)(UART0_DR_R&0xFF));
}

//------------UART_InCharNonBlocking------------
// Get oldest serial port input and return immediately
// if there is no data.
// Input: none
// Output: ASCII code for key typed or 0 if no character
unsigned char UART_InCharNonBlocking(void){
// as part of Lab 11, modify this program to use UART0 instead of UART1
	
	//The status of the two FIFOs (Rx and Tx) can be seen in the UART0_FR_R register.
	
	// The Receive FIFO empty flag, RXFE, 
	// RXFE, is clear when new input data are in the receive FIFO.
	// When the FIFO becomes empty, the RXFE flag will be set,(set to value 1...)
	// There is a Receive FIFO full flag RXFF,
	// which is set when the FIFO is full. 
  if((UART0_FR_R&UART_FR_RXFE) == 0){
    return((unsigned char)(UART0_DR_R&0xFF));
  } else{
    return 0;
  }
}

//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART_OutChar(unsigned char data){
// as part of Lab 11, modify this program to use UART0 instead of UART1 [ITS DONE]
	
	// The transmission software can write to its data register if its TXFF (transmit FIFO full) flag is zero.
  // TXFF equal to zero means the FIFO is not full and has room. 

  while((UART0_FR_R&UART_FR_TXFF) != 0);
  UART0_DR_R = data;
}

//------------UART_InUDec------------
// InUDec accepts ASCII input in unsigned decimal format
//     and converts to a 32-bit unsigned number
//     valid range is 0 to 4294967295 (2^32-1)
// Input: none
// Output: 32-bit unsigned number
// If you enter a number above 4294967295, it will return an incorrect value
// Backspace will remove last digit typed
unsigned long UART_InUDec(void){
	unsigned long number=0, length=0;
	char character;
  character = UART_InChar(); //gets char from the UART
  while(character != CR){ // accepts until <enter> is typed
		// The next line checks that the input is a digit, 0-9.
		// If the character is not 0-9, it is ignored and not echoed
    if((character>='0') && (character<='9')) {
      number = 10*number+(character-'0');   // this line overflows if above 4294967295
      length++;
      UART_OutChar(character); //outputs character
    }
		// If the input is a backspace, then the return number is
		// changed and a backspace is outputted to the screen
    else if((character==BS) && length){
      number /= 10;
      length--;
      UART_OutChar(character);
    }
    character = UART_InChar();
  }
  return number;
}

//------------UART_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void UART_OutString(unsigned char buffer[]){
// as part of Lab 11 implement this function
 unsigned int i = 0; //counter,
	
 while( buffer[i] != '\0' )
 {
	 UART_OutChar(buffer[i]);
	 i++;
 }
}

unsigned char String[10];
//-----------------------UART_ConvertUDec-----------------------
// Converts a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: store the conversion in global variable String[10]
// Fixed format 4 digits, one space after, null termination
// Examples
//    4 to "   4 "  
//   31 to "  31 " 
//  102 to " 102 " 
// 2210 to "2210 "
//10000 to "**** "  any value larger than 9999 converted to "**** "
void UART_ConvertUDec(unsigned long n){
// as part of Lab 11 implement this function
	unsigned int counter = 1000, resto =0;
	unsigned int i = 0; //for-loop counter.-
	
	//the output string will be String[10]
	//intilalization to all zeroes.
	// zeroes indicator flag
	unsigned int ind_zeros = 0; //if == 0 , then outputs spaces

	if( n > 9999 ) 
	{
		String[0] = String [1] = String [2] = String [3] = '*';
		String [4] = ' ';		String [5] = '\0';
	}
	else if( n==0)
	{
		String[0] = String [1] = String [2] = ' ';
		String [3] = '0';
		String [4] = ' ';		String [5] = '\0';
	}
	else {
		String[0] = String [1] = String [2] = String [3] = ' ';
		String [4] = ' ';		String [5] = '\0';
		for (i=0; i<4; i++)
		{
				resto = n/counter;
				String[i] = resto + 48; //ascii(48) = is character zero, ...
				if (resto != 0) ind_zeros=1; //from now onwards, the zeroes will be printed.
				if (resto == 0 &&  ind_zeros==0)
				{
					String[i] = ' ';
					if (i==3)  String[3] = '0';
				}
				n = n - resto*counter;
				counter/=10;
				
		}
  }
}

//-----------------------UART_OutUDec-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// Fixed format 4 digits, one space after, null termination
void UART_OutUDec(unsigned long n){
  UART_ConvertUDec(n);     // convert using your function
  UART_OutString(String);  // output using your function
}

//-----------------------UART_ConvertDistance-----------------------
// Converts a 32-bit distance into an ASCII string
// Input: 32-bit number to be converted (resolution 0.001cm)
// Output: store the conversion in global variable String[10]
// Fixed format 1 digit, point, 3 digits, space, units, null termination
// Examples
//    4 to "0.004 cm"  
//   31 to "0.031 cm" 
//  102 to "0.102 cm" 
// 2210 to "2.210 cm"
//10000 to "*.*** cm"  any value larger than 9999 converted to "*.*** cm"
void UART_ConvertDistance(unsigned long n){
// as part of Lab 11 implement this function
  unsigned int i = 0, resto =0, counter = 1000;
	
	if( n > 9999 ) 
	{
		//force the string "*.*** "
		String[0] = String[2] = String[3] = String[4] = '*';
		String [1] = '.';
		String [5] = ' ';
		String [6] = 'c';
		String [7] = 'm';
		String [8] = '\0';
	}
	else {
		
		String[0] = String[1] = String [2] = String[3] = String[4] = ' ';
		String [5] = ' ';
		String [6] = 'c';
		String [7] = 'm';
		String [8] = '\0';	
		
		resto= n/counter;
		String[0] = resto + 48; //ascii(48) = is character zero, ...
		n = n-resto*counter;
		counter/=10;
		
		String [1] = '.';
		
		for (i=2; i<5; i++)
		{
				resto = n/counter;
				String[i] = resto + 48; //ascii(48) = is character zero, ...
				n = n - resto*counter;
				counter/=10;
		}
  }
	
	
	
}

//-----------------------UART_OutDistance-----------------------
// Output a 32-bit number in unsigned decimal fixed-point format
// Input: 32-bit number to be transferred (resolution 0.001cm)
// Output: none
// Fixed format 1 digit, point, 3 digits, space, units, null termination
void UART_OutDistance(unsigned long n){
  UART_ConvertDistance(n);      // convert using your function
  UART_OutString(String);       // output using your function
}
