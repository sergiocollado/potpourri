/*
 * FreeRTOS Kernel V10.0.1
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/******************************************************************************
 * This project provides two demo applications.  A simple blinky style project,
 * and a more comprehensive test and demo application.  The
 * mainCREATE_SIMPLE_BLINKY_DEMO_ONLY setting is used to select between the two.
 * The simply blinky demo is implemented and described in main_blinky.c.  The
 * more comprehensive test and demo application is implemented and described in
 * main_full.c.
 *
 * This file implements the code that is not demo specific, including the
 * hardware setup and FreeRTOS hook functions.
 *
 *******************************************************************************
 * NOTE: Windows will not be running the FreeRTOS demo threads continuously, so
 * do not expect to get real time behaviour from the FreeRTOS Windows port, or
 * this demo application.  Also, the timing information in the FreeRTOS+Trace
 * logs have no meaningful units.  See the documentation page for the Windows
 * port for further information:
 * http://www.freertos.org/FreeRTOS-Windows-Simulator-Emulator-for-Visual-Studio-and-Eclipse-MingW.html
 *

 *
 *******************************************************************************
 */

/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/*prototypes*/
static void CreateMatrixTask(void);
static void CreateComunicationTask(void);
static void CreatePriorityTask(void);
static void matrix_task(void);
static void communication_task(void);
static void priority_task(void);

/* Run time and task stats gathering related definitions. */
#define configGENERATE_RUN_TIME_STATS           1	//to use vTaskGetRunTimeStats()
#define configUSE_TRACE_FACILITY                1
#define configUSE_STATS_FORMATTING_FUNCTIONS    1
#define configUSE_APPLICATION_TASK_TAG 1 // to use xTaskCallApplicationTaskHook()

extern volatile unsigned long ulHighFrequencyTimerTicks=0;

extern void vConfigureTimerForRunTimeStats(void); /*defined in win32 port in Run-time-stats-utils.c*/
unsigned long ulGetRunTimeCounterValue(void); /*defined in win32 port in Run-time-stats-utils.c*/

#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() vConfigureTimerForRunTimeStats()
#define portGET_RUN_TIME_COUNTER_VALUE() ulGetRunTimeCounterValue()

char TimeStats[3*1024];

/*Matrix task:*/

/*help variables for tasks*/
BaseType_t xReturnedMatrixTask;
TaskHandle_t matrix_handle = NULL;

/*Comunication task:*/

/*help variables for tasks*/
BaseType_t xReturnedComunication;
TaskHandle_t communication_handle = NULL;

/*Priority task:*/

/*help variables for tasks*/
BaseType_t xReturnedPriorityTask;
TaskHandle_t priority_handle = NULL;

/*global variables*/
volatile TickType_t num_ticks = 0;
unsigned long int num_ticks_matrix = 0;
unsigned long  int num_comm_task_ticks = 0;
unsigned long  int num_prio_ticks = 0;


unsigned long  int matrix_task_period = 0;
unsigned long  int commun_task_period = 0;
unsigned long  int priori_task_period = 0;

unsigned long  int last_matrix_tick_call = 0;
unsigned long  int last_commun_tick_call = 0;
unsigned long  int last_priori_tick_call = 0;

unsigned long  int num_comm_ticks_init = 0; /* start comm loop ticks time*/
unsigned long  int num_comm_ticks_end = 0;  /* end comm loop ticks time*/
unsigned long  int num_comm_ticks_run = 0;  /* num_comm_ticks_run = num_comm_ticks_end - num_comm_ticks_init */

unsigned long  int matrix_period_init = 0;
unsigned long  int comm_period_init = 0;
unsigned long  int prio_period_init = 0;


/* This demo uses heap_5.c, and these constants define the sizes of the regions
that make up the total heap.  heap_5 is only used for test and example purposes
as this demo could easily create one large heap region instead of multiple
smaller heap regions - in which case heap_4.c would be the more appropriate
choice.  See http://www.freertos.org/a00111.html for an explanation. */
#define mainREGION_1_SIZE	7201
#define mainREGION_2_SIZE	29905
#define mainREGION_3_SIZE	6407

/*-----------------------------------------------------------*/


/*
 * This demo uses heap_5.c, so start by defining some heap regions.  It is not
 * necessary for this demo to use heap_5, as it could define one large heap
 * region.  Heap_5 is only used for test and example purposes.  See
 * http://www.freertos.org/a00111.html for an explanation.
 */
static void  prvInitialiseHeap( void );

/*
 * Prototypes for the standard FreeRTOS application hook (callback) functions
 * implemented within this file.  See http://www.freertos.org/a00016.html .
 */
void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );
void vApplicationTickHook( void );
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/*
 * Writes trace data to a disk file when the trace recording is stopped.
 * This function will simply overwrite any trace files that already exist.
 */
static void prvSaveTraceFile( void );

/*-----------------------------------------------------------*/

/* When configSUPPORT_STATIC_ALLOCATION is set to 1 the application writer can
use a callback function to optionally provide the memory required by the idle
and timer tasks.  This is the stack that will be used by the timer task.  It is
declared here, as a global, so it can be checked by a test that is implemented
in a different file. */
StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

/* Notes if the trace is running or not. */
static BaseType_t xTraceRunning = pdTRUE;

/*-----------------------------------------------------------*/


int main( void )
{
	printf("Hello World!");
	/* This demo uses heap_5.c, so start by defining some heap regions.  heap_5
	is only used for test and example reasons.  Heap_4 is more appropriate.  See
	http://www.freertos.org/a00111.html for an explanation. */
	prvInitialiseHeap();

	/* Initialise the trace recorder.  Use of the trace recorder is optional.
	See http://www.FreeRTOS.org/trace for more information. */
	vTraceEnable( TRC_START );

	//may tasks
	CreateMatrixTask();
	CreateComunicationTask();
    CreatePriorityTask();

	printf("\nNumber of tasks: %d\n", (int)uxTaskGetNumberOfTasks());
	vTaskStartScheduler();

	for (;;); // "for"-ever
	
	return 0;
}
/*-----------------------------------------------------------*/



/*Create Matrix task*/
void CreateMatrixTask(void)
{
	/* Create the task, storing the handle. */
	xReturnedMatrixTask = xTaskCreate(
		(pdTASK_CODE)matrix_task,  /* Function that implements the task. */
		(signed char *)"Matrix", /* Text name for the task. */
		1000, /* Stack size in words, not bytes. */
		NULL, /* Parameter passed into the task. */
		3, /* The priority at which the created task will execute*/
		&matrix_handle);  /* Used to pass out the created task's handle. */

	if (xReturnedMatrixTask == pdPASS)
	{
		/* The task was created.  Use the task's handle to delete the task. */
		//vTaskDelete(matrix_handle);
		UBaseType_t prio = uxTaskPriorityGet(matrix_handle);
		printf("\nSUCCEDD matrix task ... with prio: %d", (int)prio);	fflush(stdout);
	}
	else if (xReturnedMatrixTask == pdFAIL) {
		printf("\nFAILURE communication task");	fflush(stdout);
		/*Use the task's handle to delete the task. */
		vTaskDelete(matrix_handle);
	}
	else
	{
		printf("\nweird state matrix task"); fflush(stdout);
		vTaskDelete(matrix_handle);
	}
}


/*matrixtask*/
#define SIZE 10
#define ROW SIZE
#define COL SIZE
static void matrix_task()
{

	int i;
	double **a = (double **)pvPortMalloc(ROW * sizeof(double*));
	for (i = 0; i < ROW; i++) a[i] = (double *)pvPortMalloc(COL * sizeof(double));
	double **b = (double **)pvPortMalloc(ROW * sizeof(double*));
	for (i = 0; i < ROW; i++) b[i] = (double *)pvPortMalloc(COL * sizeof(double));
	double **c = (double **)pvPortMalloc(ROW * sizeof(double*));
	for (i = 0; i < ROW; i++) c[i] = (double *)pvPortMalloc(COL * sizeof(double));

	double sum = 0.0;
	int j, k, l;

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			a[i][j] = 1.5;
			b[i][j] = 2.6;
		}
	}

	while (1) {
		/*
		* In an embedded systems, matrix multiplication would block the CPU for a long time
		* but since this is a PC simulator we must add one additional dummy delay.
		*/
		long simulationdelay;
		for (simulationdelay = 0; simulationdelay < 1000000000; simulationdelay++)
			;
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				c[i][j] = 0.0;
			}
		}

		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				sum = 0.0;
				for (k = 0; k < SIZE; k++) {
					for (l = 0; l < 10; l++) {
						sum = sum + a[i][k] * b[k][j];
					}
				}
				c[i][j] = sum;
			}
		}

		vTaskDelay(100);
	}
}

static void CreatePriorityTask(void) {

	if (1) {
		/* Create the task, storing the handle. */
		xReturnedPriorityTask = xTaskCreate(
			(pdTASK_CODE)priority_task,  /* Function that implements the task. */
			(signed char *)"Priority", /* Text name for the task. */
			1000, /* Stack size in words, not bytes. */
			NULL, /* Parameter passed into the task. */
			1, /* The priority at which the created task will execute*/
			&priority_handle);  /* Used to pass out the created task's handle. */

		if (xReturnedPriorityTask == pdPASS)
		{
			/* The task was created.*/
			UBaseType_t prio = uxTaskPriorityGet(priority_handle);
			printf("\nSUCCEDD priority task ... with prio: %d", (int)prio);	fflush(stdout);
		}
		else if (xReturnedPriorityTask == pdFAIL) {
			printf("\nFAILURE priority task");	fflush(stdout);
			/* Use the task's handle to delete the task. */
			vTaskDelete(priority_handle);
		}
		else
		{
			printf("\nweird state priority task"); fflush(stdout);
			vTaskDelete(priority_handle);
		}
	}
}


/*priority task*/
static void priority_task()
{
	while (1) {
		//printf(".");
		
		if(num_comm_ticks_run!=0)
		{ 
			if (num_comm_ticks_run > 1000) {
				printf("\ncommunication_ticks: %d,  prio_com ->4", num_comm_ticks_run);
				vTaskPrioritySet(communication_handle, 4);
				num_comm_ticks_run = 0;
			}
			else if (num_comm_ticks_run <= 200 && num_comm_ticks_run!=0) {
				printf("\n\ncommunication_ticks: %d, prio_com ->2", num_comm_ticks_run);
				vTaskPrioritySet(communication_handle, 2);
				num_comm_ticks_run = 0;
			}
			else{
				//vTaskPrioritySet(communication_handle, 1);
				//printf("\nprio_com ->1- %d", num_comm_ticks_run);
				//vTaskPrioritySet(communication_handle, 3);
				num_comm_ticks_run = 0;
			}
		}
		//printf("Matrix task period: %d", matrix_task_period);
		fflush(stdout);
	}
}


/*Create communication task*/
void CreateComunicationTask(void)
{

	/* Create the task, storing the handle. */
	xReturnedComunication = xTaskCreate(
		(pdTASK_CODE)communication_task,  /* Function that implements the task. */
		(signed char *)"Communication", /* Text name for the task. */
		10 * configMINIMAL_STACK_SIZE, /* Stack size in words, not bytes. */
		NULL, /* Parameter passed into the task. */
		1, /* The priority at which the created task will execute */
		&communication_handle);  /* Used to pass out the created task's handle. */

	if (xReturnedComunication == pdPASS)
	{
		/* The task was created.*/
		UBaseType_t prio = uxTaskPriorityGet(communication_handle);
		printf("\nSUCCEDD communication task ... with prio: %d", (int)prio);	fflush(stdout);
	}
	else if (xReturnedComunication == pdFAIL) {
		printf("\nFAILURE communication task");	fflush(stdout);
		vTaskDelete(communication_handle);
	}
	else {
		printf("\nweird state communication task"); fflush(stdout);
		vTaskDelete(communication_handle);
	}
}
/*comunicationtask.cpp*/
static void communication_task()
{
	while (1) {
		num_comm_ticks_init = xTaskGetTickCount();
		UBaseType_t priority = uxTaskPriorityGet(communication_handle, 4);
		printf("\n\nSending data...task priority: %d", (int)priority);
		//printf("\ntick: %d", (int)num_comm_ticks_init);
		vTaskDelay(100);
		printf("\nData sent!");
		vTaskDelay(100);
		num_comm_ticks_end = xTaskGetTickCount();
		//printf("\ntack: %d", (unsigned int)num_comm_ticks_end);
		num_comm_ticks_run = num_comm_ticks_end - num_comm_ticks_init;
		printf("\nrun_com_ticks: %d", num_comm_ticks_run);

		printf("\n\nTask periods:\n matrix task: %d", matrix_task_period);
		printf("- commun task: %d", commun_task_period);
		printf("- priori task: %d", priori_task_period);
		printf("\nAverage usage:\n   matrix task: %.3f", num_ticks_matrix / (double)num_comm_ticks_end);
		printf("- commun task: %.3f", num_comm_task_ticks / (double)num_comm_ticks_end);
		printf("- priori task: %.3f", num_prio_ticks / (double)num_comm_ticks_init);
		printf("\nTotal ticks: %d", (int)num_comm_ticks_end);
		printf("\n   total task ticks: %lu \t %lu \t %lu", num_ticks_matrix, num_comm_task_ticks, num_prio_ticks);
		printf("\n\nvTaskGetRunTimeStats():");
		vTaskGetRunTimeStats(TimeStats); /* ref: https://www.freertos.org/rtos-run-time-stats.html */
		printf("\n\n%s", TimeStats);
		fflush(stdout);
	}
}

/*--------------------------------------------------------*/

/*-----------------------------------------------------------*/


void vApplicationMallocFailedHook(void)
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c, heap_2.c or heap_4.c is being used, then the
	size of the	heap available to pvPortMalloc() is defined by
	configTOTAL_HEAP_SIZE in FreeRTOSConfig.h, and the xPortGetFreeHeapSize()
	API function can be used to query the size of free heap space that remains
	(although it does not provide information on how the remaining heap might be
	fragmented).  See http://www.freertos.org/a00111.html for more
	information. */
	vAssertCalled(__LINE__, __FILE__);
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook(void)
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If application tasks make use of the
	vTaskDelete() API function to delete themselves then it is also important
	that vApplicationIdleHook() is permitted to return to its calling function,
	because it is the responsibility of the idle task to clean up memory
	allocated by the kernel to any task that has since deleted itself. */

	/* Uncomment the following code to allow the trace to be stopped with any
	key press.  The code is commented out by default as the kbhit() function
	interferes with the run time behaviour. */
	/*
		if( _kbhit() != pdFALSE )
		{
			if( xTraceRunning == pdTRUE )
			{
				vTraceStop();
				prvSaveTraceFile();
				xTraceRunning = pdFALSE;
			}
		}
	*/
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
	(void)pcTaskName;
	(void)pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected.  This function is
	provided as an example only as stack overflow checking does not function
	when running the FreeRTOS Windows port. */
	vAssertCalled(__LINE__, __FILE__);
}
/*-----------------------------------------------------------*/

void vApplicationTickHook(void)
{
	/* This function will be called by each tick interrupt if
	configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
	added here, but the tick hook is called from an interrupt context, so
	code must not attempt to block, and only the interrupt safe FreeRTOS API
	functions can be used (those that end in FromISR()). */

	num_ticks = xTaskGetTickCount();

	static TaskHandle_t prev_task = NULL;
	static TaskHandle_t current_task = NULL;

	/*prev_task update*/
	prev_task = current_task;
	/* get the current task handle*/
	current_task = xTaskGetCurrentTaskHandle();

	/*period calculation*/
	/*check if there was a change in the task*/
	if (current_task != prev_task) {
		if (current_task == matrix_handle && prev_task != matrix_handle) {
			matrix_task_period = (unsigned int)num_ticks - last_matrix_tick_call;
			last_matrix_tick_call = (unsigned int)num_ticks;
		}
		else if (current_task == communication_handle && prev_task != communication_handle) {
			commun_task_period = (unsigned int)num_ticks - last_commun_tick_call;
			last_commun_tick_call = num_ticks;
		}
		else if (current_task == priority_handle && prev_task != priority_handle) {
			priori_task_period = (unsigned int)num_ticks - last_priori_tick_call;
			last_priori_tick_call = num_ticks;
		}
	}

	//get data to calculate average cpu usage.
	if (current_task == matrix_handle) {
		num_ticks_matrix++;
	}
	else if (current_task == communication_handle) {
		num_comm_task_ticks++;
	}
	else if (current_task == priority_handle) {
		num_prio_ticks++;
	}

}
/*-----------------------------------------------------------*/

void vApplicationDaemonTaskStartupHook(void)
{
	/* This function will be called once only, when the daemon task starts to
	execute	(sometimes called the timer task).  This is useful if the
	application includes initialisation code that would benefit from executing
	after the scheduler has been started. */
}
/*-----------------------------------------------------------*/

void vAssertCalled(unsigned long ulLine, const char * const pcFileName)
{
	static BaseType_t xPrinted = pdFALSE;
	volatile uint32_t ulSetToNonZeroInDebuggerToContinue = 0;

	/* Called if an assertion passed to configASSERT() fails.  See
	http://www.freertos.org/a00110.html#configASSERT for more information. */

	/* Parameters are not used. */
	(void)ulLine;
	(void)pcFileName;

	printf("ASSERT! Line %ld, file %s, GetLastError() %ld\r\n", ulLine, pcFileName, GetLastError());

	taskENTER_CRITICAL();
	{
		/* Stop the trace recording. */
		if (xPrinted == pdFALSE)
		{
			xPrinted = pdTRUE;
			if (xTraceRunning == pdTRUE)
			{
				vTraceStop();
				prvSaveTraceFile();
			}
		}

		/* You can step out of this function to debug the assertion by using
		the debugger to set ulSetToNonZeroInDebuggerToContinue to a non-zero
		value. */
		while (ulSetToNonZeroInDebuggerToContinue == 0)
		{
			__asm { NOP };
			__asm { NOP };
		}
	}
	taskEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

static void prvSaveTraceFile(void)
{
	FILE* pxOutputFile;

	fopen_s(&pxOutputFile, "Trace.dump", "wb");

	if (pxOutputFile != NULL)
	{
		fwrite(RecorderDataPtr, sizeof(RecorderDataType), 1, pxOutputFile);
		fclose(pxOutputFile);
		printf("\r\nTrace output saved to Trace.dump\r\n");
	}
	else
	{
		printf("\r\nFailed to create trace dump file\r\n");
	}
}
/*-----------------------------------------------------------*/

static void  prvInitialiseHeap(void)
{
	/* The Windows demo could create one large heap region, in which case it would
	be appropriate to use heap_4.  However, purely for demonstration purposes,
	heap_5 is used instead, so start by defining some heap regions.  No
	initialisation is required when any other heap implementation is used.  See
	http://www.freertos.org/a00111.html for more information.

	The xHeapRegions structure requires the regions to be defined in start address
	order, so this just creates one big array, then populates the structure with
	offsets into the array - with gaps in between and messy alignment just for test
	purposes. */
	static uint8_t ucHeap[configTOTAL_HEAP_SIZE];
	volatile uint32_t ulAdditionalOffset = 19; /* Just to prevent 'condition is always true' warnings in configASSERT(). */
	const HeapRegion_t xHeapRegions[] =
	{
		/* Start address with dummy offsets						Size */
		{ ucHeap + 1,											mainREGION_1_SIZE },
		{ ucHeap + 15 + mainREGION_1_SIZE,						mainREGION_2_SIZE },
		{ ucHeap + 19 + mainREGION_1_SIZE + mainREGION_2_SIZE,	mainREGION_3_SIZE },
		{ NULL, 0 }
	};

	/* Sanity check that the sizes and offsets defined actually fit into the
	array. */
	configASSERT((ulAdditionalOffset + mainREGION_1_SIZE + mainREGION_2_SIZE + mainREGION_3_SIZE) < configTOTAL_HEAP_SIZE);

	/* Prevent compiler warnings when configASSERT() is not defined. */
	(void)ulAdditionalOffset;

	vPortDefineHeapRegions(xHeapRegions);
}
/*-----------------------------------------------------------*/

/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
used by the Idle task. */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
	/* If the buffers to be provided to the Idle task are declared inside this
	function then they must be declared static - otherwise they will be allocated on
	the stack and so not exists after this function exits. */
	static StaticTask_t xIdleTaskTCB;
	static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

	/* Pass out a pointer to the StaticTask_t structure in which the Idle task's
	state will be stored. */
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

	/* Pass out the array that will be used as the Idle task's stack. */
	*ppxIdleTaskStackBuffer = uxIdleTaskStack;

	/* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
	Note that, as the array is necessarily of type StackType_t,
	configMINIMAL_STACK_SIZE is specified in words, not bytes. */
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
/*-----------------------------------------------------------*/

/* configUSE_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
application must provide an implementation of vApplicationGetTimerTaskMemory()
to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize)
{
	/* If the buffers to be provided to the Timer task are declared inside this
	function then they must be declared static - otherwise they will be allocated on
	the stack and so not exists after this function exits. */
	static StaticTask_t xTimerTaskTCB;

	/* Pass out a pointer to the StaticTask_t structure in which the Timer
	task's state will be stored. */
	*ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

	/* Pass out the array that will be used as the Timer task's stack. */
	*ppxTimerTaskStackBuffer = uxTimerTaskStack;

	/* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
	Note that, as the array is necessarily of type StackType_t,
	configMINIMAL_STACK_SIZE is specified in words, not bytes. */
	*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

