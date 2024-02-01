# Notes on memory management on Linux kernel

 - reference: Understanding the Linux Virtual Memory Manager: https://www.kernel.org/doc/gorman/html/understand/
 - reference: https://www.kernel.org/doc/gorman/html/understand/index.html
 - reference: What every programmer should know about memory:
     - https://lwn.net/Articles/250967/
     - https://lwn.net/Articles/252125/
     - https://lwn.net/Articles/253361/
     - https://lwn.net/Articles/254445/
     - https://lwn.net/Articles/255364/
 - reference: https://www.kernel.org/doc/
 - reference: https://linux-kernel-labs.github.io/refs/heads/master/lectures/address-space.html
 - reference: https://linux-kernel-labs.github.io/refs/heads/master/lectures/memory-management.html
 - reference: https://0xax.gitbooks.io/linux-insides/content/MM/

Videos: 
 - https://youtu.be/tpRlczF0pqw
 - https://youtu.be/w_z5tbFjmAA
 - https://youtu.be/7aONIVSXiJ8
 - https://youtu.be/wbi6IZDIv_4
 - https://youtu.be/fwLoPtTCmnw
 - https://youtu.be/i17b3xJv3Uo

### What is physical address space?


The entire range of memory addresses accessible by processors is often referred to as physical address space

In 32 Bit systems can have address space of 2^32 = 4 GB

In 64 Bit systems the addres space is 2^64.


This Physical address space is used by
 - RAM
 - BIOS
 - APIC
 - PCI
 - Other memory mapped I/O devices


```
+------------------+  <- 0xFFFFFFFF (4GB)
|      32-bit      |
|  memory mapped   |
|     devices      |
|                  |
/\/\/\/\/\/\/\/\/\/\

/\/\/\/\/\/\/\/\/\/\
|                  |
|      Unused      |
|                  |
+------------------+  <- depends on amount of RAM
|                  |
|                  |
| Extended Memory  |
|                  |
|                  |
+------------------+  <- 0x00100000 (1MB)
|     BIOS ROM     |
+------------------+  <- 0x000F0000 (960KB)
|  16-bit devices, |
|  expansion ROMs  |
+------------------+  <- 0x000C0000 (768KB)
|   VGA Display    |
+------------------+  <- 0x000A0000 (640KB)
|                  |
|    Low Memory    |
|                  |
+------------------+  <- 0x00000000
```

To see the memory space, use: 
```
$ sudo cat /proc/iomem  # This file shows you the current map of the system's memory for each physical device.

00000000-00000fff : Reserved
00001000-0009ffff : System RAM
000a0000-000fffff : Reserved
  000a0000-000dffff : PCI Bus 0000:00
  000f0000-000fffff : System ROM
00100000-09bfefff : System RAM
09bff000-0a000fff : Reserved
0a001000-0a1fffff : System RAM
0a200000-0a20efff : ACPI Non-volatile Storage
0a20f000-c7186fff : System RAM
c7187000-c7302fff : Reserved
c7303000-c74a9017 : System RAM
c74a9018-c74b6857 : System RAM
c74b6858-c74b7017 : System RAM
c74b7018-c74c8057 : System RAM
c74c8058-c7542fff : System RAM
c7543000-c7543fff : Reserved
c7544000-cb298fff : System RAM
cb299000-cc7a1fff : Reserved
  cc780000-cc783fff : MSFT0101:00
    cc780000-cc783fff : MSFT0101:00
  cc784000-cc787fff : MSFT0101:00
    cc784000-cc787fff : MSFT0101:00
cc7a2000-cc7eafff : ACPI Tables
cc7eb000-cc99dfff : ACPI Non-volatile Storage
cc99e000-cd1fefff : Reserved
cd1ff000-cdffffff : System RAM
ce000000-cfffffff : Reserved
d0000000-febfffff : PCI Bus 0000:00
  d0000000-e01fffff : PCI Bus 0000:04
    d0000000-dfffffff : 0000:04:00.0
    e0000000-e01fffff : 0000:04:00.0
  e0300000-e04fffff : PCI Bus 0000:02
    e0300000-e03fffff : 0000:02:00.0
      e0300000-e03fffff : 0000:02:00.0
    e0400000-e0403fff : 0000:02:00.0
    e0404000-e0404fff : 0000:02:00.0
  f0000000-f7ffffff : PCI MMCONFIG 0000 [bus 00-7f]
    f0000000-f7ffffff : pnp 00:00
  fc900000-fccfffff : PCI Bus 0000:04
    fc900000-fc9fffff : 0000:04:00.4
      fc900000-fc9fffff : xhci-hcd    #  This is the USB 3.0 controller
    fca00000-fcafffff : 0000:04:00.3
      fca00000-fcafffff : xhci-hcd     
    fcb00000-fcbfffff : 0000:04:00.2
      fcb00000-fcbfffff : ccp
    fcc00000-fcc7ffff : 0000:04:00.0
    fcc80000-fccbffff : 0000:04:00.5
    fccc0000-fccc7fff : 0000:04:00.6
      fccc0000-fccc7fff : ICH HD audio
    fccc8000-fcccbfff : 0000:04:00.1
      fccc8000-fcccbfff : ICH HD audio
    fcccc000-fcccdfff : 0000:04:00.2
      fcccc000-fcccdfff : ccp
  fcd00000-fcdfffff : PCI Bus 0000:05
    fcd00000-fcd007ff : 0000:05:00.1
      fcd00000-fcd007ff : ahci
    fcd01000-fcd017ff : 0000:05:00.0
      fcd01000-fcd017ff : ahci
  fce00000-fcefffff : PCI Bus 0000:03
    fce00000-fce03fff : 0000:03:00.0
      fce00000-fce03fff : nvme
    fce04000-fce23fff : 0000:03:00.0
  fcf00000-fcffffff : PCI Bus 0000:01
    fcf00000-fcf03fff : 0000:01:00.0
    fcf04000-fcf04fff : 0000:01:00.0
      fcf04000-fcf04fff : r8169
  fd210510-fd21053f : MSFT0101:00
  fd300000-fd37ffff : amd_iommu
fec00000-fec003ff : IOAPIC 0
fec01000-fec013ff : IOAPIC 1
fec10000-fec10fff : Reserved
  fec10000-fec10fff : pnp 00:02
fed00000-fed00fff : Reserved
  fed00000-fed003ff : HPET 0
    fed00000-fed003ff : PNP0103:00
fed40000-fed44fff : Reserved
fed80000-fed8ffff : Reserved
  fed81200-fed812ff : AMDI0030:00
  fed81500-fed818ff : AMDI0030:00
    fed81500-fed818ff : AMDI0030:00 AMDI0030:00
fedc0000-fedc0fff : pnp 00:02
fedc4000-fedc9fff : Reserved
fedcc000-fedcefff : Reserved
fedd5000-fedd5fff : Reserved
fee00000-ffffffff : PCI Bus 0000:00
  fee00000-fee00fff : Local APIC
    fee00000-fee00fff : pnp 00:02
  ff000000-ffffffff : pnp 00:02
100000000-76e2fffff : System RAM
  463800000-464bfffff : Kernel code      # This is the kernel section
  464c00000-4658b4fff : Kernel rodata
  465a00000-465e0f67f : Kernel data
  4662e0000-4673fffff : Kernel bss
76e300000-82fffffff : Reserved
3fff40000000-3fffffffffff : 0000:04:00.0
```

This file shows you the current map of the system's memory for each physical device.

To get the RAM used, use the command: 
```
$ free -m
```
or
```
$ cat /proc/meminfo
```


### Virtual Address Space for 32-bit processors

On Linux, every memory address is virtual. They do not point to any address in the RAM directly.

Whenever you access a memory location, a translation mechanism is performed in order to match the corresponding phyical memory.

On Linux Systems, each process owns a virtual address space.

Size of the virtual address space is 4GB on 32-bit systems (even on a system with physical memory less than 4 GB)

Linux divides this virtual address space into:
 - An area for applications, called user space.
 - An area for kernel, called kernel space.

The split between the two is set by a kernel configuration parameter named PAGE_OFFSET.

This is called 3G/1G Split:

```
      .------------------------. 0xFFFFFFFF 
      |                        | (4 GB) 
      |    Kernel addresses    | 
      |                        | 
      |                        | 
      .------------------------.CONFIG_PAGE_OFFSET 
      |                        |(x86: 0xC0000000, ARM: 0x80000000) 
      |                        | 
      |                        | 
      |  User space addresses  | 
      |                        | 
      |                        | 
      |                        | 
      |                        | 
      '------------------------' 00000000

```

User address space is allocated per process, so that each process runs in a sandbox, separated from others.

The kernel address space is same for all process; there is only one kernel.


### Virtual Address Space for 64-bit memory map

 - reference: https://unix.stackexchange.com/questions/509607/how-a-64-bit-process-virtual-address-space-is-divided-in-linux
 - reference: https://docs.kernel.org/arch/x86/x86_64/mm.html

The 64-bit x86 virtual memory map splits the address space into two: the lower section (with the top bit set to 0) is user-space,
the upper section (with the top bit set to 1) is kernel-space. (Note that x86-64 defines “canonical” “lower half” and “higher half” 
addresses, with a number of bits effectively limited to 48 or 57; see Wikipedia or the Intel SDM, volume 3 section 4.5, for details.)

Architecture defines a 64-bit virtual address. Implementations can support less. Currently supported are 48- and 57-bit virtual addresses.
Bits 63 through to the most-significant implemented bit are sign extended. This causes hole between user space and kernel addresses if you interpret them as unsigned.

The direct mapping covers all memory in the system up to the highest memory address (this means in some cases it can also include PCI memory holes).


```
===========================================================================================
    Start addr    |   Offset   |     End addr     |  Size   | VM area description
===========================================================================================
                  |            |                  |         |
 0000000000000000 |    0       | 00007fffffffffff |  128 TB | user-space virtual memory
__________________|____________|__________________|_________|______________________________
                  |            |                  |         |
 0000800000000000 | +128    TB | ffff7fffffffffff | ~16M TB | non-canonical
__________________|____________|__________________|_________|______________________________
                  |            |                  |         |
 ffff800000000000 | -128    TB | ffffffffffffffff |  128 TB | kernel-space virtual memory
__________________|____________|__________________|_________|______________________________
```

### Virtual Address Space for ARM 64-bit memory map

- reference: https://www.kernel.org/doc/html/latest/arch/arm64/memory.html


### Why kernel shares its address space  with every process

 - Every single process uses system calls, which will involve the kernel
 - Mapping the kernel's virtual memory address into each process virtual address space allows us to avoid the cost of switching out the memory address space on each entry to and exit from the kernel


### Kinds of Memory & printing addresses

Kernel and user space work with virtual addresses.

These virtual addresses are mapped to physical addresses by memory management hardware (MMU).

```
Header File: #include <asm/io.h>

phys_addr = virt_to_phys(virt_addr);
virt_addr = phys_to_virt(phys_addr);
```

For printing kernel pointers which should be hidden from unprivileged users. The behaviour of %pK depends on the kptr_restrict sysctl - see Documentation for /proc/sys/kernel/ for more details.

- reference: https://www.kernel.org/doc/html/latest/core-api/printk-formats.html?highlight=formats#pointer-types
- reference: https://www.kernel.org/doc/html/latest/core-api/printk-formats.html?highlight=formats#kernel-pointers
- reference: https://www.kernel.org/doc/html/latest/admin-guide/sysctl/kernel.html#kptr-restrict
- reference: https://www.kernel.org/doc/html/latest/core-api/printk-formats.html?highlight=formats#unmodified-addresses
- reference: https://www.kernel.org/doc/html/latest/core-api/printk-formats.html?highlight=formats#physical-address-types-phys-addr-t

A raw pointer value may be printed with `%p `which will hash the address before printing. The kernel also supports extended specifiers for printing pointers of different types.

For printing pointers when you really want to print the address. Please consider whether or not you are leaking sensitive information about the kernel
memory layout before printing pointers with `%px`. `%px`is functionally equivalent to `%lx` (or `%lu`). `%px` is preferred because it is more uniquely grep'able.
If in the future we need to modify the way the kernel handles printing pointers we will be better equipped to find the call sites.

Before using `%px`, consider if using `%p` is sufficient together with enabling the no_hash_pointers kernel parameter during debugging sessions. One valid scenario for `%px` 
might be printing information immediately before a panic, which prevents any sensitive information to be exploited anyway, and with `%px` there would be no need 
to reproduce the panic with `no_hash_pointers`.

For printing a phys_addr_t type (and its derivatives, such as resource_size_t) which can vary based on build options, regardless of the width of the CPU data path, 
then the `%pa` is used

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");
static int __init test_hello_init(void)
{
    int i = 10;
    void *virtual_address = (void *)&i;
    phys_addr_t physical_address = virt_to_phys(virtual_address);

    pr_info("Virtual Address(hashed) of i is %p\n", virtual_address);
    pr_info("Virtual Address(unmodified) of i is %px\n", virtual_address);
    pr_info("Physical Address of i is %pa\n", &physical_address);
    pr_info("Virtual address of i is %px\n", phys_to_virt(physical_address));
    return -1;  // as int doesn't return 0, the module init will fail
}

static void __exit test_hello_exit(void)
{
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```


### Pages

 - reference: linux kernel memory management: https://docs.kernel.org/mm/index.html
 - reference: linux kernel virtual memory pages: https://docs.kernel.org/mm/page_tables.html

Virtual address space (0x00000000 to 0xffffffff) is divided into pages of 4096 (4KiB) bytes.

The page size may differ in other systems. But on ARM and x86 it is fixed.

The size of a page is defined in the kernel through the `PAGE_SIZE` macro.

Pages in the virtual address space are mapped to physical addresses by the Memory Management Unit(MMU), which uses page tables to perform the mapping.

Memory Page/Virtual Page/Page: 
 - Refers to a fixed length contiguous block of **virtual memory**. 
 - Kernel data structure to represent a memory page is struct page

Frame/Page Frame:
 - Refers to a fixed length contiguous block of **physical memory** on top of which the OS maps a memory page
 - Each page frame is given a page frame number (PFN).
 - Given a page, you can easily get its PFN and vice versa, using page_to_pfn/pfn_to_page macros

Page Table:
 - Kernel and architecture data structure used to store the mapping between virtual addresses and physical addresses
 - Each entry describes key pair page/frame


#### Command to find out page size

```
$ getconf PAGESIZE
or
$ getconf PAGE_SIZE
```

### Page

Kernel represents every virtual page on the system with struct page structure.

Header File: <linux/mmtypes.h>

```
struct page {
        unsigned long flags;
        atomic_t      _count;
	       void          *virtual;
	....
};
```

 - Flags: Status of the page: Dirty, locked in memory. 
    -  Values: <linux/page-flags.h>
 - _count : Usage count of the page. How many references are to this page. When page is free _count is negative one
 - virtual: Page's virtual Address.

with 4KB Page Size and 4GB of Physical Memory = 1048576 Pages

Each page is taking 64 bytes = 1048576*64 = 64 MB is used to store all the physical pages

<br> 

Kernel memory is managed in a fairly straightforward way. 

It is not demand-paged, meaning that, for every allocation using kmalloc() or similar function, there is real physical memory.

Kernel memory is never discarded or paged out. So the kernel memory will always be on the RAM.

Linux employs a lazy allocation strategy for user space, only mapping physical pages of memory when the program accesses it.

For example, allocating a buffer of 1 MiB using malloc(3) returns a pointer to a block of memory addresses but no actual physical memory. 

 A flag is set in the page table entries such that any read or write access is trapped by the kernel. This is known as a page fault.

Only at this point does the kernel attempt to find a page of physical memory and add it to the page table mapping for the process.

### Page faults

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#define BUFFER_SIZE (4*1024 * 1024)

void print_pgfaults(void)
{
  int ret;
  struct rusage usage;
  ret = getrusage(RUSAGE_SELF, &usage);
  if (ret == -1) {
    perror("getrusage");
  } else {
    printf ("Major page faults %ld\n", usage.ru_majflt);
    printf ("Minor page faults %ld\n", usage.ru_minflt);
  }
}

int main (int argc, char *argv[])
{
  unsigned char *p;
  printf("Initial state\n");
  print_pgfaults();
  p = malloc(BUFFER_SIZE);
  printf("After malloc\n");
  print_pgfaults();
  memset(p, 'a', BUFFER_SIZE);
  printf("After memset\n");
  print_pgfaults();
  memset(p, 'b', BUFFER_SIZE);
  printf("After 2nd memset\n");
  print_pgfaults();
  return 0;
}
```

When try to access the memroy with memset, we can see, that page faults are generated. 


A page fault is generated when the kernel traps an access to a page that has not been mapped.

In fact, there are two kinds of page fault: minor and major. 

 With a minor fault, the kernel just has to find a page of physical memory and map it into the process address space

A major page fault occurs when the virtual memory is mapped to a file, for example using mmap(2)

major faults are much more expensive in time and system resources


### User space virtual address space

```
User space virtual address space
=================================

	 		 address|-------------------| command-line arguments
   				|-------------------| and environment variables
				|        stack      |
				|-------------------|
				|	            |
				|		    |
				|		    |
				|-------------------|
				|		heap|
				|-------------------|
				|uninitialized data | initialized to
				|		(bss| zero by exec
				|-------------------|
				| initialized data  | read from
				|-------------------| program file 
				|		text| by exec
	low address 		|-------------------|
			Typical memory arrangement

$ cat /proc/pid/maps

```

### Kernel space

#### Low and High Memory


The Linux kernel has its own virtual address space, as every user mode process does.

The kernel code and data structures must fit into that space, but the biggest consumer of kernel address space is virtual mappings for physical memory.

The kernel to access physical memory should first map it into the kernel's virtual address space. 

Maximum amount of physical memory handled by the kernel = amount that could be mapped into the kernel's portion of virtual address space - Space used by kernel code.

As, a result x86 based Linux systems could work with a maximum of a little under 1 GB of physical memory.

The virtual address space of the kernel (1 GB sized in a 3G/1G split) is divided into two parts:
 - Low memory or LOWMEM, which is the first 896 MB
 - High memory or HIGHMEM, represented by the top 128 MB


```
                                           Physical mem 
       Process address space    +------> +------------+ 
                                |        |  3200 M    | 
                                |        |            | 
    4 GB+---------------+ <-----+        |  HIGH MEM  | 
        |     128 MB    |                |            | 
        +---------------+ <---------+    |            | 
        +---------------+ <------+  |    |            |  
        |     896 MB    |        |  +--> +------------+          
    3 GB+---------------+ <--+   +-----> +------------+  
        |               |    |           |   896 MB   | LOW MEM 
        |     /////     |    +---------> +------------+ 
        |               |      
    0 GB +---------------+
```

#### Low Memory

The first 896 MB of kernel address space constitutes the low memory region.

Early in the boot, the kernel permanently maps this 896MB

Addresses that result from this mapping are called **logical addresses**. 

These are virtual addresses, but can be translated into physical addresses by subtracting a fixed offset, since the mapping is permanent and known in advance.

You can convert a physical address into a logical address using the `__pa(address)` macro, and then revert it with the `__va(address)` macro.

Low memory matches with the lower bound of physical addresses.

In fact, to serve different purposes, kernel memory is divided into a zone.

We can then identify three different memory zones in the kernel space:

 - ZONE_DMA: This contains page frames of memory below 16 MB, reserved for Direct Memory Access (DMA)
 - ZONE_NORMAL: This contains page frames of memory above 16 MB and below 896 MB, for normal use
 - ZONE_HIGHMEM: This contains page frames of memory at and above 896 MB

On a 512 MB system, there will be no ZONE_HIGHMEM, 16 MB for ZONE_DMA, and 496 MB for ZONE_NORMAL.

#### High Memory

The top 128 MB of the kernel address space is called the high memory region. 

It is used by the kernel to temporarily map physical memory above 1 GB

When physical memory above 1GB (or more precisely 896MB) needs to be accessed, the kernel uses those 128MB to create a temporary mapping to its virtual address space, thus achieving the goal of being able to access all physical pages.

The physical memory above 896 MB is mapped on demand to the 128 MB of the HIGHMEM region.

Mapping to access high memory is created on the fly by the kernel, and destroyed when done. This makes high memory access slower. 

**Concept of high memory does not exist on 64-bit systems**, due to the huge address range (2^64), where the 3G/1G split does not make sense anymore.

### How to check low and high mem? 

```
$ cat /proc/meminfo | grep LowTotal # this will report the low memory
$ cat /proc/meminfo | grep HighTotal # this will report high memory
```
### Memory allocation mechanism

```
	----------------------------------
	|	Kernel			 |
	|	Module			 |
	----------------------------------
	    |		|	|	|
	    v	        |	|	v
	----------	|	|  -----------
	|         |	|	|  |         |
	|kmalloc  |	|	|  |vmalloc  |
	|allocator|	|	|  |allocator|
	----------	|	|  -----------
	   |            |	|
	   v	        v	|
	-----------------	|	
	| slab       	|	|
	| allocator  	|	|
	----------------	|
		|		|
		v		v
	------------------------------------------
	|	Page Allocator			 |
	|Allocate physical memory by chunk of 4k |
	------------------------------------------
			|
			|	
			v
	---------------------------------------
	|	Main Memory		      |
	|				      |
	---------------------------------------
```

There is an allocation mechanism to satisfy any kind of memory request.

Depending on what you need memory for, you can choose the one closest to your goal.

The main allocator is the page allocator, which only works with pages (a page being the smallest memory unit it can deliver)

Then comes the SLAB allocator which is built on top of the page allocator, getting pages from it and returning smaller memory entities (by mean of slabs and caches). This is the allocator on which the kmalloc allocator relies on.


### kmalloc family allocation

`kmalloc` is a kernel memory allocation function, such as malloc() in user space

Memory returned by kmalloc is __**contiguous**__ in physical memory and in virtual memory:

```
			virtual memory    physical memory
			----------        --------
		   - - -|	 |------- |	 |
	kmalloc	  /	|	 |        |	 |
	---------/	|        |        |	 |
	|	|	|        |        |	 |
	|	|   ---	|        |------- | 	 |
	|	|  /	|        |	  |	 |
	|	| /	|        |	  |	 |
	---------/	|        |	  |	 |
			|        |	  |	 | 
			|        |        |      |
			|        |        |      |
			|        |        |      |
			|        |        |      |
			----------        --------
```

`kmalloc` allocator is the general and higher-level memory allocator in the kernel, and relies on SLAB Allocator

Memory returned from kmalloc has a kernel logical address because it is allocated from the LOW_MEM region, unless HIGH_MEM is specified.

Header File: #include <linux/slab.h>

```
void *kmalloc(size_t size, int flags); 

	size: specifies the size of the memory to be allocated (in bytes).
	flags: determines how and where memory should be allocated. 
		Available flags are the same as the page allocator (GFP_KERNEL, GFP_ATOMIC, GFP_DMA, and so on)
```

Return Value: On Success, returns the virtual address of the chunk allocated, which is guaranteed to be physically contiguous.  On error, it returns NULL

#### Flags

 - GFP_KERNEL: This is the standard flag. We cannot use this flag in the interrupt handler because its code may sleep. It always returns memory from the LOM_MEM zone (hence a logical address).
 - GFP_ATOMIC: This guarantees the atomicity of the allocation. The only flag to use when we are in the interrupt context.
 - GFP_USER: This allocates memory to a user space process. Memory is then distinct and separated from that allocated to the kernel.
 - GFP_HIGHUSER: This allocates memory from the HIGH_MEMORY zone.
 - GFP_DMA: This allocates memory from DMA_ZONE.

#### kfree

The kfree function is used to free the memory allocated by kmalloc. The following is the prototype of kfree():

```
void kfree(const void *ptr) 
```

Memory corruption can happen:
 - on a block of memory that already has been freed
 - on a pointer that is not an address returned from kmalloc()

Always balance allocations and frees to ensure that kfree() is called exactly once on the correct pointer

### Example

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");

static void *ptr;
int alloc_size = 1024;

module_param(alloc_size, int, 0);

static int test_hello_init(void)
{
	ptr = kmalloc(alloc_size,GFP_ATOMIC);
	if(!ptr) {
		/* handle error */
		pr_err("memory allocation failed\n");
		return -ENOMEM;
	} else {
		phys_addr_t physical_address = virt_to_phys(ptr);
		pr_info("Memory Allocated:%px\n", ptr);
		pr_info("Physical Address of i is %pa\n", &physical_address);
	}

	return 0;
}

static void test_hello_exit(void)
{
	kfree(ptr);
	pr_info("Memory freed\n");

}

module_init(test_hello_init);
module_exit(test_hello_exit);
```
you can check the physycal memory used by devices, with `$ cat /proc/iomem` and then chekck that the physical memory alocated belong to the RAM.

 - reference: iomem : https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/4/html/reference_guide/s2-proc-iomem


### zones

- reference: https://www.kernel.org/doc/gorman/html/understand/understand005.html#toc13

Linux kernel divides physical RAM into a number of different memory regions: zones

What memory regions(zones) there are depends on whether your machine is 32-bit or 64-bit and also how complicated it is

Zones:

 - 1. DMA: 	low 16 MBytes of memory. At this point it exists for historical reasons. 
		There was hardware that could only do DMA into this area of physical memory.

 - 2. DMA32:	exists only in 64-bit Linux. 
		it is the low 4 GBytes of memory, more or less.
		t exists because the transition to large memory 64-bit machines has created a class of hardware that can only do DMA to the low 4 GBytes of memory.

 - 3. Normal:	 is different on 32-bit and 64-bit machines.
		 - On 64-bit machines, it is all RAM from 4GB or so on upwards
		 - On 32-bit machines it is all RAM from 16 MB to 896 MB for complex and somewhat historical reasons

		 Note that this implies that machines with a 64-bit kernel can have very small amounts of Normal memory unless they have significantly more than 4GB of RAM. 
		For example, a 2 GB machine running a 64-bit kernel will have no Normal memory at all while a 4 GB machine will have only a tiny amount of it.

 - 4. HighMem:	exists only on 32-bit Linux; 
		it is all RAM above 896 MB, including RAM above 4 GB on sufficiently large machines.

Within each zone, Linux uses a buddy-system allocator to allocate and free physical memory.


### Buddy Allocator

- reference: https://www.kernel.org/doc/gorman/html/understand/understand009.html
- reference: https://grimoire.carcano.ch/blog/memory-management-the-buddy-allocator/
- reference: https://cs.stackexchange.com/questions/152260/buddy-system-allocator-and-slab-allocator-in-linux-kernel
- reference: https://www.geeksforgeeks.org/operating-system-allocating-kernel-memory-buddy-system-slab-system/
- reference: https://hackernoon.com/understanding-kernel-memory-allocation-using-buddy-and-slab-systems
- reference: https://www.tutorialspoint.com/allocating-kernel-memory-buddy-system-and-slab-system

Memory is broken up into large blocks of pages where each block is a power of two number of pages (2^order).
All free pages are split into 11 (MAX_ORDER) lists, each contains a list of 2^order pages.

When an allocation request is made for a particular size, the buddy system looks into the appropriate list for a free block, and returns its address, if available. 

However, if it cannot find a free block, it moves to check in the next high-order list for a larger block, which if available it splits the higher-order block into equal parts called buddies, returns one for the allocator, and queues the second into a lower-order list. 

When both buddy blocks become free at some future time, they are coalesced to create a larger block.

### /proc/buddyinfo

- reference: https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/4/html/reference_guide/s2-proc-buddyinfo

Using the buddy algorithm, each column represents the number of pages of a certain order (a certain size) that are available at any given time.

```
# cat /proc/buddyinfo 
Node 0, zone      DMA      1      1      0      1      2      1      1      0      1      1      3 
Node 0, zone   Normal      1      1      1      1      3      1      1      2      3      4    207 
Node 0, zone  HighMem     22      8      4      1      1      1      1      1      1      2     34 
```
The 11 colums, belong to the 11 (MAX_ORDER) lists. 

This means, zone DMA, there are 1 of 2^(0*PAGE_SIZE) free chunks of memory, 1 of 2^(1)*PAGE_SIZE, 0 of 2^(2)*PAGE_SIZE and so on upto 3*(2^10)*PAGE_SIZE = Nearly 16 MB







