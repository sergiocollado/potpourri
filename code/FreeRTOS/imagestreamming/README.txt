this is a sample project in FreeRTOS

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
