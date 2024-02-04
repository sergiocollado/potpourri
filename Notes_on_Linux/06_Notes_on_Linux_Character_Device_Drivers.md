References:
 - Linux kernel documentation - device drivers: https://docs.kernel.org/driver-api/driver-model/driver.html
 - The linux device driver: https://docs.kernel.org/driver-api/driver-model/overview.html
 - Drivers implementer's API: https://docs.kernel.org/driver-api/index.html
 - Let's code a Linux Driver: https://www.youtube.com/watch?v=x1Y203vH-Dc&list=PLCGpd0Do5-I3b5TtyqeF1UdyD4C-S-dMa
 - Linux kernel labs - character drivers: https://linux-kernel-labs.github.io/refs/heads/master/labs/device_drivers.html


## Introduction

In Linux everything is considered to be a file so devices are also considered to be a file.

In UNIX, hardware devices are accessed by the user through special device files.

These files are grouped into the /dev directory, and system calls open, read, write, close, lseek, mmap etc. are redirected by the operating system to the device driver associated with the physical device.

In the UNIX world there are two categories of device files and thus device drivers: character and block.

This division is done 
 - by the speed, 
 - volume and 
 - way of organizing the data to be transferred from the device to the system and vice versa.

In the first category, there are slow devices, which manage a small amount of data, and access to data does not require frequent seek queries.

Examples are devices such as keyboard, mouse, serial ports, sound card, joystick. 

In general, operations with these devices (read, write) are performed sequentially byte by byte.

The second category includes devices where data volume is large, data is organized on blocks, and search is common. 

Examples of devices that fall into this category are hard drives, cdroms, ram disks, magnetic tape drives.

For these devices, reading and writing is done at the data block level.

For the two types of device drivers, the Linux kernel offers different APIs.

If for character devices system calls go directly to device drivers, in case of block devices, the drivers do not work directly with system calls. 

In the case of block devices, communication between the user-space and the block device driver is mediated by the file management subsystem and the block device subsystem. 


### Character Device Driver

A character device typically transfers data to and from a user application — they behave like pipes or serial ports, instantly reading or writing the byte data in a character-by-character stream.

#### Command to list all the character device driver
```
$ls -l /dev/ | grep "^c"
```

#### Command to list all the block device driver

```
$ls -l /dev/ | grep "^b"
```

#### Steps in creating a character driver

1. Allocate a device number dynamically or statically (dev_t)
2. Initializing the character device with its file operations (struct cdev, struct file_operations)
3. Registering the character device with Linux Kernel (cdev_add)
