#include <stdio.h>
#include <stdlib.h> 
#include <errno.h>
#include <string.h>
 
extern int errno; 

int main(void) {
	printf("Hello, World!\n");
	
	for(int errornum =0; errornum<135; errornum++ )
	{
	  errno = errornum;
    fprintf(stdout, "Value of errno: %d\n", errno);
    fprintf(stdout, ".\tError string: %s\n\n", strerror( errno ));
    //strerror() returns a pointer to the string with the text explanation of the errno
	}
      
	exit(EXIT_SUCCESS);
}

/********************************************
Hello, World!
Value of errno: 0
.	Error string: Success

Value of errno: 1
.	Error string: Operation not permitted

Value of errno: 2
.	Error string: No such file or directory

Value of errno: 3
.	Error string: No such process

Value of errno: 4
.	Error string: Interrupted system call

Value of errno: 5
.	Error string: Input/output error

Value of errno: 6
.	Error string: No such device or address

Value of errno: 7
.	Error string: Argument list too long

Value of errno: 8
.	Error string: Exec format error

Value of errno: 9
.	Error string: Bad file descriptor

Value of errno: 10
.	Error string: No child processes

Value of errno: 11
.	Error string: Resource temporarily unavailable

Value of errno: 12
.	Error string: Cannot allocate memory

Value of errno: 13
.	Error string: Permission denied

Value of errno: 14
.	Error string: Bad address

Value of errno: 15
.	Error string: Block device required

Value of errno: 16
.	Error string: Device or resource busy

Value of errno: 17
.	Error string: File exists

Value of errno: 18
.	Error string: Invalid cross-device link

Value of errno: 19
.	Error string: No such device

Value of errno: 20
.	Error string: Not a directory

Value of errno: 21
.	Error string: Is a directory

Value of errno: 22
.	Error string: Invalid argument

Value of errno: 23
.	Error string: Too many open files in system

Value of errno: 24
.	Error string: Too many open files

Value of errno: 25
.	Error string: Inappropriate ioctl for device

Value of errno: 26
.	Error string: Text file busy

Value of errno: 27
.	Error string: File too large

Value of errno: 28
.	Error string: No space left on device

Value of errno: 29
.	Error string: Illegal seek

Value of errno: 30
.	Error string: Read-only file system

Value of errno: 31
.	Error string: Too many links

Value of errno: 32
.	Error string: Broken pipe

Value of errno: 33
.	Error string: Numerical argument out of domain

Value of errno: 34
.	Error string: Numerical result out of range

Value of errno: 35
.	Error string: Resource deadlock avoided

Value of errno: 36
.	Error string: File name too long

Value of errno: 37
.	Error string: No locks available

Value of errno: 38
.	Error string: Function not implemented

Value of errno: 39
.	Error string: Directory not empty

Value of errno: 40
.	Error string: Too many levels of symbolic links

Value of errno: 41
.	Error string: Unknown error 41

Value of errno: 42
.	Error string: No message of desired type

Value of errno: 43
.	Error string: Identifier removed

Value of errno: 44
.	Error string: Channel number out of range

Value of errno: 45
.	Error string: Level 2 not synchronized

Value of errno: 46
.	Error string: Level 3 halted

Value of errno: 47
.	Error string: Level 3 reset

Value of errno: 48
.	Error string: Link number out of range

Value of errno: 49
.	Error string: Protocol driver not attached

Value of errno: 50
.	Error string: No CSI structure available

Value of errno: 51
.	Error string: Level 2 halted

Value of errno: 52
.	Error string: Invalid exchange

Value of errno: 53
.	Error string: Invalid request descriptor

Value of errno: 54
.	Error string: Exchange full

Value of errno: 55
.	Error string: No anode

Value of errno: 56
.	Error string: Invalid request code

Value of errno: 57
.	Error string: Invalid slot

Value of errno: 58
.	Error string: Unknown error 58

Value of errno: 59
.	Error string: Bad font file format

Value of errno: 60
.	Error string: Device not a stream

Value of errno: 61
.	Error string: No data available

Value of errno: 62
.	Error string: Timer expired

Value of errno: 63
.	Error string: Out of streams resources

Value of errno: 64
.	Error string: Machine is not on the network

Value of errno: 65
.	Error string: Package not installed

Value of errno: 66
.	Error string: Object is remote

Value of errno: 67
.	Error string: Link has been severed

Value of errno: 68
.	Error string: Advertise error

Value of errno: 69
.	Error string: Srmount error

Value of errno: 70
.	Error string: Communication error on send

Value of errno: 71
.	Error string: Protocol error

Value of errno: 72
.	Error string: Multihop attempted

Value of errno: 73
.	Error string: RFS specific error

Value of errno: 74
.	Error string: Bad message

Value of errno: 75
.	Error string: Value too large for defined data type

Value of errno: 76
.	Error string: Name not unique on network

Value of errno: 77
.	Error string: File descriptor in bad state

Value of errno: 78
.	Error string: Remote address changed

Value of errno: 79
.	Error string: Can not access a needed shared library

Value of errno: 80
.	Error string: Accessing a corrupted shared library

Value of errno: 81
.	Error string: .lib section in a.out corrupted

Value of errno: 82
.	Error string: Attempting to link in too many shared libraries

Value of errno: 83
.	Error string: Cannot exec a shared library directly

Value of errno: 84
.	Error string: Invalid or incomplete multibyte or wide character

Value of errno: 85
.	Error string: Interrupted system call should be restarted

Value of errno: 86
.	Error string: Streams pipe error

Value of errno: 87
.	Error string: Too many users

Value of errno: 88
.	Error string: Socket operation on non-socket

Value of errno: 89
.	Error string: Destination address required

Value of errno: 90
.	Error string: Message too long

Value of errno: 91
.	Error string: Protocol wrong type for socket

Value of errno: 92
.	Error string: Protocol not available

Value of errno: 93
.	Error string: Protocol not supported

Value of errno: 94
.	Error string: Socket type not supported

Value of errno: 95
.	Error string: Operation not supported

Value of errno: 96
.	Error string: Protocol family not supported

Value of errno: 97
.	Error string: Address family not supported by protocol

Value of errno: 98
.	Error string: Address already in use

Value of errno: 99
.	Error string: Cannot assign requested address

Value of errno: 100
.	Error string: Network is down

Value of errno: 101
.	Error string: Network is unreachable

Value of errno: 102
.	Error string: Network dropped connection on reset

Value of errno: 103
.	Error string: Software caused connection abort

Value of errno: 104
.	Error string: Connection reset by peer

Value of errno: 105
.	Error string: No buffer space available

Value of errno: 106
.	Error string: Transport endpoint is already connected

Value of errno: 107
.	Error string: Transport endpoint is not connected

Value of errno: 108
.	Error string: Cannot send after transport endpoint shutdown

Value of errno: 109
.	Error string: Too many references: cannot splice

Value of errno: 110
.	Error string: Connection timed out

Value of errno: 111
.	Error string: Connection refused

Value of errno: 112
.	Error string: Host is down

Value of errno: 113
.	Error string: No route to host

Value of errno: 114
.	Error string: Operation already in progress

Value of errno: 115
.	Error string: Operation now in progress

Value of errno: 116
.	Error string: Stale file handle

Value of errno: 117
.	Error string: Structure needs cleaning

Value of errno: 118
.	Error string: Not a XENIX named type file

Value of errno: 119
.	Error string: No XENIX semaphores available

Value of errno: 120
.	Error string: Is a named type file

Value of errno: 121
.	Error string: Remote I/O error

Value of errno: 122
.	Error string: Disk quota exceeded

Value of errno: 123
.	Error string: No medium found

Value of errno: 124
.	Error string: Wrong medium type

Value of errno: 125
.	Error string: Operation canceled

Value of errno: 126
.	Error string: Required key not available

Value of errno: 127
.	Error string: Key has expired

Value of errno: 128
.	Error string: Key has been revoked

Value of errno: 129
.	Error string: Key was rejected by service

Value of errno: 130
.	Error string: Owner died

Value of errno: 131
.	Error string: State not recoverable

Value of errno: 132
.	Error string: Operation not possible due to RF-kill

Value of errno: 133
.	Error string: Memory page has hardware error

Value of errno: 134
.	Error string: Unknown error 134
*********************************************/
