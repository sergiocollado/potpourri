# FAT - File Allocation Table

FAT file system used to be very popular for hard-disks, and even nowadays is common to use it.

There are 12-bit(FAT12), 16-bit(FAT16) and 32-bit(FAT32) versions.

# An overview of the 16-bit version

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
| 0x0e     | 2  |  Number of reserved blocks that are in the disk and are not actually part of the file system. In most cases is just 1, being the allowance the Boot Block |
| 0x10     |  1 | Number of File Allocation Tables |
| 0x11  | 2  |   Number of root directory entries (even unused ones) |
| 0x13    | 2  | Total number of blocks in the entire disk. If the disk happens to be larger that 65535 blocks -- then this number cannot be stored at this fiel, because it wouldn't fit - you would need more than two bytes to represent it-- In this case the value of this field is set to zero; and the true number of blocks in the entire disk, is stored at position offset 0x20. |
|  0x15    |  1 |   Media descriptor                             |
|  0x16   | 2  |  The number of blocks used by one copy of the File Allocation Table |
|  0x18    | 2  |  The numbero of blocks per track. This information is for the use of the Bootstrap program.                       |
|  0x1a    |  2 |   Number of heads(disk surfaces). This information is for the use of the Boostrap program                            |
|  0x1c   |  4 |  The numbero of hidden blocks. This is a legacy field, and usually is set to 0. It can be ignored  |
|  0x20    | 4  | Total number of blocks in the entire disk - review field offset 0x13                          |
|  0x24   |  2 |  Physical drive number. This info is for the use of the Boostrap programm |
|  0x26    |  1 |  Extended boot record signature. This info is for the use of the Boostrap programm                               |
|  0x27    |  4 |  Volumen serial number. Unique number used for identification of a particular disk  |
|  0x2b    | 11  | Volumen Label. This is a string of characters for human-readeable identification of the disk- this is selected when the disk is formatted  |
|  0x36    | 8  |   File system identifier                             |
|  0x3e     | 0x1c0   |   The remainder of the Boostrap program                           |
|  0x1fe    | 2  |  Boot block 'signature' (0x55 followed by 0xaa)                          |

## The Media descriptor

Previosly it was dificult for de operating system to detect the size and type of a disk just by its hardware. So the 'Media descriptor' was used to classify disks. As today is rarely used, and most of the hard-disks set it to 0xf0.

## FAT - File Allocation Table

The FAT uses one or more blocks inmediately following the Boot Block. Commonly, part of its last block will remain unused. and its ulikely that the required number of entries will exactly fill a complete number of blocks. If there is a second  FAT, this inmediately follow the first one (but starting at a new block) ... and this is repeated for any number of FATs.

In the case of FAT16, each entry in the FAT uses two bytes in lenght (i.e. 16 bits) The disk data area is divided into clusters-- that are the same as allocation units, but with a different numeration (isntead of being numbered from the start of the disk, clusters are numberated from the start of the disk data area). So, the cluster number is the the allocation unit number, minus a constant value which is the size of the areas in between the start of the disk and the start of the data area. 

**Warn for the adventurer** The clusters start its numbering at 2, not at 0!! So the above calculations need to have 2 added to get the cluster of a given allocation unit. And a cluster number is converted to an allocation unit number by substracting 2 ... !!






References:

[A tutorial on the FAT file system](http://www.tavi.co.uk/phobos/fat.html)
