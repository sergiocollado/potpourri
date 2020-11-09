// Lab1.c
// Runs on either MSP432 or TM4C123
// Start project to Lab 1.  Take sensor readings, process the data,
// and output the results.  Specifically, this program will
// measure steps using the accelerometer, audio noise using
// microphone, and light intensity using the light sensor.
// Daniel and Jonathan Valvano
// February 3, 2016

/* This example accompanies the books
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2016

   "Embedded Systems: Real-Time Operating Systems for ARM Cortex-M Microcontrollers",
   ISBN: 978-1466468863, Jonathan Valvano, copyright (c) 2016

   "Embedded Systems: Introduction to the MSP432 Microcontroller",
   ISBN: 978-1512185676, Jonathan Valvano, copyright (c) 2016

   "Embedded Systems: Real-Time Interfacing to the MSP432 Microcontroller",
   ISBN: 978-1514676585, Jonathan Valvano, copyright (c) 2016

 Copyright 2016 by Jonathan W. Valvano, valvano@mail.utexas.edu
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

//  J1   J3               J4   J2
// [ 1] [21]             [40] [20]
// [ 2] [22]             [39] [19]
// [ 3] [23]             [38] [18]
// [ 4] [24]             [37] [17]
// [ 5] [25]             [36] [16]
// [ 6] [26]             [35] [15]
// [ 7] [27]             [34] [14]
// [ 8] [28]             [33] [13]
// [ 9] [29]             [32] [12]
// [10] [30]             [31] [11]

// +3.3V connected to J1.1 (power)
// joystick horizontal (X) connected to J1.2 (analog)
// UART from BoosterPack to LaunchPad connected to J1.3 (UART)
// UART from LaunchPad to BoosterPack connected to J1.4 (UART)
// joystick Select button connected to J1.5 (digital)
// microphone connected to J1.6 (analog)
// LCD SPI clock connected to J1.7 (SPI)
// ambient light (OPT3001) interrupt connected to J1.8 (digital)
// ambient light (OPT3001) and temperature sensor (TMP006) I2C SCL connected to J1.9 (I2C)
// ambient light (OPT3001) and temperature sensor (TMP006) I2C SDA connected to J1.10 (I2C)

// temperature sensor (TMP006) interrupt connected to J2.11 (digital)
// nothing connected to J2.12 (SPI CS_Other)
// LCD SPI CS connected to J2.13 (SPI)
// nothing connected to J2.14 (SPI MISO)
// LCD SPI data connected to J2.15 (SPI)
// nothing connected to J2.16 (reset)
// LCD !RST connected to J2.17 (digital)
// nothing connected to J2.18 (SPI CS_Wireless)
// servo PWM connected to J2.19 (PWM)
// GND connected to J2.20 (ground)

// +5V connected to J3.21 (power)
// GND connected to J3.22 (ground)
// accelerometer X connected to J3.23 (analog)
// accelerometer Y connected to J3.24 (analog)
// accelerometer Z connected to J3.25 (analog)
// joystick vertical (Y) connected to J3.26 (analog)
// nothing connected to J3.27 (I2S WS)
// nothing connected to J3.28 (I2S SCLK)
// nothing connected to J3.29 (I2S SDout)
// nothing connected to J3.30 (I2S SDin)

// LCD RS connected to J4.31 (digital)
// user Button2 (bottom) connected to J4.32 (digital)
// user Button1 (top) connected to J4.33 (digital)
// gator hole switch connected to J4.34 (digital)
// nothing connected to J4.35
// nothing connected to J4.36
// RGB LED blue connected to J4.37 (PWM)
// RGB LED green connected to J4.38 (PWM)
// RGB LED red (jumper up) or LCD backlight (jumper down) connected to J4.39 (PWM)
// buzzer connected to J4.40 (PWM)

#include <stdint.h>
#include "BSP.h"
#include "Profile.h"
#include "Texas.h"
#include "CortexM.h"

uint32_t sqrt32(uint32_t s);

//---------------- Global variables shared between tasks ----------------
uint32_t Time;              // elasped time in seconds
uint32_t Steps;             // number of steps counted
uint32_t Magnitude;         // will not overflow (3*1,023^2 = 3,139,587)
                            // Exponentially Weighted Moving Average
uint32_t EWMA;              // https://en.wikipedia.org/wiki/Moving_average#Exponential_moving_average
uint16_t SoundData;         // raw data sampled from the microphone
uint32_t SoundRMS;          // Root Mean Square average of most recent sound samples
uint32_t LightData;
int ReDrawAxes = 0;         // non-zero means redraw axes on next display task

enum plotstate{
  Accelerometer,
  Microphone,
  Light
};
enum plotstate PlotState = Accelerometer;
//color constants
#define BGCOLOR     LCD_BLACK
#define AXISCOLOR   LCD_ORANGE
#define MAGCOLOR    LCD_YELLOW
#define EWMACOLOR   LCD_CYAN
#define SOUNDCOLOR  LCD_CYAN
#define LIGHTCOLOR  LCD_LIGHTGREEN
#define TOPTXTCOLOR LCD_WHITE
#define TOPNUMCOLOR LCD_ORANGE
//------------ end of Global variables shared between tasks -------------

//---------------- Task0 samples sound from microphone ----------------
//#define SOUNDRMSLENGTH 10   // number of samples to collect before calculating RMS (may overflow if greater than 4104)
#define SOUNDRMSLENGTH 1000 // number of samples to collect before calculating RMS (may overflow if greater than 4104)
int16_t SoundArray[SOUNDRMSLENGTH];
// *********Task0_Init*********
// initializes microphone
// Task0 measures sound intensity
// Inputs:  none
// Outputs: none
void Task0_Init(void){
  BSP_Microphone_Init();
  SoundRMS = 0;
}
// *********Task0*********
// collects data from microphone
// Inputs:  none
// Outputs: none
void Task0(void){
  static int32_t soundSum = 0;
  static int time = 0;// units of microphone sampling rate
  int32_t soundAvg;
  int i;
  TExaS_Task0();     // record system time in array, toggle virtual logic analyzer
  Profile_Toggle0(); // viewed by the logic analyzer to know Task0 started
  BSP_Microphone_Input(&SoundData);
  soundSum = soundSum + (int32_t)SoundData;
  SoundArray[time] = SoundData;
  time = time + 1;
  if(time == SOUNDRMSLENGTH){
    time = 0;
    soundAvg = soundSum/SOUNDRMSLENGTH;
    soundSum = 0;
    for(i=0; i<SOUNDRMSLENGTH; i=i+1){
      soundSum = soundSum + (SoundArray[i] - soundAvg)*(SoundArray[i] - soundAvg);
    }
    SoundRMS = sqrt32(soundSum/SOUNDRMSLENGTH);
    soundSum = 0;
  }
}

void Task0_25times()
{
	for(int i=0; i<25; ++i)
	{
		Task0();
	}
}
/* ****************************************** */
/*          End of Task0 Section              */
/* ****************************************** */

//---------------- Task1 measures acceleration ----------------
uint16_t AccX, AccY, AccZ;  // returned by BSP as 10-bit numbers
#define ALPHA 128           // The degree of weighting decrease, a constant smoothing factor between 0 and 1,023. A higher ALPHA discounts older observations faster.
                            // basic step counting algorithm is based on a forum post from
                            // http://stackoverflow.com/questions/16392142/android-accelerometer-profiling/16539643#16539643
enum state{                 // the step counting algorithm cycles through four states
  LookingForMax,            // looking for a local maximum in current magnitude
  LookingForCross1,         // looking for current magnitude to cross average magnitude, minus a constant
  LookingForMin,            // looking for a local minimum in current magnitude
  LookingForCross2          // looking for current magnitude to cross average magnitude, plus a constant
};
enum state AlgorithmState = LookingForMax;
uint32_t LocalMin = 1024;   // smallest measured magnitude since odd-numbered step detected
uint32_t LocalMax = 0;      // largest measured magnitude since even-numbered step detected
uint32_t LocalCount = 0;    // number of measured magnitudes above local min or below local max
#define LOCALCOUNTTARGET 5  // The number of valid measured magnitudes needed to confirm a local min or local max.  Increase this number for longer strides or more frequent measurements.
#define AVGOVERSHOOT 25     // The amount above or below average a measurement must be to count as "crossing" the average.  Increase this number to reject increasingly hard shaking as steps.
// *********Task1_Init*********
// initializes accelerometer
// Task1 counts Steps
// Inputs:  none
// Outputs: none
void Task1_Init(void){
  BSP_Accelerometer_Init();
  // initialize the exponential weighted moving average filter
  BSP_Accelerometer_Input(&AccX, &AccY, &AccZ);
  Magnitude = sqrt32(AccX*AccX + AccY*AccY + AccZ*AccZ);
  EWMA = Magnitude;                // this is a guess; there are many options
  Steps = 0;
}
// *********Task1*********
// collects data from accelerometer
// counts Steps
// Inputs:  none
// Outputs: none
void Task1(void){
  TExaS_Task1();     // record system time in array, toggle virtual logic analyzer
  Profile_Toggle1(); // viewed by the logic analyzer to know Task1 started

  BSP_Accelerometer_Input(&AccX, &AccY, &AccZ);
  Magnitude = sqrt32(AccX*AccX + AccY*AccY + AccZ*AccZ);
  EWMA = (ALPHA*Magnitude + (1023 - ALPHA)*EWMA)/1024;

  if(AlgorithmState == LookingForMax){
    if(Magnitude > LocalMax){
      LocalMax = Magnitude;
      LocalCount = 0;
    } else{
      LocalCount = LocalCount + 1;
      if(LocalCount >= LOCALCOUNTTARGET){
        AlgorithmState = LookingForCross1;
      }
    }
  } else if(AlgorithmState == LookingForCross1){
    if(Magnitude > LocalMax){
      // somehow measured a very large magnitude
      LocalMax = Magnitude;
      LocalCount = 0;
      AlgorithmState = LookingForMax;
    } else if(Magnitude < (EWMA -  AVGOVERSHOOT)){
      // step detected
      Steps = Steps + 1;
      LocalMin = 1024;
      LocalCount = 0;
      AlgorithmState = LookingForMin;
    }
  } else if(AlgorithmState == LookingForMin){
    if(Magnitude < LocalMin){
      LocalMin = Magnitude;
      LocalCount = 0;
    } else{
      LocalCount = LocalCount + 1;
      if(LocalCount >= LOCALCOUNTTARGET){
        AlgorithmState = LookingForCross2;
      }
    }
  } else if(AlgorithmState == LookingForCross2){
    if(Magnitude < LocalMin){
      // somehow measured a very small magnitude
      LocalMin = Magnitude;
      LocalCount = 0;
      AlgorithmState = LookingForMin;
    } else if(Magnitude > (EWMA + AVGOVERSHOOT)){
      // step detected
      Steps = Steps + 1;
      LocalMax = 0;
      LocalCount = 0;
      AlgorithmState = LookingForMax;
    }
  }
}
/* ****************************************** */
/*          End of Task1 Section              */
/* ****************************************** */


//---------------- Task2 measures light ----------------
uint32_t Task2Failures;  // number of times Light wasn't ready
// *********Task2_Init*********
// initializes light sensor
// Task2 measures light intensity
// Inputs:  none
// Outputs: none
void Task2_Init(void){
  Task2Failures = 0;
  BSP_LightSensor_Init();
  LightData = BSP_LightSensor_Input();
  BSP_LightSensor_Start();
}
// *********Task2*********
// collects data from light sensor
// Inputs:  none
// Outputs: none
// must be called less than once a second
void Task2(void){
  TExaS_Task2();     // record system time in array, toggle virtual logic analyzer
  Profile_Toggle2(); // viewed by the logic analyzer to know Task2 started

  if(BSP_LightSensor_End(&LightData)==0){
    Task2Failures++;      // should have been ready
  }
  BSP_LightSensor_Start(); // start measurement for next time
}
/* ****************************************** */
/*          End of Task2 Section              */
/* ****************************************** */

//------------Task3 handles switch input, buzzer output, LED output-------
// *********Task3_Init*********
// initializes switches, buzzer, and LEDs
// Task3 checks the switches, updates the mode, and outputs to the buzzer and LED
// Inputs:  none
// Outputs: none
void Task3_Init(void){
  BSP_Button1_Init();
  BSP_Button2_Init();
  BSP_Buzzer_Init(0);
  BSP_RGB_Init(0, 0, 0);
}
// *********Task3*********
// non-real-time task
// checks the switches, updates the mode, and outputs to the buzzer and LED
// Inputs:  none
// Outputs: none
void Task3(void){
  static uint8_t prev1 = 0, prev2 = 0;
  uint8_t current;
  TExaS_Task3();     // record system time in array, toggle virtual logic analyzer
  Profile_Toggle3(); // viewed by the logic analyzer to know Task3 started

  BSP_Buzzer_Set(0);
  current = BSP_Button1_Input();
  if((current == 0) && (prev1 != 0)){
    // Button1 was pressed since last loop
    if(PlotState == Accelerometer){
      PlotState = Microphone;
    } else if(PlotState == Microphone){
      PlotState = Light;
    } else if(PlotState == Light){
      PlotState = Accelerometer;
    }
    ReDrawAxes = 1;                // redraw axes on next call of display task
    BSP_Buzzer_Set(512);           // beep until next call of this task
  }
  prev1 = current;
  current = BSP_Button2_Input();
  if((current == 0) && (prev2 != 0)){
    // Button2 was pressed since last loop
    if(PlotState == Accelerometer){
      PlotState = Light;
    } else if(PlotState == Microphone){
      PlotState = Accelerometer;
    } else if(PlotState == Light){
      PlotState = Microphone;
    }
    ReDrawAxes = 1;                // redraw axes on next call of display task
    BSP_Buzzer_Set(512);           // beep until next call of this task
  }
  prev2 = current;
  // update the LED
  switch(AlgorithmState){
    case LookingForMax: BSP_RGB_Set(500, 0, 0); break;
    case LookingForCross1: BSP_RGB_Set(350, 350, 0); break;
    case LookingForMin: BSP_RGB_Set(0, 500, 0); break;
    case LookingForCross2: BSP_RGB_Set(0, 0, 500); break;
    default: BSP_RGB_Set(0, 0, 0);
  }
}
/* ****************************************** */
/*          End of Task3 Section              */
/* ****************************************** */


//---------------- Task4 plots data on LCD ----------------
#define ACCELERATION_MAX 1400
#define ACCELERATION_MIN 600
#define SOUND_MAX 900
#define SOUND_MIN 300
#define LIGHT_MAX 200000
#define LIGHT_MIN 0
void drawaxes(void){
  if(PlotState == Accelerometer){
    BSP_LCD_Drawaxes(AXISCOLOR, BGCOLOR, "Time", "Mag", MAGCOLOR, "Ave", EWMACOLOR, ACCELERATION_MAX, ACCELERATION_MIN);
  } else if(PlotState == Microphone){
    BSP_LCD_Drawaxes(AXISCOLOR, BGCOLOR, "Time", "Sound", SOUNDCOLOR, "", 0, SoundData+100, SoundData-100);
  } else if(PlotState == Light){
    BSP_LCD_Drawaxes(AXISCOLOR, BGCOLOR, "Time", "Light", LIGHTCOLOR, "", 0, LIGHT_MAX, LIGHT_MIN);
  }
}

// return the number of digits
int numlength(uint32_t n){
  if(n < 10) return 1;
  if(n < 100) return 2;
  if(n < 1000) return 3;
  if(n < 10000) return 4;
  if(n < 100000) return 5;
  if(n < 1000000) return 6;
  if(n < 10000000) return 7;
  if(n < 100000000) return 8;
  if(n < 1000000000) return 9;
  return 10;
}

// *********Task4_Init*********
// initializes LCD
// Task4 updates the plot and Task5 updates the text at the top of the plot
// Inputs:  none
// Outputs: none
void Task4_Init(void){
  BSP_LCD_Init();
  BSP_LCD_FillScreen(BSP_LCD_Color565(0, 0, 0));
  drawaxes();
  ReDrawAxes = 0;
}
// *********Task4*********
// updates the plot
// Inputs:  none
// Outputs: none
void Task4(void){
  TExaS_Task4();     // record system time in array, toggle virtual logic analyzer
  Profile_Toggle4(); // viewed by the logic analyzer to know Task4 started

  if(ReDrawAxes){
    ReDrawAxes = 0;
    drawaxes();
  }
  if(PlotState == Accelerometer){
    BSP_LCD_PlotPoint(Magnitude, MAGCOLOR);
    BSP_LCD_PlotPoint(EWMA, EWMACOLOR);
  } else if(PlotState == Microphone){
    BSP_LCD_PlotPoint(SoundData, SOUNDCOLOR);
  } else if(PlotState == Light){
    BSP_LCD_PlotPoint(LightData, LIGHTCOLOR);
  }
  BSP_LCD_PlotIncrement();
}
/* ****************************************** */
/*          End of Task4 Section              */
/* ****************************************** */


/* ------------------------------------------ */
//------- Task5 displays text on LCD -----------
/* ------------------------------------------ */
// *********Task5_Init*********
// initializes LCD
// Task5 updates the text at the top of the plot
// Inputs:  none
// Outputs: none
void Task5_Init(void){
  // assumes BSP_LCD_Init(); has been called
  BSP_LCD_DrawString(0, 0,  "Time=",  TOPTXTCOLOR);
  BSP_LCD_DrawString(0, 1,  "Step=",  TOPTXTCOLOR);
  BSP_LCD_DrawString(10, 0, "Light=", TOPTXTCOLOR);
  BSP_LCD_DrawString(10, 1, "Sound=", TOPTXTCOLOR);
}

// *********Task5*********
// updates the text at the top of the LCD
// Inputs:  none
// Outputs: none
void Task5(void){
  TExaS_Task5();     // record system time in array, toggle virtual logic analyzer
  Profile_Toggle5(); // viewed by the logic analyzer to know Task5 started

  BSP_LCD_SetCursor(5,  0); BSP_LCD_OutUDec4(Time,          TOPNUMCOLOR);
  BSP_LCD_SetCursor(5,  1); BSP_LCD_OutUDec4(Steps,         MAGCOLOR);
  BSP_LCD_SetCursor(16, 0); BSP_LCD_OutUDec4(LightData/100, LIGHTCOLOR);
  BSP_LCD_SetCursor(16, 1); BSP_LCD_OutUDec4(SoundRMS,      SOUNDCOLOR);
}
/* ****************************************** */
/*          End of Task5 Section              */
/* ****************************************** */

int main(void){
  DisableInterrupts();
  BSP_Clock_InitFastest();
  Profile_Init();               // initialize the 7 hardware profiling pins
  // change 1000 to 4-digit number from edX 
  TExaS_Init(GRADER, 5993 );         // initialize the Lab 1 grader
//  TExaS_Init(LOGICANALYZER, 1000);  // initialize the Lab 1 logic analyzer
  Task0_Init();    // microphone init
  Task1_Init();    // accelerometer init
  Task2_Init();    // light init
  Task3_Init();    // buttons init
  Task4_Init();    // LCD graphics init
  Task5_Init();    // LCD text init
  Time = 0;
  EnableInterrupts(); // interrupts needed for grader to run
  while(1){
    for(int i=0; i<10; i++){ // runs at about 10 Hz
      Task0_25times();  // sample microphone
      Task1();  // sample accelerometer
      Task0_25times();
      Task3();  // check the buttons and change mode if pressed
			Task0_25times();
      Task4();  // update the plot
			Task0_25times();
      BSP_Delay1ms(100);
    }
    Task2();   // sample light at 1 Hz
    Task5();   // update the LCD text at 1 Hz
    Time++;    // 1 Hz
    Profile_Toggle6();
  }

}

// Newton's method
// s is an integer
// sqrt(s) is an integer
uint32_t sqrt32(uint32_t s){
uint32_t t;   // t*t will become s
int n;             // loop counter
  t = s/16+1;      // initial guess
  for(n = 16; n; --n){ // will finish
    t = ((t*t+s)/t)/2;
  }
  return t;
}




