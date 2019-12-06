/*
	This an example of a computer vision system that analyzes an image, filtering
	for edge detection, then encrypts the file, and send it through a communication socket.

	At initialization it runs some self-test functions to check the code works as expected.

	The system uses the FAT filesystem.

	Both tasks are synchronized using a lightweight binary semaphore.

	the tasks are:
	- void EdgeDetection_task(void);
	- void EncryptAndStreamTask(void);

	A timer is created to monitor the system performance so it reports the ticks and time usage
    for each task.

	other support functions are:

	bool createfile(unsigned char* bmp);
	bool encryptimage(char* imageName, char* encryptedImageName);
	bool decryptimage(char* imageName, char* decryptedImageName);
	bool BmpEqual(char* imageName, char* imageName2);
	int  checkimagesize(char* imagefileName, bool verbose);
	bool DoEdgeDetection(char* filename);
	bool checkEncryptDecrypt(char* filename);
	void GoToBaseDirectory(void);
	void SystemMonitor(void);
	bool createTCPSocket(xSocket_t* xClientSocket, TickType_t xTimeOut, struct freertos_sockaddr* xBindAddress);
	bool SendFile(char* filename, xSocket_t* xClientSocket, struct freertos_sockaddr xDestinationAddress);
	void StreamEncryptedFrame(void);
*/
/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    1 tab == 4 spaces!
*/
/*
 * Instructions for using this project are provided on:
 * http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/examples_FreeRTOS_simulator.html
 *
 * NOTE: Some versions of Visual Studio will generate erroneous compiler
 * warnings about variables being used before they are set.
 */

/* Standard includes. */
#include <stdio.h>
#include <time.h>

/* FreeRTOS includes. */
#include <FreeRTOS.h>
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"

/* FreeRTOS+TCP includes. */
#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"
#include "FreeRTOS_TCP_server.h"
#include "FreeRTOS_DHCP.h"

/* FreeRTOS+FAT includes. */
#include "ff_headers.h"
#include "ff_stdio.h"
#include "ff_ramdisk.h"

/* Demo application includes. */
//#include "SimpleUDPClientAndServer.h"
//#include "TwoUDPEchoClients.h"
#include "TCPEchoClient_SingleTasks.h"
#include "TCPEchoClient_SeparateTasks.h"
//#include "UDPCommandConsole.h"
#include "TCPCommandConsole.h"
//#include "UDPSelectServer.h"
#include "SimpleTCPEchoServer.h"
#include "TFTPServer.h"
#include "demo_logging.h"

/*for my program*/
#include "canny.h" //canny edge detection specification
#include "RSA.h"   //RSA algorithm implementation.
#include "lenna.h" //the test image is hardcoded here.

/*my functions*/
bool createfile(unsigned char* imgbmp, uint32_t arraysize);
bool encryptimage(char* imageName, char* encryptedImageName);
bool decryptimage(char* imageName, char* decryptedImageName);
bool BmpEqual(char* imageName, char* imageName2);
int  checkimagesize(char* imagefileName, bool verbose);
bool DoEdgeDetection(char* filename);
bool checkEncryptDecrypt(char* filename);
void GoToBaseDirectory(void);
void SystemMonitor(void);
bool createTCPSocket(xSocket_t *xClientSocket, TickType_t xTimeOut, struct freertos_sockaddr *xBindAddress);
bool SendFile(char* filename, xSocket_t* xClientSocket, struct freertos_sockaddr xDestinationAddress);
void StreamEncryptedFrame(void);

/*my task prototypes*/
static void EdgeDetectionTask(void);
static void EdgeDetection_task(void);
/*help variables for tasks*/
BaseType_t xReturnedEdgeDetectionTask;
TaskHandle_t EdgeDetectionTask_handle = NULL;

static void EncryptAndStreamTask(void);
static void EncryptAndStream_task(void);
/*help variables for tasks*/
BaseType_t xReturnedEncryptAndStreamTask;
TaskHandle_t EncryptAndStreamTask_handle = NULL;

/*auxiliary to monitor the system performance*/
char TimeStats[3 * 1024]; //buffer to print the time stats

/* Run time and task stats gathering related definitions. */
#define configGENERATE_RUN_TIME_STATS           1	//to use vTaskGetRunTimeStats()
#define configUSE_TRACE_FACILITY                1
#define configUSE_STATS_FORMATTING_FUNCTIONS    1
#define configUSE_APPLICATION_TASK_TAG 1 // to use xTaskCallApplicationTaskHook()

extern volatile unsigned long ulHighFrequencyTimerTicks = 0;

extern void vConfigureTimerForRunTimeStats(void); /*defined in win32 port in Run-time-stats-utils.c*/
unsigned long ulGetRunTimeCounterValue(void); /*defined in win32 port in Run-time-stats-utils.c*/

#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() vConfigureTimerForRunTimeStats()
#define portGET_RUN_TIME_COUNTER_VALUE() ulGetRunTimeCounterValue()


/* UDP command server task parameters. */
//#define mainUDP_CLI_TASK_PRIORITY						( tskIDLE_PRIORITY )
//#define mainUDP_CLI_PORT_NUMBER							( 5001UL )

/* TCP command server task parameters.  The standard telnet port is used even
though this is not implementing a real telnet server. */
#define mainTCP_CLI_TASK_PRIORITY						( tskIDLE_PRIORITY )
#define mainTCP_CLI_PORT_NUMBER							( 23UL )

/* Simple UDP client and server task parameters. */
//#define mainSIMPLE_UDP_CLIENT_SERVER_TASK_PRIORITY		( tskIDLE_PRIORITY )
//#define mainSIMPLE_UDP_CLIENT_SERVER_PORT				( 5005UL )

/* Select UDP server task parameters. */
//#define mainUDP_SELECT_SERVER_TASK_PRIORITY				( tskIDLE_PRIORITY )
//#define mainUDP_SELECT_SERVER_PORT						( 30001UL )

/* Echo client task parameters - used for both TCP and UDP echo clients. */
#define mainECHO_CLIENT_TASK_STACK_SIZE 				( configMINIMAL_STACK_SIZE * 2 )
#define mainECHO_CLIENT_TASK_PRIORITY					( tskIDLE_PRIORITY + 1 )

/* FTP and HTTP servers execute in the TCP server work task. */
#define mainTCP_SERVER_TASK_PRIORITY					( tskIDLE_PRIORITY + 2 )
#define	mainTCP_SERVER_STACK_SIZE						1400 /* Not used in the Win32 simulator. */

/* TFTP server parameters. */
#define mainTFTP_SERVER_PRIORITY						( tskIDLE_PRIORITY + 1 )
#define mainTFTP_SERVER_STACK_SIZE						1400 /* Not used in the Win32 simulator. */

/* Dimensions the buffer used to send UDP print and debug messages. */
//#define cmdPRINTF_BUFFER_SIZE		512

/* The number and size of sectors that will make up the RAM disk.  The RAM disk
is huge to allow some verbose FTP tests. */
#define mainRAM_DISK_SECTOR_SIZE	512UL /* Currently fixed! */
#define mainRAM_DISK_SECTORS		( ( 5UL * 1024UL * 1024UL ) / mainRAM_DISK_SECTOR_SIZE ) /* 5M bytes. */
#define mainIO_MANAGER_CACHE_SIZE	( 15UL * mainRAM_DISK_SECTOR_SIZE )

/* Where the RAM disk is mounted. */
#define mainRAM_DISK_NAME			"/ram"

/* Define a name that will be used for LLMNR and NBNS searches. */
#define mainHOST_NAME				"RTOSDemo"
#define mainDEVICE_NICK_NAME		"windows_demo"

/* Set to 0 to run the STDIO examples once only, or 1 to create multiple tasks
that run the tests continuously. */
#define mainRUN_STDIO_TESTS_IN_MULTIPLE_TASK 0

/* Set the following constants to 1 or 0 to define which tasks to include and
exclude:

mainCREATE_FTP_SERVER:  When set to 1 the TCP server task will include an FTP
server.
See http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/FTP_Server.html

mainCREATE_HTTP_SERVER:  When set to 1 the TCP server task will include a basic
HTTP server.
See http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/HTTP_web_Server.html

mainCREATE_UDP_CLI_TASKS:  When set to 1 a command console that uses a UDP port
for input and output is created using FreeRTOS+CLI.  The port number used is set
by the mainUDP_CLI_PORT_NUMBER constant above.  A dumb UDP terminal such as YAT
can be used to connect.
See http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/UDP_CLI.html

mainCREATE_TCP_CLI_TASKS:  When set to 1 a command console that uses a TCP port
for input and output is created using FreeRTOS+CLI.  The port number used is set
by the mainTCP_CLI_PORT_NUMBER constant above.  A dumb UDP terminal such as YAT
can be used to connect.

mainCREATE_SIMPLE_UDP_CLIENT_SERVER_TASKS:  When set to 1 two UDP client tasks
and two UDP server tasks are created.  The clients talk to the servers.  One set
of tasks use the standard sockets interface, and the other the zero copy sockets
interface.  These tasks are self checking and will trigger a configASSERT() if
they detect a difference in the data that is received from that which was sent.
As these tasks use UDP, and can therefore loose packets, they will cause
configASSERT() to be called when they are run in a less than perfect networking
environment.
See http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/UDP_client_server.html

mainCREATE_SELECT_UDP_SERVER_TASKS: Uses two tasks to demonstrate the use of the
FreeRTOS_select() function.

mainCREATE_UDP_ECHO_TASKS:  When set to 1 a two tasks are created that send
UDP echo requests to the standard echo port (port 7).  One task uses the
standard socket interface, the other the zero copy socket interface.  The IP
address of the echo server must be configured using the configECHO_SERVER_ADDR0
to configECHO_SERVER_ADDR3 constants in FreeRTOSConfig.h.  These tasks are self
checking and will trigger a configASSERT() if the received echo reply does not
match the transmitted echo request.  As these tasks use UDP, and can therefore
loose packets, they will cause configASSERT() to be called when they are run in
a less than perfect networking environment, or when connected to an echo server
that (legitimately as UDP is used) opts not to reply to every echo request.
See http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/UDP_Echo_Clients.html

mainCREATE_TCP_ECHO_TASKS_SINGLE:  When set to 1 a set of tasks are created that
send TCP echo requests to the standard echo port (port 7), then wait for and
verify the echo reply, from within the same task (Tx and Rx are performed in the
same RTOS task).  The IP address of the echo server must be configured using the
configECHO_SERVER_ADDR0 to configECHO_SERVER_ADDR3 constants in
FreeRTOSConfig.h.
See http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/TCP_Echo_Clients.html

mainCREATE_TCP_ECHO_TASKS_SEPARATE:  As per the description for the
mainCREATE_TCP_ECHO_TASKS_SINGLE constant above, except this time separate tasks
are used to send data to and receive data from the echo server (one task is used
for Tx and another task for Rx, using the same socket).
See http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/TCP_Echo_Clients_Separate.html

mainCREATE_SIMPLE_TCP_ECHO_SERVER:  When set to 1 FreeRTOS tasks are used with
FreeRTOS+TCP to create a TCP echo server.  Echo clients are also created, but
the echo clients use Windows threads (as opposed to FreeRTOS tasks) and use the
Windows TCP library (Winsocks).  This creates a communication between the
FreeRTOS+TCP TCP/IP stack and the Windows TCP/IP stack.
See http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/TCP_Echo_Server.html
*/
#define mainCREATE_UDP_CLI_TASKS					0
#define mainCREATE_TCP_CLI_TASKS					1 //1
#define mainCREATE_SIMPLE_UDP_CLIENT_SERVER_TASKS	0
#define mainCREATE_SELECT_UDP_SERVER_TASKS			0 /* _RB_ Requires retest. */
#define mainCREATE_UDP_ECHO_TASKS					0
#define mainCREATE_TCP_ECHO_TASKS_SINGLE			0
#define mainCREATE_TCP_ECHO_TASKS_SEPARATE			0
#define mainCREATE_SIMPLE_TCP_ECHO_SERVER			0 //1
#define mainCREATE_FTP_SERVER						0
#define mainCREATE_HTTP_SERVER 						0
#define mainCREATE_TFTP_SERVER						0

/* Set the following constant to pdTRUE to log using the method indicated by the
name of the constant, or pdFALSE to not log using the method indicated by the
name of the constant.  Options include to standard out (mainLOG_TO_STDOUT), to a
disk file (mainLOG_TO_DISK_FILE), and to a UDP port (mainLOG_TO_UDP).  If
mainLOG_TO_UDP is set to pdTRUE then UDP messages are sent to the IP address
configured as the echo server address (see the configECHO_SERVER_ADDR0
definitions in FreeRTOSConfig.h) and the port number set by configPRINT_PORT in
FreeRTOSConfig.h. */
#define mainLOG_TO_STDOUT 		pdTRUE	
#define mainLOG_TO_DISK_FILE 	pdFALSE
#define mainLOG_TO_UDP 			pdFALSE

/*-----------------------------------------------------------*/

/*
 * Register commands that can be used with FreeRTOS+CLI through the UDP socket.
 * The commands are defined in CLI-commands.c and File-related-CLI-commands.c
 * respectively.
 */
extern void vRegisterCLICommands( void );
extern void vRegisterFileSystemCLICommands( void );

/*
 * A software timer is created that periodically checks that some of the TCP/IP
 * demo tasks are still functioning as expected.  This is the timer's callback
 * function.
 */
static void prvCheckTimerCallback( TimerHandle_t xTimer );

/*
 * Just seeds the simple pseudo random number generator.
 */
static void prvSRand( UBaseType_t ulSeed );

/*
 * Miscellaneous initialisation including preparing the logging and seeding the
 * random number generator.
 */
static void prvMiscInitialisation( void );

/*
 * Creates a RAM disk, then creates files on the RAM disk.  The files can then
 * be viewed via the FTP server and the command line interface.
 */
static void prvCreateDiskAndExampleFiles( void );

/*
 * Functions used to create and then test files on a disk.
 */
extern void vCreateAndVerifyExampleFiles( const char *pcMountPath );
extern void vStdioWithCWDTest( const char *pcMountPath );
extern void vMultiTaskStdioWithCWDTest( const char *const pcMountPath, uint16_t usStackSizeWords );

/*
 * The task that runs the FTP and HTTP servers.
 */
#if( ( mainCREATE_FTP_SERVER == 1 ) || ( mainCREATE_HTTP_SERVER == 1 ) )
	static void prvServerWorkTask( void *pvParameters );
#endif


/* The default IP and MAC address used by the demo.  The address configuration
defined here will be used if ipconfigUSE_DHCP is 0, or if ipconfigUSE_DHCP is
1 but a DHCP server could not be contacted.  See the online documentation for
more information. */
static const uint8_t ucIPAddress[ 4 ] = { configIP_ADDR0, configIP_ADDR1, configIP_ADDR2, configIP_ADDR3 };
static const uint8_t ucNetMask[ 4 ] = { configNET_MASK0, configNET_MASK1, configNET_MASK2, configNET_MASK3 };
static const uint8_t ucGatewayAddress[ 4 ] = { configGATEWAY_ADDR0, configGATEWAY_ADDR1, configGATEWAY_ADDR2, configGATEWAY_ADDR3 };
static const uint8_t ucDNSServerAddress[ 4 ] = { configDNS_SERVER_ADDR0, configDNS_SERVER_ADDR1, configDNS_SERVER_ADDR2, configDNS_SERVER_ADDR3 };

/* Default MAC address configuration.  The demo creates a virtual network
connection that uses this MAC address by accessing the raw Ethernet data
to and from a real network connection on the host PC.  See the
configNETWORK_INTERFACE_TO_USE definition for information on how to configure
the real network connection to use. */
const uint8_t ucMACAddress[ 6 ] = { configMAC_ADDR0, configMAC_ADDR1, configMAC_ADDR2, configMAC_ADDR3, configMAC_ADDR4, configMAC_ADDR5 };

/* The UDP address to which print messages are sent. */
static struct freertos_sockaddr xPrintUDPAddress;

/* Use by the pseudo random number generator. */
static UBaseType_t ulNextRand;

/* Handle of the task that runs the FTP and HTTP servers. */
static TaskHandle_t xServerWorkTaskHandle = NULL;

/*-----------------------------------------------------------*/

/*
 * NOTE: Some versions of Visual Studio will generate erroneous compiler
 * warnings about variables being used before they are set.
 */
int main( void )
{
const uint32_t ulLongTime_ms = 250UL, ulCheckTimerPeriod_ms = 15000UL;
TimerHandle_t xCheckTimer;
TimerHandle_t xSystemMonitorTimer;
	
	printf("Hello World!\n");

	/*
	 * Instructions for using this project are provided on:
	 * http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/examples_FreeRTOS_simulator.html
	 *
	 * NOTE: Some versions of Visual Studio will generate erroneous compiler
	 * warnings about variables being used before they are set.
	 */

	/* Miscellaneous initialisation including preparing the logging and seeding
	the random number generator. */
	prvMiscInitialisation();

	/* Initialise the network interface.

	***NOTE*** Tasks that use the network are created in the network event hook
	when the network is connected and ready for use (see the definition of
	vApplicationIPNetworkEventHook() below).  The address values passed in here
	are used if ipconfigUSE_DHCP is set to 0, or if ipconfigUSE_DHCP is set to 1
	but a DHCP server cannot be	contacted. */
	FreeRTOS_debug_printf( ( "FreeRTOS_IPInit\n" ) );
	FreeRTOS_IPInit( ucIPAddress, ucNetMask, ucGatewayAddress, ucDNSServerAddress, ucMACAddress );

	/* A timer is used to periodically check the example tasks are functioning
	as expected.  First create the software timer ... */
	xCheckTimer = xTimerCreate( "Check",				/* Text name used for debugging only. */
								pdMS_TO_TICKS( ulCheckTimerPeriod_ms ),
								pdTRUE,					/* This is an auto-reload timer. */
								NULL,					/* Parameter not used. */
								prvCheckTimerCallback ); /* The timer callback function. */
	
	/* ... assert if the timer was not created, ... */
	configASSERT( xCheckTimer );

	/* ... then start the timer. */
	xTimerStart( xCheckTimer, 0 );


	/* A timer is created to evaluate system task performances*/
	xSystemMonitorTimer = xTimerCreate("SystemTasks",		/* Text name used for debugging only. */
		pdMS_TO_TICKS(1000),    /*timer period is 1000ms to system ticks*/
		pdTRUE,					/* This is an auto-reload timer. */
		NULL,					/* timer id in case it is needed for identification */
		SystemMonitor); /* The timer callback function. */

	xTimerStart(xSystemMonitorTimer, 0);


	#if( ( mainCREATE_FTP_SERVER == 1 ) || ( mainCREATE_HTTP_SERVER == 1 ) )
	{
		/* Create the task that handles the FTP and HTTP servers.  This will
		initialise the file system then wait for a notification from the network
		event hook before creating the servers.  The task is created at the idle
		priority, and sets itself to mainTCP_SERVER_TASK_PRIORITY after the file
		system has initialised. */
		xTaskCreate( prvServerWorkTask, "SvrWork", mainTCP_SERVER_STACK_SIZE, NULL, tskIDLE_PRIORITY, &xServerWorkTaskHandle );
	}
	#endif

	/*launch my intended tasks:*/

	/* Create the RAM disk used by the FTP and HTTP servers. */
	prvCreateDiskAndExampleFiles();

	printf("\n\n----------------------");	
	printf("\nCheck basic functions:");	
	printf("\n----------------------");	fflush(stdout);

	// create my image of lenna.bmp
	printf("\n##sizearray: %d", sizeof(image128) / sizeof(image128[0]) ); 
	if(createfile(image128, sizeof(image128)/sizeof(image128[0])) == true) {printf("\nImage created OK");	} else{printf("\nImage created NOK"); }
	printf("\n#"); fflush(stdout);
	checkimagesize("lenna.bmp", true);
	//check edge detection function	
	if (DoEdgeDetection("lenna.bmp") == true) { printf("\nEdge detection OK"); }
	else { printf("\nEdge detection NOK"); }
	//checkimagesize("out.bmp", false);
	if (checkEncryptDecrypt("out.bmp") == true) { printf("\nEncryptDecript OK"); } else { printf("\nEncryptDecript NOK"); }

	Sleep(50);
	EdgeDetectionTask();
	Sleep(50);
	EncryptAndStreamTask();


	printf("\nNumber of tasks: %d\n", (int)uxTaskGetNumberOfTasks());
	printf("\nvTaskStartScheduler\n");	fflush(stdout);

	/* Start the RTOS scheduler. */
	//FreeRTOS_debug_printf( ("vTaskStartScheduler\n") );
	vTaskStartScheduler();

	checkimagesize("lenna.bmp", false);

	/* If all is well, the scheduler will now be running, and the following
	line will never be reached.  If the following line does execute, then
	there was insufficient FreeRTOS heap memory available for the idle and/or
	timer tasks	to be created.  See the memory management section on the
	FreeRTOS web site for more details (this is standard text that is not not
	really applicable to the Win32 simulator port). */
	for( ;; ) 
	{
		Sleep( ulLongTime_ms );
	}
}
/*-----------------------------------------------------------*/

bool DoEdgeDetection(char* filename)
{

	checkimagesize(filename, false);

	bitmap_info_header_t ih;
	const pixel_t* in_bitmap_data = load_bmp(filename, &ih);
	if (in_bitmap_data == NULL) {
		printf("main: BMP image not loaded.\n");
		return false;
	}

	//printf("Info: %d x %d x %d\n", ih.width, ih.height,(int)ih.bitspp);

	const pixel_t* out_bitmap_data =
		canny_edge_detection(in_bitmap_data, &ih, 40, 80, 1.0);
	if (out_bitmap_data == NULL) {
		printf("failed canny_edge_detection.\n");
		return false;
	}

	if (save_bmp("out.bmp", &ih, out_bitmap_data)) {
		printf("main: BMP image not saved.\n");
		return false;
	}
	else {
	//	printf("saved file out.bmp\n");
	}

	vPortFree((pixel_t*)in_bitmap_data);
	vPortFree((pixel_t*)out_bitmap_data);

	return true;
}


void ff_fopen_message(FF_FILE* pxFile, char* pcFileName)
{
	if (pxFile == NULL) { printf("Error when ff_fopen the file: %s\n", pcFileName);
	fflush(stdout); }
	else {/* printf("ff_fopen file %s\n", pcFileName);*/ }
}

void checkfileisBMP(char* filename,  bool verbose)
{
	BaseType_t xFileNumber;
	int32_t lItemsWritten = 0;
	FF_FILE* pxFile;
	char* pcBuffer, * pcFileName;
	const int BUFFER_SIZE = 10;
	int lReturn;
	FF_Stat_t xStat;
	int filesize = 0;

	pxFile = ff_fopen(filename, "r");
	ff_fopen_message(pxFile, filename);

	size_t xSize = sizeof(unsigned char);
	size_t xItems = 3; 
	char header[4]; memset(header, '0', 4);
	size_t numItemsreaded = 0;

	numItemsreaded = ff_fread(header, xSize, xItems, pxFile);

	if(ff_fclose(pxFile)==-1) { printf("\nErrono: %u in line: %d", (uint32_t)stdioGET_FF_ERROR(), __LINE__); }
	header[3] = '\0';
	if(verbose==true) printf("image header: %s", header);
	if (strcmp("BM6", header) == 0 && verbose == true) printf("It is an image\n"); 

	return true;
}

int checkimagesize(char* imagefileName, bool verbose)
{
	int lReturn;
	FF_Stat_t xStat;

	/* Find the length of the file with name pcFileName. */
	if (ff_stat(imagefileName, &xStat) == 0)
	{
		lReturn = xStat.st_size;
		if (verbose == true) { printf("\nThe size of the file: %s, is: %d\n", imagefileName, lReturn); fflush(stdout); }
	}
	else
	{/* Could not obtain the length of the file. */
		printf("\nCould not read the size of the file: %s\n", imagefileName); fflush(stdout);
		return 0;
	}
	return lReturn;
}

void GoToBaseDirectory(void)
{
	char pwd[50];

	/* Ensure in the root of the mount being used. */
	int lResult = ff_chdir(mainRAM_DISK_NAME);
	configASSERT(lResult >= 0);

	if (ff_getcwd(pwd, 50) != NULL)
	{
		printf("\nthe current directory is: ");
		printf(pwd);
		printf("\n"); fflush(stdout);
	}
}

bool createfile(unsigned char *imgbmp, uint32_t arraysize)
{
	//This function will automatically create the lenna.bmp file
	char pwd[50];
	if ( ff_getcwd(pwd, 50) != NULL)
	{
		printf("\nthe current directory is: "); 
		printf(pwd);
		printf("\n"); fflush(stdout);
	}

	GoToBaseDirectory();

	BaseType_t xFileNumber;
	int32_t lItemsWritten = 0;
	FF_FILE* pxFile;
	char* pcRAMBuffer, * pcFileName;
	const int RAM_BUFFER_SIZE = 200;

	/* Allocate buffers used to hold date written to/from the disk, and the
	file names. */
	pcRAMBuffer = (char*)pvPortMalloc(RAM_BUFFER_SIZE);
	pcFileName = (char*)pvPortMalloc(250);
	configASSERT(pcRAMBuffer);
	configASSERT(pcFileName);

	/* Generate a file name. */
	xFileNumber = 1;
	sprintf(pcFileName, "%s", "lenna.bmp");

	/* Open the file, creating the file if it does not already exist. */
	pxFile = ff_fopen(pcFileName, "w");	ff_fopen_message(pxFile, pcFileName); 
	configASSERT(pxFile);
	int numelem = arraysize;
	//printf("numelem: %d\n", numelem); fflush(stdout);
	int maxcount = numelem / RAM_BUFFER_SIZE;
	int resto = numelem % RAM_BUFFER_SIZE;
	int count = 0; 

	for ( count = 0; count < maxcount; count++)
	{   //beware pointer arithmetic!!
		memcpy(pcRAMBuffer, (int)(imgbmp + count*RAM_BUFFER_SIZE), RAM_BUFFER_SIZE);
		lItemsWritten += ff_fwrite( pcRAMBuffer, sizeof(unsigned char), RAM_BUFFER_SIZE, pxFile );
		if (lItemsWritten != RAM_BUFFER_SIZE*(count+1)) {
			printf("error when writting the image\n"); fflush(stdout);
				break;
		}
		//if (count == 0) { printf("\nIMAGE: %s", pcRAMBuffer); fflush(stdout); } //This would print BM6 in case of bmp image
	}
	if (resto > 0)
	{
		memcpy(pcRAMBuffer, (int)(imgbmp + count * RAM_BUFFER_SIZE), resto);
		lItemsWritten += ff_fwrite(pcRAMBuffer, sizeof(unsigned char), resto, pxFile);
		if (lItemsWritten != (resto + maxcount*RAM_BUFFER_SIZE))
		{
			printf("error when writting the image2\n"); fflush(stdout);
		}
	}

	//printf("total items written: %d\n", lItemsWritten); fflush(stdout); 

	/* Close the file */
	if( ff_fclose(pxFile) == -1) { printf("error when closing the file: %s\n", pcFileName); fflush(stdout); }

	printf("\nCreated lenna.bmp\n"); fflush(stdout);

	checkimagesize(pcFileName, false);

	checkfileisBMP(pcFileName, false);

	//free the memory of the image.-
	vPortFree(pcRAMBuffer);
	vPortFree(pcFileName);
	
	return true;
}

void SystemMonitor(void)
{
	static long int counter = 0;
	/*This task just prints out the system task timings and cpu usage*/
	 /* ref: https://www.freertos.org/rtos-run-time-stats.html */
	printf("\n\nseconds: %lu - vTaskGetRunTimeStats():", counter);
	counter++;
	vTaskGetRunTimeStats(TimeStats);
	printf("\n\n%s", TimeStats);
	fflush(stdout);

}

bool encryptimage(char* imageName, char *encryptedimage)
{ //this function will encrypt with RSA the image given.
	bool result =  false;

	FF_FILE* pxFile;
	FF_FILE * pxFileEncrypted;
	unsigned int filesize = 0;

	filesize = checkimagesize(imageName, false);

	//check if the image exits in the current directory
	/* Open the file, creating the file if it does not already exist. */
	pxFile = ff_fopen(imageName, "r");	ff_fopen_message(pxFile, imageName);

	//create the name of the encripted file
	char* encryptedfilename = encryptedimage;

	/* Create or overwrite a writable file. */
	pxFileEncrypted = ff_fopen(encryptedfilename, "w"); 
	ff_fopen_message(pxFileEncrypted, encryptedfilename);

	unsigned int maxloop = filesize / 100; // 100 is the size of msg[100]
	unsigned int remain = filesize % 100;
	//crypt key values
	p = 5; q = 11; 
	n = p * q;
	t = (p - 1) * (q - 1);
	ce();

	size_t xSize = sizeof(unsigned char); 
	size_t xItems = 100; //because this is the size of msg[100]
	size_t numItemsreaded = 0; 

	unsigned int counter = 0;
	for (counter = 0; counter < maxloop; counter++)
	{
		numItemsreaded += ff_fread(msg, xSize,xItems,pxFile);
		//printf("readed: %s\n", msg);
		if (numItemsreaded != ((counter + 1) * xItems)) { printf("error when reading the file"); break; }
		encrypt();
		size_t writtenelem = ff_fwrite(en, xSize, xItems, pxFileEncrypted);
		if ((int)writtenelem != 100) 
		{	//check the number of written elements.
			printf("error when writting the file: %s; expected 100 elems and found: %d\n", encryptedfilename,(int) writtenelem); fflush(stdout); break;	
		}
	}
	if (remain > 0)
	{
		numItemsreaded += ff_fread(msg + counter * 100, xSize, remain, pxFile);
		encrypt();
		int writtenelem = ff_fwrite(en, xSize, remain, pxFileEncrypted);
		if (writtenelem != remain)
		{  printf("error when writting the file: %s\n", encryptedfilename); fflush(stdout); }
	}
	if (ff_fclose(pxFile) == -1) { printf("error when closing the file: %s\n", imageName); { printf("\nErrono: %u, %s ,%d", (uint32_t)stdioGET_FF_ERROR(), __FUNCTION__, __LINE__); } fflush(stdout); }
	if (ff_fclose(pxFileEncrypted) == -1) { printf("error when closing the file: %s\n", encryptedfilename); { printf("\nErrono: %u", (uint32_t)stdioGET_FF_ERROR()); }fflush(stdout); }

	/* Find the length of the encriptedfile */
	//filesize = checkimagesize(encryptedfilename, false);

	//printf("Encription finished");
	result = true; return result;
} //end of encrypt image


bool decryptimage(char* imageName, char* decryptedImageName)
{ //this function will decrypt with RSA the image given.
  //the input file will be the encripted file to decrytp
	bool result = false;

	FF_FILE* pxFile;
	FF_FILE* pxFileDecrypted;
	unsigned int filesize = 0;

	filesize = checkimagesize(imageName, false);

	pxFile = ff_fopen(imageName, "r");	ff_fopen_message(pxFile, imageName);

	//create the name of the encripted file
	char* encryptedfilename = decryptedImageName;

	/* Create or overwrite a writable file. */
	pxFileDecrypted = ff_fopen(encryptedfilename, "w+"); 
	ff_fopen_message(pxFileDecrypted, encryptedfilename);

	//crypt key values
	p = 5; q = 11;

	size_t xSize = sizeof(unsigned char);
	size_t xItems = 100; //because this is the size of msg[100]
	size_t numItemsreaded = 0;

	unsigned int counter = 0;
	unsigned int maxloop = filesize / 100; // 100 is the size of msg[100]
	for (counter = 0; counter < maxloop; counter++)
	{
		numItemsreaded += ff_fread(en, xSize, xItems, pxFile);
		//printf("readed: %s\n", msg);
		if (numItemsreaded != ((counter + 1) * xItems)) { printf("error when reading the file"); break; }
		decrypt();
		size_t writtenelem = ff_fwrite(m, xSize, xItems, pxFileDecrypted);
		if ((int)writtenelem != 100)
		{	//check the number of written elements.
			printf("error when writting the file: %s; expected 100 elems and found: %d\n", encryptedfilename, (int)writtenelem); fflush(stdout); break;
		}
	}
	unsigned int remain = filesize % 100;
	if (remain > 0)
	{
		numItemsreaded += ff_fread(msg + counter * 100, xSize, remain, pxFile);
		encrypt();
		int writtenelem = ff_fwrite(en, xSize, remain, pxFileDecrypted);
		if (writtenelem != remain)
		{
			printf("error when writting the file: %s\n", encryptedfilename); fflush(stdout);
		}
	}
	if (ff_fclose(pxFile) == -1) { printf("error when closing the file: %s\n", imageName); fflush(stdout); }
	if (ff_fclose(pxFileDecrypted) == -1) { printf("error when closing the file: %s\n", encryptedfilename); fflush(stdout); }

	/* Find the length of the encriptedfile */
	filesize = checkimagesize(encryptedfilename, false);

	//printf("Decription finished");
	result = true; return result;
} //end of dencrypt image

bool checkEncryptDecrypt(char* imageName)
{ //this function will encrypt with RSA the image given.
	bool result = false;

	FF_FILE* pxFile;
	unsigned int filesize = 0;

	filesize = checkimagesize(imageName, false);

	//check if the image exits in the current directory
	/* Open the file, creating the file if it does not already exist. */
	pxFile = ff_fopen(imageName, "r");	ff_fopen_message(pxFile, imageName);

	unsigned int maxloop = filesize / 100; // 100 is the size of msg[100]
	unsigned int remain = filesize % 100;
	//crypt key values
	p = 5; q = 11;
	n = p * q;
	t = (p - 1) * (q - 1);
	ce();

	size_t xSize = sizeof(unsigned char);
	size_t xItems = 100; //because this is the size of msg[100]
	size_t numItemsreaded = 0;

	unsigned int counter = 0;
	char msgin[100];
	char msenc[100];
	char msgout[100];
	char msgencry2[100];
	long int en1[100];
	long int en2[100];
	for (counter = 0; counter < maxloop; counter++)
	{
		numItemsreaded += ff_fread(msg, xSize, xItems, pxFile);
		if (numItemsreaded != ((counter + 1) * xItems)) { printf("\nError when reading the file"); break; }
		for (int count = 0; count < 100; count++) { m[count]= msgin[count] = msg[count];  };
		encrypt();
		for (int count = 0; count < 100; count++) { en1[count] = en[count]; }; //get partial result
		decrypt();	
		encrypt();
		for (int count = 0; count < 100; count++) { en2[count] = en[count]; }; //get partial result
		if (strcmp(en1, en2) != 0)
		{ printf("\nWrong encrypt-decrypt process"); return false; }
	}
	if (remain > 0)
	{
		numItemsreaded += ff_fread(msg + counter * 100, xSize, remain, pxFile);
		for (int count = 0; count < 100; count++) { msgin[count] = m[count] = msg[count]; };
		encrypt();
		for (int count = 0; count < 100; count++) { en1[count] = en[count]; }; //get partial result
		decrypt();

		encrypt();
		for (int count = 0; count < 100; count++) { en2[count] = en[count]; }; //get partial result
		if (strcmp(en1, en2) != 0) { printf("\nWrong encrypt-decrypt process2"); return false; }
	}
	if (ff_fclose(pxFile) == -1) { printf("\nError when closing the file: %s\n", imageName);
	 printf("\nErrono: %u, %s ,%d", (uint32_t)stdioGET_FF_ERROR(), __FUNCTION__, __LINE__); 
	 fflush(stdout); }
	
	//printf("Encription-Decrypt finished");
	result = true;
	return result;
} //end of encrypt image


bool BmpEqual(char* imageName, char* imageName2)
{ //this function will check if the given bmps images are equal.
	bool result = false;

	FF_FILE* pxFile;
	FF_FILE* pxFile2;
	unsigned int filesize = 0;
	unsigned int filesize2 = 0;

	filesize = checkimagesize(imageName, false);
	filesize2 = checkimagesize(imageName2, false);

	if (filesize != filesize2)
	{
		printf("images are not equal: %s != %s", imageName, imageName2);
		return false;
	}

	//check if the image exits in the current directory
	pxFile = ff_fopen(imageName, "r");	ff_fopen_message(pxFile, imageName);
	pxFile2 = ff_fopen(imageName2, "r");	ff_fopen_message(pxFile2, imageName2);


	size_t xSize = sizeof(unsigned char);
	size_t xItems = 100; //because this is the size of msg[100]
	size_t numItemsreaded1 = 0;
	size_t numItemsreaded2 = 0;
	char buffer1[100];
	char buffer2[100];

	unsigned int counter = 0;
	unsigned int maxloop = filesize / 100; // 100 is the size of msg[100]
	for (counter = 0; counter < maxloop; counter++)
	{
		numItemsreaded1 += ff_fread(buffer1, xSize, xItems, pxFile);
		numItemsreaded2 += ff_fread(buffer2, xSize, xItems, pxFile2);
		
		if (numItemsreaded1 != ((counter + 1) * xItems)) {
			printf("error when reading the file\n"); break; }
		if (numItemsreaded2 != ((counter + 1) * xItems)) {
			printf("error when reading the file2\n"); break; }

		if (memcmp(buffer1, buffer2, 100) != 0) {
			printf(">>the bmps are not equal!\n"); fflush(stdout); return false;
		}
	}
	unsigned int remain = filesize % 100;
	if (remain > 0)
	{
		numItemsreaded1 += ff_fread(buffer1, xSize, remain, pxFile);
		numItemsreaded2 += ff_fread(buffer2, xSize, remain, pxFile2);
		
		if (numItemsreaded1 != (remain + (counter) * xItems))
		{ printf("error when reading the file\n"); }
		if (numItemsreaded2 != (remain + (counter) * xItems))
		{ printf("error when reading the file2\n");  }

		if (memcmp(buffer1, buffer2, remain) != 0)
		{printf("the bmps are not equal!"); fflush(stdout); return false;}
	}
	if (ff_fclose(pxFile) == -1) { printf("error when closing the file: %s\n", imageName); { printf("\nErrono: %u, %s ,%d", (uint32_t)stdioGET_FF_ERROR(), __FUNCTION__, __LINE__); }fflush(stdout); }
	if (ff_fclose(pxFile2) == -1) { printf("error when closing the file: %s\n", imageName2); { printf("\nErrono: %u, %s ,%d", (uint32_t)stdioGET_FF_ERROR(), __FUNCTION__, __LINE__); } fflush(stdout); }

	//printf("BMPS are equal: %s - %s\n", imageName, imageName2);
	result = true; return result;
} //end of BmpEqual


bool createTCPSocket(xSocket_t *xClientSocket, TickType_t xTimeOut, struct freertos_sockaddr *xDestinationAddress)
{
	bool result = false;
	socklen_t xSize = sizeof(xSocket_t);

	/* Attempt to open the socket. */
	*xClientSocket = FreeRTOS_socket(PF_INET,
		SOCK_STREAM,  /* SOCK_STREAM for TCP. */
		IPPROTO_TCP);

	/* Check the socket was created successfully. */
	if (*xClientSocket != FREERTOS_INVALID_SOCKET)
	{
		/* The socket was created successfully and can now be used to connect to
		   a remote socket using FreeRTOS_connect(), before sending data using
		   FreeRTOS_send().  Alternatively the socket can be bound to a port using
		   FreeRTOS_bind(), before listening for incoming connections using
		   FreeRTOS_listen(). */

		/* Set send and receive time outs. */
		FreeRTOS_setsockopt(*xClientSocket,
			0,
			FREERTOS_SO_RCVTIMEO,
			&xTimeOut,
			sizeof(xTimeOut));

		FreeRTOS_setsockopt(*xClientSocket,
			0,
			FREERTOS_SO_SNDTIMEO,
			&xTimeOut,
			sizeof(xTimeOut));

		/* The socket was created successfully and can now be used to send data
		using the FreeRTOS_sendto() API function.  Sending to a socket that has
		not first been bound will result in the socket being automatically bound
		to a port number.  Use FreeRTOS_bind() to bind the socket to a
		specific port number.  This example binds the socket to port 9999.  The
		port number is specified in network byte order, so FreeRTOS_htons() is
		used. */
		/*xDestinationAddress.sin_port = FreeRTOS_htons(9999);*/

		/* Bind the socket, but pass in NULL to let FreeRTOS+TCP choose the port number. */
		if (FreeRTOS_bind(*xClientSocket, NULL, xSize) == 0)
		{

			/* Fill in the destination address and port number, which in this case is
			port 1024 on IP address 192.168.0.100. */

			xDestinationAddress->sin_addr = FreeRTOS_inet_addr_quick(192, 168, 0, 100);
			xDestinationAddress->sin_port = FreeRTOS_htons(1024);

			/* The bind was successful. */
			printf("The socket bind was successful"); 
			/*https://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_UDP/API/sendto.html*/
			/*https://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/TCP_Networking_Tutorial_Sending_TCP_Data.html*/
			
			result = true;
		}

	}else {
		printf("There was insufficient FreeRTOS heap memory available for the socket to be created."); fflush(stdout);
	}

	return false;
}

bool SendFile(char* filename, xSocket_t *xClientSocket, struct freertos_sockaddr xDestinationAddress)
{

    bool result = false;

	if( pdFALSE == FreeRTOS_IsNetworkUp() );
	{
		printf("\nthe network is down");
			return false;
	}

	if (pdFALSE == FreeRTOS_issocketconnected(*xClientSocket) ) 
	{	
		printf("\nthe given socket was not open"); 
		return false;
	};

	FF_FILE* pxFile;
	FF_FILE* pxFileEncrypted;
	unsigned int filesize = 0;

	filesize = checkimagesize(filename, false);

	//check if the image exits in the current directory
	/* Open the file, creating the file if it does not already exist. */
	pxFile = ff_fopen(filename, "r");	ff_fopen_message(pxFile, filename);

	/* Note – the task stack must be big enough to hold this array!. */
	uint8_t ucBuffer[100];
	uint32_t iReturned; 

	unsigned int maxloop = filesize / 100;
	unsigned int remain = filesize % 100;

	size_t xSize = sizeof(unsigned char);
	size_t xItems = 100; 
	size_t numItemsreaded = 0;

	unsigned int counter = 0;
	for (counter = 0; counter < maxloop; counter++)
	{
		numItemsreaded += ff_fread(ucBuffer, xSize, xItems, pxFile);
		//printf("readed: %s\n", msg);
		if (numItemsreaded != ((counter + 1) * xItems)) { printf("error when reading the file"); break; }

		/* Send the buffer with ulFlags set to 0, so the FREERTOS_ZERO_COPY bit
			is clear. */
		iReturned = FreeRTOS_sendto(
			/* The socket being send to. */
			*xClientSocket,
			/* The data being sent. */
			ucBuffer,
			/* The length of the data being sent. */
			100,
			/* ulFlags with the FREERTOS_ZERO_COPY bit clear. */
			0,
			/* Where the data is being sent. */
			&xDestinationAddress,
			/* Not used but should be set as shown. */
			sizeof(xDestinationAddress)
		);

		if (iReturned == 100)
		{
			/* The data was successfully queued for sending.  100 bytes will have
			been copied out of ucBuffer and into a buffer inside the IP stack.
			ucBuffer can be re-used now. */
		}
		else
		{	//check the number of written elements.
			printf("error when sending the file: %s; expected 100 elems and found: %d\n", filename, (int)iReturned); fflush(stdout); break;
		}
	}
	if (remain > 0)
	{
		numItemsreaded += ff_fread(msg + counter * 100, xSize, remain, pxFile);


		/* Send the buffer with ulFlags set to 0, so the FREERTOS_ZERO_COPY bit
	is clear. */
		iReturned = FreeRTOS_sendto(
			/* The socket being send to. */
			*xClientSocket,
			/* The data being sent. */
			ucBuffer,
			/* The length of the data being sent. */
			remain,
			/* ulFlags with the FREERTOS_ZERO_COPY bit clear. */
			0,
			/* Where the data is being sent. */
			&xDestinationAddress,
			/* Not used but should be set as shown. */
			sizeof(xDestinationAddress)
		);

		if (iReturned == remain)
		{
			/* The data was successfully queued for sending.  100 bytes will have
			been copied out of ucBuffer and into a buffer inside the IP stack.
			ucBuffer can be re-used now. */
		}
		else
		{	//check the number of written elements.
			printf("error2 when sending the file: %s; expected : %d\n", filename, (int)remain); fflush(stdout); 
		}

	}
	if (ff_fclose(pxFile) == -1) { printf("error when closing the file: %s\n", filename); 
	printf("\nErrono: %u, %s ,%d", (uint32_t)stdioGET_FF_ERROR(), __FUNCTION__, __LINE__);  fflush(stdout); }

	result = true;
	return result;
}

void StreamEncryptedFrame(void)
{
	/*https://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_UDP/API/socket.html*/
	/*https://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_UDP/API/FreeRTOS_IPInit.html*/
	/*https://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/TCP_Networking_Tutorial_TCP_Client_and_Server.html*/

	/* Variable to hold the created socket. */
	xSocket_t xClientSocket;
	socklen_t xSize = sizeof(xSocket_t);
	struct freertos_sockaddr xBindAddress;
	TickType_t xTimeOut = pdMS_TO_TICKS(2000);

	/* Attempt to open the socket. */
	 xClientSocket = FreeRTOS_socket(PF_INET,
									SOCK_STREAM,  /* SOCK_STREAM for TCP. */
									IPPROTO_TCP);


	/* Check the socket was created successfully. */
	if (xClientSocket != FREERTOS_INVALID_SOCKET)
	{

		/* Set send and receive time outs. */
		FreeRTOS_setsockopt(xClientSocket,
			0,
			FREERTOS_SO_RCVTIMEO,
			&xTimeOut,
			sizeof(xTimeOut));

		FreeRTOS_setsockopt(xClientSocket,
			0,
			FREERTOS_SO_SNDTIMEO,
			&xTimeOut,
			sizeof(xTimeOut));

		/* The socket was created successfully and can now be used to send data
		using the FreeRTOS_sendto() API function.  Sending to a socket that has
		not first been bound will result in the socket being automatically bound
		to a port number.  Use FreeRTOS_bind() to bind the socket to a
		specific port number.  This example binds the socket to port 9999.  The
		port number is specified in network byte order, so FreeRTOS_htons() is
		used. */
		xBindAddress.sin_port = FreeRTOS_htons(9999);

		/* Bind the socket, but pass in NULL to let FreeRTOS+TCP choose the port number. */
		if (FreeRTOS_bind(xClientSocket, NULL, xSize) == 0)
		{
			/* The bind was successful. */
			
		    /*https://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_UDP/API/sendto.html*/
			/*https://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/TCP_Networking_Tutorial_Sending_TCP_Data.html*/

			/* Note – the task stack must be big enough to hold this array!. */
			uint8_t ucBuffer[128];
			struct freertos_sockaddr xDestinationAddress;
			int32_t iReturned;

			/* Fill in the destination address and port number, which in this case is
			port 1024 on IP address 192.168.0.100. */
			xDestinationAddress.sin_addr = FreeRTOS_inet_addr_quick(192, 168, 0, 100);
			xDestinationAddress.sin_port = FreeRTOS_htons(1024);

			/* The local buffer is filled with the data to be sent, in this case it is
			just filled with 0xff. */
			memset(ucBuffer, 0xff, 128);

			/* Send the buffer with ulFlags set to 0, so the FREERTOS_ZERO_COPY bit
			is clear. */
			iReturned = FreeRTOS_sendto(
				/* The socket being send to. */
				xClientSocket,
				/* The data being sent. */
				ucBuffer,
				/* The length of the data being sent. */
				128,
				/* ulFlags with the FREERTOS_ZERO_COPY bit clear. */
				0,
				/* Where the data is being sent. */
				&xDestinationAddress,
				/* Not used but should be set as shown. */
				sizeof(xDestinationAddress)
			);

			if (iReturned == 128)
			{
				/* The data was successfully queued for sending.  128 bytes will have
				been copied out of ucBuffer and into a buffer inside the IP stack.
				ucBuffer can be re-used now. */
			}

		}
	}
	else
	{
		/* There was insufficient FreeRTOS heap memory available for the socket
		to be created. */
		printf("There was insufficient FreeRTOS heap memory available for the socket to be created.");
	}
}

/*Create EdgeDetectionTask */
void EdgeDetectionTask(void)
{
	/* Create the task, storing the handle. */
	xReturnedEdgeDetectionTask = xTaskCreate(
		EdgeDetection_task,  /* Function that implements the task. */
		(signed char*)"EdgeDetectionTask", /* Text name for the task. */
		1000, /* Stack size in words, not bytes. */
		NULL, /* Parameter passed into the task. */
		3, /* The priority at which the created task will execute*/
		&EdgeDetectionTask_handle);  /* Used to pass out the created task's handle. */

	if (xReturnedEdgeDetectionTask == pdPASS)
	{
		/* The task was created.  Use the task's handle to delete the task. */
		//vTaskDelete(matrix_handle);
		UBaseType_t prio = uxTaskPriorityGet(EdgeDetectionTask_handle);
		printf("\nSUCCEDD EdgeDetectionTask ... with prio: %d", (int)prio);	fflush(stdout);
	}
	else if (xReturnedEdgeDetectionTask == pdFAIL) {
		printf("\nFAILURE EdgeDetectionTask ");	fflush(stdout);
		/*Use the task's handle to delete the task. */
		vTaskDelete(EdgeDetectionTask_handle);
	}
	else
	{	printf("\nweird state EdgeDetectionTask"); fflush(stdout);
		vTaskDelete(EdgeDetectionTask_handle);
	}
}

static void EdgeDetection_task()
{
	GoToBaseDirectory();
	printf("Edge Detection task started\n"); fflush(stdout);

	if (createfile(image128, sizeof(image128) / sizeof(image128[0])) == true) { printf("\nImage created OK"); }
    else { printf("\nImage created NOK"); }

	while (1) {
		//printf("\nEdge Detection task --\n");

	   if (DoEdgeDetection("lenna.bmp") == true) { printf("\nEdge detection OK"); }
	   else { printf("\nEdge detection NOK"); }

	   
		/* Send a notification to prvTask2(), bringing it out of the Blocked state. */
		xTaskNotifyGive(EncryptAndStreamTask_handle);

		/* Block to wait for other task, to notify this task. */
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

		//fflush(stdout);
		//vTaskDelay(100);
	}
}

void EncryptAndStreamTask(void)
{
	/* Create the task, storing the handle. */
	xReturnedEncryptAndStreamTask = xTaskCreate(
		EncryptAndStream_task,  /* Function that implements the task. */
		(signed char*)"EncryptAndStreamTask", /* Text name for the task. */
		1000, /* Stack size in words, not bytes. */
		NULL, /* Parameter passed into the task. */
		3, /* The priority at which the created task will execute*/
		&EncryptAndStreamTask_handle);  /* Used to pass out the created task's handle. */

	if (xReturnedEncryptAndStreamTask == pdPASS)
	{
		/* The task was created.  Use the task's handle to delete the task. */
		//vTaskDelete(matrix_handle);
		UBaseType_t prio = uxTaskPriorityGet(EncryptAndStreamTask_handle);
		printf("\nSUCCEDD EncryptAndStreamTask ... with prio: %d", (int)prio);	fflush(stdout);
	}
	else if (xReturnedEncryptAndStreamTask == pdFAIL) {
		printf("\nFAILURE EncryptAndStreamTask ");	fflush(stdout);
		/*Use the task's handle to delete the task. */
		vTaskDelete(EncryptAndStreamTask_handle);
	}
	else
	{
		printf("\nweird state EncryptAndStreamTask"); fflush(stdout);
		vTaskDelete(EncryptAndStreamTask_handle);
	}
}

static void EncryptAndStream_task()
{
	GoToBaseDirectory();
	printf("Edge EncryptAndStreamTask started\n"); fflush(stdout);

	xSocket_t xClientSocket;
	struct freertos_sockaddr xDestinationAddress = { 0,0,0,0 };
	TickType_t xTimeOut = pdMS_TO_TICKS(2000);
	bool socketcreated = false;

	//for (uint8_t counter = 0; counter < 10 || socketcreated == true; i++)
	/*while (pdFALSE == FreeRTOS_IsNetworkUp())
	{	
		// Block to wait for prvTask2() to notify this task. 
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		// Send a notification to the other task, bringing it out of the Blocked state. 
		xTaskNotifyGive(EdgeDetectionTask_handle);
	}*/

	{ socketcreated = createTCPSocket(&xClientSocket, xTimeOut, &xDestinationAddress); }

	while (1) {

		//if( pdTRUE == FreeRTOS_IsNetworkUp() )
		{
			if( encryptimage("out.bmp", "encrypted") == true) { printf("\nEncryption OK"); }
			else { printf("\nnEncryption NOK"); }
			//vTaskDelay(100);

			SendFile("encrypted", &xClientSocket, xDestinationAddress);
		}
		/*else
		{
			printf("\nthe network is down");
		}*/

		/* Block to wait for prvTask2() to notify this task. */
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

		/* Send a notification to the other task, bringing it out of the Blocked state. */
		xTaskNotifyGive(EdgeDetectionTask_handle);
	}
}

static void prvCreateDiskAndExampleFiles( void )
{
static uint8_t ucRAMDisk[ mainRAM_DISK_SECTORS * mainRAM_DISK_SECTOR_SIZE ];
FF_Disk_t *pxDisk;

	/* Create the RAM disk. */
	pxDisk = FF_RAMDiskInit( mainRAM_DISK_NAME, ucRAMDisk, mainRAM_DISK_SECTORS, mainIO_MANAGER_CACHE_SIZE );
	configASSERT( pxDisk );

	/* Print out information on the disk. */
	FF_RAMDiskShowPartition( pxDisk );

	/* Create a few example files on the disk.  These are not deleted again. */
	vCreateAndVerifyExampleFiles( mainRAM_DISK_NAME );

	/* A few sanity checks only - can only be called after
	vCreateAndVerifyExampleFiles(). */
	#if( mainRUN_STDIO_TESTS_IN_MULTIPLE_TASK == 1 )
	{
		/* Note the stack size is not actually used in the Windows port. */
		vMultiTaskStdioWithCWDTest( mainRAM_DISK_NAME, configMINIMAL_STACK_SIZE * 2U );
	}
	#else
	{
		vStdioWithCWDTest( mainRAM_DISK_NAME );
	}
	#endif
}
/*-----------------------------------------------------------*/

#if( ( mainCREATE_FTP_SERVER == 1 ) || ( mainCREATE_HTTP_SERVER == 1 ) )

	static void prvServerWorkTask( void *pvParameters )
	{
	TCPServer_t *pxTCPServer = NULL;
	const TickType_t xInitialBlockTime = pdMS_TO_TICKS( 200UL );

	/* A structure that defines the servers to be created.  Which servers are
	included in the structure depends on the mainCREATE_HTTP_SERVER and
	mainCREATE_FTP_SERVER settings at the top of this file. */
	static const struct xSERVER_CONFIG xServerConfiguration[] =
	{
		#if( mainCREATE_HTTP_SERVER == 1 )
				/* Server type,		port number,	backlog, 	root dir. */
				{ eSERVER_HTTP, 	80, 			12, 		configHTTP_ROOT },
		#endif

		#if( mainCREATE_FTP_SERVER == 1 )
				/* Server type,		port number,	backlog, 	root dir. */
				{ eSERVER_FTP,  	21, 			12, 		"" }
		#endif
	};

		/* Remove compiler warning about unused parameter. */
		( void ) pvParameters;

		/* Create the RAM disk used by the FTP and HTTP servers. */
		prvCreateDiskAndExampleFiles();
		printf("ram disk created\n");	fflush(stdout);

		// create my image of lenna.bmp
		createfile(image);
		encryptimage("lenna.bmp");

		/* The priority of this task can be raised now the disk has been
		initialised. */
		vTaskPrioritySet( NULL, mainTCP_SERVER_TASK_PRIORITY );

		/* If the CLI is included in the build then register commands that allow
		the file system to be accessed. */
		#if( ( mainCREATE_UDP_CLI_TASKS == 1 ) || ( mainCREATE_TCP_CLI_TASKS == 1 ) )
		{
			vRegisterFileSystemCLICommands();
		}
		#endif /* mainCREATE_UDP_CLI_TASKS */


		/* Wait until the network is up before creating the servers.  The
		notification is given from the network event hook. */
		ulTaskNotifyTake( pdTRUE, portMAX_DELAY );

		/* Create the servers defined by the xServerConfiguration array above. */
		pxTCPServer = FreeRTOS_CreateTCPServer( xServerConfiguration, sizeof( xServerConfiguration ) / sizeof( xServerConfiguration[ 0 ] ) );
		configASSERT( pxTCPServer );

		for( ;; )
		{
			FreeRTOS_TCPServerWork( pxTCPServer, xInitialBlockTime );
		}
	}

#endif /* ( ( mainCREATE_FTP_SERVER == 1 ) || ( mainCREATE_HTTP_SERVER == 1 ) ) */
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
const uint32_t ulMSToSleep = 1;

	/* This is just a trivial example of an idle hook.  It is called on each
	cycle of the idle task if configUSE_IDLE_HOOK is set to 1 in
	FreeRTOSConfig.h.  It must *NOT* attempt to block.  In this case the
	idle task just sleeps to lower the CPU usage. */
	Sleep( ulMSToSleep );
}
/*-----------------------------------------------------------*/

void vAssertCalled( const char *pcFile, uint32_t ulLine )
{
const uint32_t ulLongSleep = 1000UL;
volatile uint32_t ulBlockVariable = 0UL;
volatile char *pcFileName = ( volatile char *  ) pcFile;
volatile uint32_t ulLineNumber = ulLine;

	( void ) pcFileName;
	( void ) ulLineNumber;

	FreeRTOS_printf( ( "vAssertCalled( %s, %ld\n", pcFile, ulLine ) );

	/* Setting ulBlockVariable to a non-zero value in the debugger will allow
	this function to be exited. */
	taskDISABLE_INTERRUPTS();
	{
		while( ulBlockVariable == 0UL )
		{
			Sleep( ulLongSleep );
		}
	}
	taskENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

/* Called by FreeRTOS+TCP when the network connects or disconnects.  Disconnect
events are only received if implemented in the MAC driver. */
void vApplicationIPNetworkEventHook( eIPCallbackEvent_t eNetworkEvent )
{
uint32_t ulIPAddress, ulNetMask, ulGatewayAddress, ulDNSServerAddress;
char cBuffer[ 16 ];
static BaseType_t xTasksAlreadyCreated = pdFALSE;

	/* If the network has just come up...*/
	if( eNetworkEvent == eNetworkUp )
	{
		/* Create the tasks that use the IP stack if they have not already been
		created. */
		if( xTasksAlreadyCreated == pdFALSE )
		{
			/* See the comments above the definitions of these pre-processor
			macros at the top of this file for a description of the individual
			demo tasks. */
			#if( mainCREATE_SIMPLE_UDP_CLIENT_SERVER_TASKS == 1 )
			{
				vStartSimpleUDPClientServerTasks( configMINIMAL_STACK_SIZE, mainSIMPLE_UDP_CLIENT_SERVER_PORT, mainSIMPLE_UDP_CLIENT_SERVER_TASK_PRIORITY );
			}
			#endif /* mainCREATE_SIMPLE_UDP_CLIENT_SERVER_TASKS */

			#if( mainCREATE_SELECT_UDP_SERVER_TASKS == 1 )
			{
				vStartUDPSelectServerTasks( configMINIMAL_STACK_SIZE, mainUDP_SELECT_SERVER_PORT, mainUDP_SELECT_SERVER_TASK_PRIORITY );
			}
			#endif /* mainCREATE_SIMPLE_UDP_CLIENT_SERVER_TASKS */

			#if( mainCREATE_UDP_ECHO_TASKS == 1 )
			{
				vStartUDPEchoClientTasks( mainECHO_CLIENT_TASK_STACK_SIZE, mainECHO_CLIENT_TASK_PRIORITY );
			}
			#endif /* mainCREATE_UDP_ECHO_TASKS */

			#if( mainCREATE_TCP_ECHO_TASKS_SINGLE == 1 )
			{
				vStartTCPEchoClientTasks_SingleTasks( mainECHO_CLIENT_TASK_STACK_SIZE, mainECHO_CLIENT_TASK_PRIORITY );
			}
			#endif /* mainCREATE_TCP_ECHO_TASKS_SINGLE */

			#if( mainCREATE_TCP_ECHO_TASKS_SEPARATE == 1 )
			{
				vStartTCPEchoClientTasks_SeparateTasks( mainECHO_CLIENT_TASK_STACK_SIZE, mainECHO_CLIENT_TASK_PRIORITY );
			}
			#endif /* mainCREATE_TCP_ECHO_TASKS_SEPARATE */

			#if( mainCREATE_TFTP_SERVER == 1 )
			{
				vStartTFTPServerTask( mainTFTP_SERVER_STACK_SIZE, mainTFTP_SERVER_PRIORITY );
			}
			#endif /* mainCREATE_TFTP_SERVER */

			#if( mainCREATE_UDP_CLI_TASKS == 1 )
			{
				/* Register example commands with the FreeRTOS+CLI command
				interpreter via the UDP port specified by the
				mainUDP_CLI_PORT_NUMBER constant. */
				vRegisterCLICommands();
				vStartUDPCommandInterpreterTask( configMINIMAL_STACK_SIZE, mainUDP_CLI_PORT_NUMBER, mainUDP_CLI_TASK_PRIORITY );
			}
			#endif /* mainCREATE_UDP_CLI_TASKS */

			#if( mainCREATE_TCP_CLI_TASKS == 1 )
			{
				/* Register example commands with the FreeRTOS+CLI command
				interpreter via the TCP port specified by the
				mainTCP_CLI_PORT_NUMBER constant. */
				vRegisterCLICommands();
				vStartTCPCommandInterpreterTask( configMINIMAL_STACK_SIZE, mainTCP_CLI_PORT_NUMBER, mainTCP_CLI_TASK_PRIORITY );
			}
			#endif /* mainCREATE_TCPP_CLI_TASKS */

			#if( mainCREATE_SIMPLE_TCP_ECHO_SERVER == 1 )
			{
				/* TCP server on port 5001, using multiple threads */
				vStartSimpleTCPServerTasks( configMINIMAL_STACK_SIZE, mainSIMPLE_UDP_CLIENT_SERVER_TASK_PRIORITY );
			}
			#endif /* mainCREATE_SIMPLE_TCP_ECHO_SERVER */

			#if( ( mainCREATE_FTP_SERVER == 1 ) || ( mainCREATE_HTTP_SERVER == 1 ) )
			{
				/* See TBD.
				Let the server work task now it can now create the servers. */
				xTaskNotifyGive( xServerWorkTaskHandle );
			}
			#endif

			xTasksAlreadyCreated = pdTRUE;
		}

		/* Print out the network configuration, which may have come from a DHCP
		server. */
		FreeRTOS_GetAddressConfiguration( &ulIPAddress, &ulNetMask, &ulGatewayAddress, &ulDNSServerAddress );
		FreeRTOS_inet_ntoa( ulIPAddress, cBuffer );
		FreeRTOS_printf( ( "\r\n\r\nIP Address: %s\r\n", cBuffer ) );

		FreeRTOS_inet_ntoa( ulNetMask, cBuffer );
		FreeRTOS_printf( ( "Subnet Mask: %s\r\n", cBuffer ) );

		FreeRTOS_inet_ntoa( ulGatewayAddress, cBuffer );
		FreeRTOS_printf( ( "Gateway Address: %s\r\n", cBuffer ) );

		FreeRTOS_inet_ntoa( ulDNSServerAddress, cBuffer );
		FreeRTOS_printf( ( "DNS Server Address: %s\r\n\r\n\r\n", cBuffer ) );
	}
}
/*-----------------------------------------------------------*/

/* Called automatically when a reply to an outgoing ping is received. */
void vApplicationPingReplyHook( ePingReplyStatus_t eStatus, uint16_t usIdentifier )
{
static const char *pcSuccess = "Ping reply received - ";
static const char *pcInvalidChecksum = "Ping reply received with invalid checksum - ";
static const char *pcInvalidData = "Ping reply received with invalid data - ";

	switch( eStatus )
	{
		case eSuccess	:
			FreeRTOS_printf( ( pcSuccess ) );
			break;

		case eInvalidChecksum :
			FreeRTOS_printf( ( pcInvalidChecksum ) );
			break;

		case eInvalidData :
			FreeRTOS_printf( ( pcInvalidData ) );
			break;

		default :
			/* It is not possible to get here as all enums have their own
			case. */
			break;
	}

	FreeRTOS_printf( ( "identifier %d\r\n", ( int ) usIdentifier ) );

	/* Prevent compiler warnings in case FreeRTOS_debug_printf() is not defined. */
	( void ) usIdentifier;
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* Called if a call to pvPortMalloc() fails because there is insufficient
	free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	internally by FreeRTOS API functions that create tasks, queues, software
	timers, and semaphores.  The size of the FreeRTOS heap is set by the
	configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
	vAssertCalled( __FILE__, __LINE__ );
}
/*-----------------------------------------------------------*/

static void prvCheckTimerCallback( TimerHandle_t xTimer )
{
static volatile uint32_t ulEchoClientErrors_Single = 0, ulEchoClientErrors_Separate = 0, ulEchoServerErrors = 0, ulUDPEchoClientErrors = 0, ulUDPSelectServerErrors = 0;

	( void ) xTimer;

	/* Not all the demo tasks contain a check function yet - although an
	assert() will be triggered if a task fails. */

	#if( mainCREATE_TCP_ECHO_TASKS_SINGLE == 1 )
	{
		if( xAreSingleTaskTCPEchoClientsStillRunning() != pdPASS )
		{
			ulEchoClientErrors_Single++;
		}
	}
	#endif

	#if( mainCREATE_TCP_ECHO_TASKS_SEPARATE == 1 )
	{
		if( xAreSeparateTaskTCPEchoClientsStillRunning() != pdPASS )
		{
 			ulEchoClientErrors_Separate++;
		}
	}
	#endif

	#if( mainCREATE_SIMPLE_TCP_ECHO_SERVER == 1 )
	{
		if( xAreTCPEchoServersStillRunning() != pdPASS )
		{
			ulEchoServerErrors++;
		}
	}
	#endif

	#if( mainCREATE_UDP_ECHO_TASKS == 1 )
	{
		if( xAreUDPEchoClientsStillRunning() != pdPASS )
		{
			ulUDPEchoClientErrors++;
		}
	}
	#endif

	#if( mainCREATE_SELECT_UDP_SERVER_TASKS == 1 )
	{
		if( xAreUDPSelectTasksStillRunning() != pdPASS )
		{
			ulUDPSelectServerErrors++;
		}
	}
	#endif
}
/*-----------------------------------------------------------*/

UBaseType_t uxRand( void )
{
const uint32_t ulMultiplier = 0x015a4e35UL, ulIncrement = 1UL;

	/* Utility function to generate a pseudo random number. */

	ulNextRand = ( ulMultiplier * ulNextRand ) + ulIncrement;
	return( ( int ) ( ulNextRand >> 16UL ) & 0x7fffUL );
}
/*-----------------------------------------------------------*/

static void prvSRand( UBaseType_t ulSeed )
{
	/* Utility function to seed the pseudo random number generator. */
    ulNextRand = ulSeed;
}
/*-----------------------------------------------------------*/

static void prvMiscInitialisation( void )
{
time_t xTimeNow;
uint32_t ulLoggingIPAddress;

	ulLoggingIPAddress = FreeRTOS_inet_addr_quick( configECHO_SERVER_ADDR0, configECHO_SERVER_ADDR1, configECHO_SERVER_ADDR2, configECHO_SERVER_ADDR3 );
	vLoggingInit( mainLOG_TO_STDOUT, mainLOG_TO_DISK_FILE, mainLOG_TO_UDP, ulLoggingIPAddress, configPRINT_PORT );

	/* Seed the random number generator. */
	time( &xTimeNow );
	FreeRTOS_debug_printf( ( "Seed for randomiser: %lu\n", xTimeNow ) );
	prvSRand( ( uint32_t ) xTimeNow );
	FreeRTOS_debug_printf( ( "Random numbers: %08X %08X %08X %08X\n", ipconfigRAND32(), ipconfigRAND32(), ipconfigRAND32(), ipconfigRAND32() ) );
}
/*-----------------------------------------------------------*/

struct tm *gmtime_r( const time_t *pxTime, struct tm *tmStruct )
{
	/* Dummy time functions to keep the file system happy in the absence of
	target support. */
	memcpy( tmStruct, gmtime( pxTime ), sizeof( * tmStruct ) );
	return tmStruct;
}
/*-----------------------------------------------------------*/

time_t FreeRTOS_time( time_t *pxTime )
{
time_t xReturn;

	xReturn = time( &xReturn );

	if( pxTime != NULL )
	{
		*pxTime = xReturn;
	}

	return xReturn;
}
/*-----------------------------------------------------------*/

#if( ipconfigUSE_LLMNR != 0 ) || ( ipconfigUSE_NBNS != 0 ) || ( ipconfigDHCP_REGISTER_HOSTNAME != 0 )

	const char *pcApplicationHostnameHook( void )
	{
		/* Assign the name "FreeRTOS" to this network node.  This function will
		be called during the DHCP: the machine will be registered with an IP
		address plus this name. */
		return mainHOST_NAME;
	}

#endif
/*-----------------------------------------------------------*/

#if( ipconfigUSE_LLMNR != 0 ) || ( ipconfigUSE_NBNS != 0 )

	BaseType_t xApplicationDNSQueryHook( const char *pcName )
	{
	BaseType_t xReturn;

		/* Determine if a name lookup is for this node.  Two names are given
		to this node: that returned by pcApplicationHostnameHook() and that set
		by mainDEVICE_NICK_NAME. */
		if( FF_stricmp( pcName, pcApplicationHostnameHook() ) == 0 )
		{
			xReturn = pdPASS;
		}
		else if( FF_stricmp( pcName, mainDEVICE_NICK_NAME ) == 0 )
		{
			xReturn = pdPASS;
		}
		else
		{
			xReturn = pdFAIL;
		}

		return xReturn;
	}

#endif
/*-----------------------------------------------------------*/
