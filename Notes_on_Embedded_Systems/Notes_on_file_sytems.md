# FAT - File Allocation Table

FAT file system used to be very popular for hard-disks, and even nowadays is common to use it.

There are 12-bit, 16-bit and 32-bit versions.

An overview of the 16-bit version is commented below:

A disk is made of __surfaces__ (one for each head), __tracks__, and __sectors__; but for simplifications we can consider it just a number
of sectors, first one numbered 0, second one numbered 1 and so on... actual location of each sector is irrelevant because, each sector
have written its own numbers within each track. We call those sectors __blocks__ and consider them linealy and sequentially allocated.

All block sizes are 512-bits of size (on some big systems, with this size it means that there are too many numbered blocks, so the
blocks are agroupated in pairs of two, four, ... and each group is called and __allocation unit__.

Disks/memory that uses FAT uses the following areas:

| Area description | Area size |
|---|---|
| Boot Block | 1 block | 
| File Allocation Table | depends on file system |
| Disk root directory | Variable (selected when the disk is formatted) |
| File data area | The rest of the disk | 


## Boot Block

The **Boot Block** uses the first sector of the storage system, and in it resides the *__Bootloader Program__*, the program that
launches the operating system. It also contains other information, that describes the file system organization:

| Offset from start | Length (in Bytes) | Description |
|---|---|---|
| 0x00 | 3 | Part of the bootloader |
| 0x03 | 8 | Optional manufacturer description |
| 0x0b | 2 | Number of bytes per block |
| 0x0d | 1 | Number of blocks per allocation unit |


References:

[A tutorial on the FAT file system](http://www.tavi.co.uk/phobos/fat.html)
