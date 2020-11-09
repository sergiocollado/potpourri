// os.c
// Runs on LM4F120/TM4C123/MSP432
// Lab 2 starter file.
// Daniel Valvano
// February 20, 2016

#include <stdint.h>
#include "os.h"
#include "../inc/CortexM.h"
#include "../inc/BSP.h"

// function definitions in osasm.s
void StartOS(void);


// TCB - Thread Control Block
tcbType tcbs[NUMTHREADS];
tcbType *RunPt;   //points to the current running thread. 
int32_t Stacks[NUMTHREADS][STACKSIZE]; //space for the  stack area for each of the task threads control



// ******** OS_Init ************
// Initialize operating system, disable interrupts
// Initialize OS controlled I/O: systick, bus clock as fast as possible
// Initialize OS global variables
// Inputs:  none
// Outputs: none
void OS_Init(void){
  DisableInterrupts();
  BSP_Clock_InitFastest();// set processor clock to fastest speed
  // initialize any global variables as needed
  //***YOU IMPLEMENT THIS FUNCTION*****

}

void SetInitialStack(int i){
  //***YOU IMPLEMENT THIS FUNCTION*****
    tcbs[i].sp = &Stacks[i][STACKSIZE-16]; // thread stack pointer
    Stacks[i][STACKSIZE-1]  = 0x01000000;  // Thumb bit
    Stacks[i][STACKSIZE-3]  = 0x14141414;  // R14
    Stacks[i][STACKSIZE-4]  = 0x12121212;  // R12
    Stacks[i][STACKSIZE-5]  = 0x03030303;  // R3
    Stacks[i][STACKSIZE-6]  = 0x02020202;  // R2
    Stacks[i][STACKSIZE-7]  = 0x01010101;  // R1
    Stacks[i][STACKSIZE-8]  = 0x00000000;  // R0
    Stacks[i][STACKSIZE-9]  = 0x11111111;  // R11
    Stacks[i][STACKSIZE-10] = 0x10101010;  // R10
    Stacks[i][STACKSIZE-11] = 0x09090909;  // R9
    Stacks[i][STACKSIZE-12] = 0x08080808;  // R8
    Stacks[i][STACKSIZE-13] = 0x07070707;  // R7
    Stacks[i][STACKSIZE-14] = 0x06060606;  // R6
    Stacks[i][STACKSIZE-15] = 0x05050505;  // R5
    Stacks[i][STACKSIZE-16] = 0x04040404;  // R4
}

//******** OS_AddThreads ***************
// Add four main threads to the scheduler
// Inputs: function pointers to four void/void main threads
// Outputs: 1 if successful, 0 if this thread can not be added
// This function will only be called once, after OS_Init and before OS_Launch
int OS_AddThreads(void(*task0)(void),
                  void(*task1)(void),
                  void(*task2)(void),
                  void(*task3)(void)){
// initialize TCB circular list
// initialize RunPt
// initialize four stacks, including initial PC
  //***YOU IMPLEMENT THIS FUNCTION*****
    int32_t status;
    status = StartCritical();
    tcbs[0].next = &tcbs[1]; // 0 points to 1
    tcbs[1].next = &tcbs[2]; // 1 points to 2
    tcbs[2].next = &tcbs[3]; // 2 points to 3
    tcbs[3].next = &tcbs[0]; // 3 points to 0
										
    SetInitialStack(0); Stacks[0][STACKSIZE-2] = (int32_t)(task0); // setting the PC to be the start point
    SetInitialStack(1); Stacks[1][STACKSIZE-2] = (int32_t)(task1); // setting the PC to be the start point
    SetInitialStack(2); Stacks[2][STACKSIZE-2] = (int32_t)(task2); // setting the PC to be the start point
    SetInitialStack(3); Stacks[3][STACKSIZE-2] = (int32_t)(task3); // setting the PC to be the start point
    RunPt = &tcbs[0];        // thread 0 will run first
    EndCritical(status);
    return 1; // successful
}

//******** OS_AddThreads3 ***************
// add three foregound threads to the scheduler
// This is needed during debugging and not part of final solution
// Inputs: three pointers to a void/void foreground tasks
// Outputs: 1 if successful, 0 if this thread can not be added
int OS_AddThreads3(void(*task0)(void),
                   void(*task1)(void),
                   void(*task2)(void)){ 
// initialize TCB circular list (same as RTOS project)
// initialize RunPt
// initialize four stacks, including initial PC
  //***YOU IMPLEMENT THIS FUNCTION*****
    int32_t status;
    status = StartCritical();
    tcbs[0].next = &tcbs[1]; // 0 points to 1
    tcbs[1].next = &tcbs[2]; // 1 points to 2
    tcbs[2].next = &tcbs[0]; // 2 points to 0

    SetInitialStack(0); Stacks[0][STACKSIZE-2] = (int32_t)(task0); // setting the PC to be the start point
    SetInitialStack(1); Stacks[1][STACKSIZE-2] = (int32_t)(task1); // setting the PC to be the start point
    SetInitialStack(2); Stacks[2][STACKSIZE-2] = (int32_t)(task2); // setting the PC to be the start point
    RunPt = &tcbs[0];        // thread 0 will run first
    EndCritical(status);
    return 1; // successful
}
                 
//******** OS_AddPeriodicEventThreads ***************
// Add two background periodic event threads
// Typically this function receives the highest priority
// Inputs: pointers to a void/void event thread function2
//         periods given in units of OS_Launch (Lab 2 this will be msec)
// Outputs: 1 if successful, 0 if this thread cannot be added
// It is assumed that the event threads will run to completion and return
// It is assumed the time to run these event threads is short compared to 1 msec
// These threads cannot spin, block, loop, sleep, or kill
// These threads can call OS_Signal
uint32_t Period1 = 0;
uint32_t Period2 = 0;
void (*AperiodicTask1)(void); 
void (*AperiodicTask2)(void);
uint32_t LCM = 0; 
int OS_AddPeriodicEventThreads(void(*thread1)(void), uint32_t period1,
  void(*thread2)(void), uint32_t period2){
  //***YOU IMPLEMENT THIS FUNCTION*****
  Period1= period1;
	Period2= period2;
	LCM = Period1*Period2; 
	AperiodicTask1 = thread1;
  AperiodicTask2 = thread2; 	
  return 1;
}

//******** OS_Launch ***************
// Start the scheduler, enable interrupts
// Inputs: number of clock cycles for each time slice
// Outputs: none (does not return)
// Errors: theTimeSlice must be less than 16,777,216
void OS_Launch(uint32_t theTimeSlice){
  STCTRL = 0;                  // disable SysTick during setup
  STCURRENT = 0;               // any write to current clears it
  SYSPRI3 =(SYSPRI3&0x00FFFFFF)|0xE0000000; // priority 7
  STRELOAD = theTimeSlice - 1; // reload value
  STCTRL = 0x00000007;         // enable, core clock and interrupt arm
  StartOS();                   // start on the first task
}

uint32_t Counter=0;
void Scheduler(void){ // every time slice
  // run any periodic event threads if needed
  // implement round robin scheduler, update RunPt
  //***YOU IMPLEMENT THIS FUNCTION*****
	  Counter = (Counter+1)%LCM;
	
    if((Counter%Period1) == 0){ 
      AperiodicTask1(); 
		}
		
    if((Counter%Period2) == 0){ 
      AperiodicTask2(); 
    }
		
    RunPt = RunPt->next;  // Round Robin
}

// ******** OS_InitSemaphore ************
// Initialize counting semaphore
// Inputs:  pointer to a semaphore
//          initial value of semaphore
// Outputs: none
void OS_InitSemaphore(int32_t *semaPt, int32_t value){
  //***YOU IMPLEMENT THIS FUNCTION*****
   (*semaPt) = value; 
}

// ******** OS_Wait ************
// Decrement semaphore
// Lab2 spinlock (does not suspend while spinning)
// Lab3 block if less than zero
// Inputs:  pointer to a counting semaphore
// Outputs: none
void OS_Wait(int32_t *semaPt){
    DisableInterrupts();
	  while( (*semaPt)==0 ) {
			// this is the spinlock
		    EnableInterrupts();  //interrups can occour here. so the sepaPt can get values bigger than zero.
        DisableInterrupts(); 			
			//The while-loop must spend some time with interrupts enabled to allow other threads 
			//an opportunity to run, and hence these other threads have an opportunity to call signal.
		}
		(*semaPt) = (*semaPt)-1; 
		EnableInterrupts(); 
}

// ******** OS_Signal ************
// Increment semaphore
// Lab2 spinlock
// Lab3 wakeup blocked thread if appropriate
// Inputs:  pointer to a counting semaphore
// Outputs: none
void OS_Signal(int32_t *semaPt){
//***YOU IMPLEMENT THIS FUNCTION*****
    DisableInterrupts(); 
	  (*semaPt) = (*semaPt)+1; 
	  EnableInterrupts(); 
}


// ******** mail-box data  ***************

uint32_t  MailBox; // shared global variable
int32_t   Send =0; //semaphore
int32_t   Ack  =0; //semaphore
uint32_t  Lost =0; //lost mails

// ******** OS_MailBox_Init ************
// Initialize communication channel
// Producer is an event thread, consumer is a main thread
// Inputs:  none
// Outputs: none
void OS_MailBox_Init(void){
  // include data field and semaphore
  //***YOU IMPLEMENT THIS FUNCTION*****
  Send = 0; //data has not been send yet.
	Ack  = 0; 
	Lost = 0;
}

// ******** OS_MailBox_Send ************
// Enter data into the MailBox, do not spin/block if full
// Use semaphore to synchronize with OS_MailBox_Recv
// Inputs:  data to be sent
// Outputs: none
// Errors: data lost if MailBox already has data
void OS_MailBox_Send(uint32_t data){
    //***YOU IMPLEMENT THIS FUNCTION*****
    //MailBox = data;
	  //OS_Signal(&Send);
	  if (Send) { ++Lost; }
		//If Send is already 1 at the beginning of the producer,
		//it means there is already unread data in the mailbox. 
		//In this situation, data will be lost. 
	  else {
        MailBox = data;
   		  OS_Signal(&Send);
		} //Send = 1	
		
	  //OS_Wait(&Ack);     //Wait for Ack == 1
}

// ******** OS_MailBox_Recv ************
// retreive mail from the MailBox
// Use semaphore to synchronize with OS_MailBox_Send
// Lab 2 spin on semaphore if mailbox empty
// Lab 3 block on semaphore if mailbox empty
// Inputs:  none
// Outputs: data retreived
// Errors:  none
uint32_t OS_MailBox_Recv(void){ 
	  uint32_t data;
    //***YOU IMPLEMENT THIS FUNCTION*****
	  OS_Wait(&Send);   //Wait for Send == 1
	  data = MailBox; //read Mail
	  //OS_Signal(&Ack);  // Ack = 1;
    return data;
}


