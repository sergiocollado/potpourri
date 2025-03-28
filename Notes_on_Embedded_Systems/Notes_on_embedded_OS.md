# NOTES ON EMBEDDED OPERATING SYSTEMS.

# KERNEL ARCHITECTURES

 - Monolitic
 - Microkernel
 - Modular
 
 ## Monolitic kernel
 
 In a monolitik kernel the main function and services of the OS, such: file systems, device drivers ... are executed in kernel mode,
 this means that the kernel usually is quite big.
 
 Examples of monolitic kernels are: MS windows, linux, unix, Mac OS.
 
 ## Microkernel
 
 A microkernel, most of the main functions and services of the OS, are not inside the kernel, so they don't run in kernel mode, instead
 those are located and run in the user mode. For example it separates the kernel, from the hardware control, and devices. As consecuence
 the kernel size, is much smaller as compared with a monolitic kernel.
 
 In a microkernel, it only keeps the most basics needed tasks, as:
 - Interrupt handling
 - low-level processes management
 - message passing and control (IPC -inter processes comunication: a method to commincation and data sharing between processes)
 
 As a result, there is an improvement in the stability and reliability of the kernel, due in the case a process crashes, it will not affect the kernel, making it crash also. 

 As drawbacks of the microkernels, one is that the context stching is quite much expensive than in a monolitic kernel, due most of the
 functions are in the user space, and then it needs to call many more functions. Also another drawback is that the overall system responses or hardware responses are slower, due to the more expensive context switch.
 
 Examples of microkernel OS are: GNU/Hurd, Minix, QNX.
 
 ## Modular kernel
 
 A modular kernel is a combination of the two previous concepts: monolitic and microkernel, and its goal is to have the best features of both types. It aims to perform sytem tasks as good as a monolitic kernel, while retaining the good stability of a microkernel.
 
 A modular kernel is made of different modules, and each modules focus on doing only one specific system task. A key point in this architecture, is that modules, are only loaded when needed. Another good thing, about the capability of loading modules as needed, is that the OS system footprint is reduced. 
 
 drawbacks of the modular kernels: 
 
 Of course, care has to be taken when loading and unloading modules, because this action takes a fair amount of time. So contantly loading and unloading modules is not recommended.
 
 In case of memory fragmentation, the stability of the system cannot be guaranteed. 
 
An example of a modular kernel: contiki.


A good reference about how to write RTOS is in the code of the µC/OS-II and µC/OS-III https://www.micrium.com/rtos/kernels/


<hr>

# [CONTIKI](http://www.contiki-os.org/)

This OS is intended for IoT devices. It uses a modular kernel.

It was created by Adam Dunkels  in 2002, and its Open Source. It is specifically designed for network and memory constrained systems. It's main focus is in low power wireless sensor systems and Internet-of-Things devices. So is a lightweight OS, enought to comply the requirements of an embedded device, with small memory and battery powered. Its footprint is about 10kb of RAM, and 30kb of ROM. Its is developed in C language.

- It is a hybrid modular OS, that combines features from monolitic and microkernel architecures.

- It works on an event-driven kernel, and supports preemptive multithreading. It uses protothreads, software flow control.- protothreads, is a mechanism that mixes an event-driven model and threads, to provide a sequential flow control without using complex state machines.

- It is based in a modular kernel, that supports dynamic module loading and linking at run-time. It is able to load and unload services/applications at run time.

- It uses a  posting events messaging mechanism for communicating services and the kernel.

- It also provides mechanims for efficient memory allocation.

- It has a full TPC/IP implementations stack.- Includes IPv4 and IPv6

- It also supports low power wireless standards as: 6LoWPAN, RPL, and CoAP.

- It has a mechanism for estimating the system's power consumpiton.

- It supports several hardware devices.

- It doesn't have a HAL (Hardware Abstraction Layer).- it communicates directly with the hw.

- It is easy to port Contiki to new microcontrollers and harware, with little effort, with configuration files.

- To rapid implementation of wireless networks, it provides the Cojaa Network Simulator.

- It has a Command Line Shell suitable for debugging applications.

Quick start reference guide:  http://www.contiki-os.org/start.html

Reference: http://www.contiki-os.org/

Reference updated: http://contiki-iot.blogspot.com.es/2016/07/how-to-set-up-contiki-os-communication_11.html

Reference: http://internetofthingsagenda.techtarget.com/feature/The-Contiki-IoT-OS-is-the-calm-in-the-storm-of-IoT-OSes?utm_content=control&utm_medium=EM&asrc=EM_ERU_77935633&utm_campaign=20170601_ERU%20Transmission%20for%2006/01/2017%20(UserUniverse:%202383547)&utm_source=ERU&src=5639188

hands-on into it: https://github.com/contiki-os/contiki/wiki

All the documentation: http://contiki.sourceforge.net/docs/2.6/

for energy estimations: https://github.com/mzimmerling/ptunes/blob/master/contiki/examples/energest-demo/contiki-sky-main.c

To change the network stack:  https://github.com/contiki-os/contiki/wiki/Change-mac-or-radio-duty-cycling-protocols

Articles: http://dunkels.com/adam/dunkels11contikimac.pdf

Tutorials and more:

 - http://anrg.usc.edu/contiki/index.php/Broadcast_Example
 - http://anrg.usc.edu/contiki/index.php/Contiki_tutorials
 - http://anrg.usc.edu/contiki/index.php/MAC_protocols_in_ContikiOS
 - https://github.com/contiki-os/contiki/wiki/Processes
 
Cooja manual:

 - https://www.researchgate.net/publication/304572240_Cooja_Simulator_Manual
 
Some cool demos:

 - http://ai.vub.ac.be/Robotics/wiki/index.php/Some_cool_demos
 
# TinyOS

Is another Iot embedded OS. It is open-source. It has a monolitic kernel.

It is designed for network and constrained systems. It is lightweight.

Created in 1999 by Berkeley University. 

TinyOS, and it's applications are written using nesC. NesC is a structured component based extension of C languaje. 

It has a minimal footprint.

It runs with a simple scheduler based on death-lines.

It allows debugging, and support race condition detections.

It is based on active messages, that are the main comunication abstraction model of TinyOS.

The main code of TinyOS consists on 401 components.

Supports low power operations.

tool for energy estimation: http://tinyos.stanford.edu/tinyos-wiki/index.php/Avrora

Safe-tinyOS: http://tinyos.stanford.edu/tinyos-wiki/index.php/Safe_TinyOS

## Basics concepts of nesC

- Separation of construction and composition. All programs in TinyOS, are build as components, and then assembled as a whole program.
- Components, have internal concurrency on the form of tasks. A component is called via it's interface.
- Specification of component behavior using a set of interfaces.
- Bidirectional interfaces. That means that intefaces provides functions with both: commands and events.
- Statically linking of components, via interfaces.
- Generated by a whole program compiler.


# [RIOT OS]( http://internetofthingsagenda.techtarget.com/definition/RIOT-operating-system?utm_content=control&utm_medium=EM&asrc=EM_ERU_77819154&utm_campaign=20170530_ERU%20Transmission%20for%2005/30/2017%20(UserUniverse:%202380487)&utm_source=ERU&src=5638584)


REFERENCE: https://riot-os.org/

It is a embedded IoT OS, based on a microkernel design inherit from Fire-kernel.

low power network systems devices. 

written in ANSI-C. but it allows use of c++.

has TCP/IP stack. IPv4, IPv6, UDP and TCP. 

designed for nerwork and memory constrain systems.

Is designed in modular way. 

Is uses a tick-less scheduler.-  so it can switch to the idle-thread, and reduce energy consumption.

Small footprint.

It uses native features in processors.

It separates CPU code, and kernel implementation.

It supports zero latency interrupt handlers, and uses a minimun context-switching times with threads priorities.

Supports multi-threading and C++

support common wireless protocols for constrained resourced systems as: 6LoWPAN and RPL. A layer that supports IEEE 802.15.4.

distributed systems can be easily implemented using the kernel system API.



# QNX

QNX is a comertial embedded real-time system, that complies with the POSIX specs. It uses a microkernel, and the processes managmement if fully controlled by means of messages. QNX features several scheduling algorithms: FIFO, Round-Robin, adaptative & sporadic, periodig, and of course priority based scheduling, also have preentive multitasking. This makes it very good option to mission critical systems. 

Qnx has a common message system for IPC (inter process communications) and also used to handle the computer networks communications. 

ACRONYMS:

WCET - Worst Case Execution Time
CFG - Control Flow Graph


# FREERTOS
FreeRTOS uses a tick scheduler.

https://www.freertos.org/Documentation/RTOS_book.html


Example of a task creation:

```C
/*Comunication task:*/

/*help variables for tasks*/
BaseType_t xReturnedComunication;
TaskHandle_t communication_handle = NULL;

int main( void )
{
	printf("Hello World!");

	prvInitialiseHeap();

	/* Create the task, storing the handle. */
	xReturnedComunication = xTaskCreate(
		(pdTASK_CODE)communication_task,  /* Function that implements the task. */
		(signed char *)"Communication", /* Text name for the task. */
		configMINIMAL_STACK_SIZE, /* Stack size in words, not bytes. */
		NULL, /* Parameter passed into the task. */
		1, /* The priority at which the created task will execute. */
		&communication_handle);  /* Used to pass out the created task's handle. */

	if (xReturnedComunication == pdPASS)
	{
		printf("SUCCEDD communication task");	fflush(stdout);
	}
	else if (xReturnedComunication == pdFAIL) {
		printf("FAILURE communication task");	fflush(stdout);
                /*Use the task's handle to delete the task. */
		vTaskDelete(communication_handle);
	}

	vTaskStartScheduler();

	for (;;);
	return 0;
}

void communication_task(void)
{
 //function code
 while(1) {
 }
}
```

References:

http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
the FAQ page "My application does not run, what could be wrong?".  Have you
defined configASSERT()?

http://www.FreeRTOS.org/support - In return for receiving this top quality
embedded software for free we request you assist our global community by
participating in the support forum.

http://www.FreeRTOS.org/training - Investing in training allows your team to
be as productive as possible as early as possible.  Now you can receive
FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
Ltd, and the world's leading authority on the world's leading RTOS.

http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
including FreeRTOS+Trace - an indispensable productivity tool, a DOS
compatible FAT file system, and our tiny thread aware UDP/IP stack.

http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
licenses offer ticketed support, indemnification and commercial middleware.

http://www.SafeRTOS.com - High Integrity Systems also provide a safety
engineered and independently SIL3 certified version for use in safety and
mission critical applications that require provable dependability.

Posix https://pubs.opengroup.org/onlinepubs/9699919799/functions/contents.html


# ZEPHYR 

https://www.zephyrproject.org/


# RTEM

https://www.rtems.org/


# NuttX 

https://nuttx.apache.org/docs/latest/

NuttX is a real-time operating system (RTOS) with an emphasis on standards compliance and small footprint. Scalable from 8-bit to 64-bit microcontroller environments, the primary governing standards in NuttX are POSIX and ANSI standards. Additional standard APIs from Unix and other common RTOS’s (such as VxWorks) are adopted for functionality not available under these standards, or for functionality that is not appropriate for deeply-embedded environments (such as fork()).


# POSIX 

POSIX  stands for Portable Operating System Interface. It is a proposal to use a common interface and semantics for portable applications that comply with the POSIX standard. 



https://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html#tag_15_08

# POSIX Safety Concepts

https://www.gnu.org/software/libc/manual/html_node/POSIX-Safety-Concepts.html#POSIX-Safety-Concepts

https://www.ctr.unican.es/publications/mgh-1993a.pdf

https://pubs.opengroup.org/onlinepubs/9699919799/nframe.html

https://wiki.debian.org/POSIX



Other embedded OS:

- http://www.chibios.org/dokuwiki/doku.php
