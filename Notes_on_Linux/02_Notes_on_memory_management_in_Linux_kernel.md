# Notes on memory management on Linux kernel

 - refernece: overview: https://zedas.fr/posts/linux-explained-7-memory-management/
 - reference: Understanding the Linux Virtual Memory Manager: https://www.kernel.org/doc/gorman/html/understand/
 - reference: https://docs.kernel.org/admin-guide/mm/index.html
 - reference: https://www.kernel.org/doc/gorman/html/understand/index.html
 - Linux VFS: https://www.kernel.org/doc/html/latest/filesystems/#core-vfs-documentation
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
 - Writing Portable Device Drivers: https://www.linuxjournal.com/article/5783

Videos: 
 - https://youtu.be/tpRlczF0pqw
 - https://youtu.be/w_z5tbFjmAA
 - https://youtu.be/7aONIVSXiJ8
 - https://youtu.be/wbi6IZDIv_4
 - https://youtu.be/fwLoPtTCmnw
 - https://youtu.be/i17b3xJv3Uo

### How to check RAM? 

Use the commands: 
```
$ cat /proc/meminfo
$ free -h
```

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

### /proc/meminfo

references:
 - https://man7.org/linux/man-pages/man5/proc.5.html
 - https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/4/html/reference_guide/s2-proc-meminfo

```
       /proc/meminfo
              This file reports statistics about memory usage on the
              system.  It is used by free(1) to report the amount of
              free and used memory (both physical and swap) on the
              system as well as the shared memory and buffers used by
              the kernel.  Each line of the file consists of a parameter
              name, followed by a colon, the value of the parameter, and
              an option unit of measurement (e.g., "kB").  The list
              below describes the parameter names and the format
              specifier required to read the field value.  Except as
              noted below, all of the fields have been present since at
              least Linux 2.6.0.  Some fields are displayed only if the
              kernel was configured with various options; those
              dependencies are noted in the list.

              MemTotal %lu
                     Total usable RAM (i.e., physical RAM minus a few
                     reserved bits and the kernel binary code).

              MemFree %lu
                     The sum of LowFree+HighFree.

              MemAvailable %lu (since Linux 3.14)
                     An estimate of how much memory is available for
                     starting new applications, without swapping.

              Buffers %lu
                     Relatively temporary storage for raw disk blocks
                     that shouldn't get tremendously large (20 MB or
                     so).

              Cached %lu
                     In-memory cache for files read from the disk (the
                     page cache).  Doesn't include SwapCached.

              SwapCached %lu
                     Memory that once was swapped out, is swapped back
                     in but still also is in the swap file.  (If memory
                     pressure is high, these pages don't need to be
                     swapped out again because they are already in the
                     swap file.  This saves I/O.)

              Active %lu
                     Memory that has been used more recently and usually
                     not reclaimed unless absolutely necessary.

              Inactive %lu
                     Memory which has been less recently used.  It is
                     more eligible to be reclaimed for other purposes.

              Active(anon) %lu (since Linux 2.6.28)
                     [To be documented.]

              Inactive(anon) %lu (since Linux 2.6.28)
                     [To be documented.]

              Active(file) %lu (since Linux 2.6.28)
                     [To be documented.]

              Inactive(file) %lu (since Linux 2.6.28)
                     [To be documented.]

              Unevictable %lu (since Linux 2.6.28)
                     (From Linux 2.6.28 to Linux 2.6.30,
                     CONFIG_UNEVICTABLE_LRU was required.)  [To be
                     documented.]

              Mlocked %lu (since Linux 2.6.28)
                     (From Linux 2.6.28 to Linux 2.6.30,
                     CONFIG_UNEVICTABLE_LRU was required.)  [To be
                     documented.]

              HighTotal %lu
                     (Starting with Linux 2.6.19, CONFIG_HIGHMEM is
                     required.)  Total amount of highmem.  Highmem is
                     all memory above ~860 MB of physical memory.
                     Highmem areas are for use by user-space programs,
                     or for the page cache.  The kernel must use tricks
                     to access this memory, making it slower to access
                     than lowmem.

              HighFree %lu
                     (Starting with Linux 2.6.19, CONFIG_HIGHMEM is
                     required.)  Amount of free highmem.

              LowTotal %lu
                     (Starting with Linux 2.6.19, CONFIG_HIGHMEM is
                     required.)  Total amount of lowmem.  Lowmem is
                     memory which can be used for everything that
                     highmem can be used for, but it is also available
                     for the kernel's use for its own data structures.
                     Among many other things, it is where everything
                     from Slab is allocated.  Bad things happen when
                     you're out of lowmem.

              LowFree %lu
                     (Starting with Linux 2.6.19, CONFIG_HIGHMEM is
                     required.)  Amount of free lowmem.

              MmapCopy %lu (since Linux 2.6.29)
                     (CONFIG_MMU is required.)  [To be documented.]

              SwapTotal %lu
                     Total amount of swap space available.

              SwapFree %lu
                     Amount of swap space that is currently unused.

              Dirty %lu
                     Memory which is waiting to get written back to the
                     disk.

              Writeback %lu
                     Memory which is actively being written back to the
                     disk.

              AnonPages %lu (since Linux 2.6.18)
                     Non-file backed pages mapped into user-space page
                     tables.

              Mapped %lu
                     Files which have been mapped into memory (with
                     mmap(2)), such as libraries.

              Shmem %lu (since Linux 2.6.32)
                     Amount of memory consumed in tmpfs(5) filesystems.

              KReclaimable %lu (since Linux 4.20)
                     Kernel allocations that the kernel will attempt to
                     reclaim under memory pressure.  Includes
                     SReclaimable (below), and other direct allocations
                     with a shrinker.

              Slab %lu
                     In-kernel data structures cache.  (See
                     slabinfo(5).)

              SReclaimable %lu (since Linux 2.6.19)
                     Part of Slab, that might be reclaimed, such as
                     caches.

              SUnreclaim %lu (since Linux 2.6.19)
                     Part of Slab, that cannot be reclaimed on memory
                     pressure.

              KernelStack %lu (since Linux 2.6.32)
                     Amount of memory allocated to kernel stacks.

              PageTables %lu (since Linux 2.6.18)
                     Amount of memory dedicated to the lowest level of
                     page tables.

              Quicklists %lu (since Linux 2.6.27)
                     (CONFIG_QUICKLIST is required.)  [To be
                     documented.]

              NFS_Unstable %lu (since Linux 2.6.18)
                     NFS pages sent to the server, but not yet committed
                     to stable storage.

              Bounce %lu (since Linux 2.6.18)
                     Memory used for block device "bounce buffers".

              WritebackTmp %lu (since Linux 2.6.26)
                     Memory used by FUSE for temporary writeback
                     buffers.

              CommitLimit %lu (since Linux 2.6.10)
                     This is the total amount of memory currently
                     available to be allocated on the system, expressed
                     in kilobytes.  This limit is adhered to only if
                     strict overcommit accounting is enabled (mode 2 in
                     /proc/sys/vm/overcommit_memory).  The limit is
                     calculated according to the formula described under
                     /proc/sys/vm/overcommit_memory.  For further
                     details, see the kernel source file
                     Documentation/vm/overcommit-accounting.rst.

              Committed_AS %lu
                     The amount of memory presently allocated on the
                     system.  The committed memory is a sum of all of
                     the memory which has been allocated by processes,
                     even if it has not been "used" by them as of yet.
                     A process which allocates 1 GB of memory (using
                     malloc(3) or similar), but touches only 300 MB of
                     that memory will show up as using only 300 MB of
                     memory even if it has the address space allocated
                     for the entire 1 GB.

                     This 1 GB is memory which has been "committed" to
                     by the VM and can be used at any time by the
                     allocating application.  With strict overcommit
                     enabled on the system (mode 2 in
                     /proc/sys/vm/overcommit_memory), allocations which
                     would exceed the CommitLimit will not be permitted.
                     This is useful if one needs to guarantee that
                     processes will not fail due to lack of memory once
                     that memory has been successfully allocated.

              VmallocTotal %lu
                     Total size of vmalloc memory area.

              VmallocUsed %lu
                     Amount of vmalloc area which is used.  Since Linux
                     4.4, this field is no longer calculated, and is
                     hard coded as 0.  See /proc/vmallocinfo.

              VmallocChunk %lu
                     Largest contiguous block of vmalloc area which is
                     free.  Since Linux 4.4, this field is no longer
                     calculated and is hard coded as 0.  See
                     /proc/vmallocinfo.

              HardwareCorrupted %lu (since Linux 2.6.32)
                     (CONFIG_MEMORY_FAILURE is required.)  [To be
                     documented.]

              LazyFree %lu (since Linux 4.12)
                     Shows the amount of memory marked by madvise(2)
                     MADV_FREE.

              AnonHugePages %lu (since Linux 2.6.38)
                     (CONFIG_TRANSPARENT_HUGEPAGE is required.)  Non-
                     file backed huge pages mapped into user-space page
                     tables.

              ShmemHugePages %lu (since Linux 4.8)
                     (CONFIG_TRANSPARENT_HUGEPAGE is required.)  Memory
                     used by shared memory (shmem) and tmpfs(5)
                     allocated with huge pages.

              ShmemPmdMapped %lu (since Linux 4.8)
                     (CONFIG_TRANSPARENT_HUGEPAGE is required.)  Shared
                     memory mapped into user space with huge pages.

              CmaTotal %lu (since Linux 3.1)
                     Total CMA (Contiguous Memory Allocator) pages.
                     (CONFIG_CMA is required.)

              CmaFree %lu (since Linux 3.1)
                     Free CMA (Contiguous Memory Allocator) pages.
                     (CONFIG_CMA is required.)

              HugePages_Total %lu
                     (CONFIG_HUGETLB_PAGE is required.)  The size of the
                     pool of huge pages.

              HugePages_Free %lu
                     (CONFIG_HUGETLB_PAGE is required.)  The number of
                     huge pages in the pool that are not yet allocated.

              HugePages_Rsvd %lu (since Linux 2.6.17)
                     (CONFIG_HUGETLB_PAGE is required.)  This is the
                     number of huge pages for which a commitment to
                     allocate from the pool has been made, but no
                     allocation has yet been made.  These reserved huge
                     pages guarantee that an application will be able to
                     allocate a huge page from the pool of huge pages at
                     fault time.

              HugePages_Surp %lu (since Linux 2.6.24)
                     (CONFIG_HUGETLB_PAGE is required.)  This is the
                     number of huge pages in the pool above the value in
                     /proc/sys/vm/nr_hugepages.  The maximum number of
                     surplus huge pages is controlled by
                     /proc/sys/vm/nr_overcommit_hugepages.

              Hugepagesize %lu
                     (CONFIG_HUGETLB_PAGE is required.)  The size of
                     huge pages.

              DirectMap4k %lu (since Linux 2.6.27)
                     Number of bytes of RAM linearly mapped by kernel in
                     4 kB pages.  (x86.)

              DirectMap4M %lu (since Linux 2.6.27)
                     Number of bytes of RAM linearly mapped by kernel in
                     4 MB pages.  (x86 with CONFIG_X86_64 or
                     CONFIG_X86_PAE enabled.)

              DirectMap2M %lu (since Linux 2.6.27)
                     Number of bytes of RAM linearly mapped by kernel in
                     2 MB pages.  (x86 with neither CONFIG_X86_64 nor
                     CONFIG_X86_PAE enabled.)

              DirectMap1G %lu (since Linux 2.6.27)
                     (x86 with CONFIG_X86_64 and
                     CONFIG_X86_DIRECT_GBPAGES enabled.)
```

### Virtual memory primer

- reference: https://docs.kernel.org/admin-guide/mm/concepts.html#virtual-memory-primer
- reference: Understanding the Linux Virtual Memory Manager: https://www.kernel.org/doc/gorman/html/understand/

The physical memory in a computer system is a limited resource and even for systems that support memory hotplug there is a hard limit on the amount of memory that can be installed. The physical memory is not necessarily contiguous; it might be accessible as a set of distinct address ranges. Besides, different CPU architectures, and even different implementations of the same architecture have different views of how these address ranges are defined.

All this makes dealing directly with physical memory quite complex and to avoid this complexity a concept of virtual memory was developed.

The virtual memory abstracts the details of physical memory from the application software, allows to keep only needed information in the physical memory (demand paging) and provides a mechanism for the protection and controlled sharing of data between processes.

With virtual memory, each and every memory access uses a virtual address. When the CPU decodes an instruction that reads (or writes) from (or to) the system memory, it translates the virtual address encoded in that instruction to a physical address that the memory controller can understand.

The physical system memory is divided into page frames, or pages. The size of each page is architecture specific. Some architectures allow selection of the page size from several supported values; this selection is performed at the kernel build time by setting an appropriate kernel configuration option.

Each physical memory page can be mapped as one or more virtual pages. These mappings are described by page tables that allow translation from a virtual address used by programs to the physical memory address. The page tables are organized hierarchically.

The tables at the lowest level of the hierarchy contain physical addresses of actual pages used by the software. The tables at higher levels contain physical addresses of the pages belonging to the lower levels. The pointer to the top level page table resides in a register. When the CPU performs the address translation, it uses this register to access the top level page table. The high bits of the virtual address are used to index an entry in the top level page table. That entry is then used to access the next level in the hierarchy with the next bits of the virtual address as the index to that level page table. The lowest bits in the virtual address define the offset inside the actual page.


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

WATCH OUT! because the SLAB allocator is in the list to be deprecated: https://www.phoronix.com/news/Linux-Deprecating-Removing-SLAB


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


### Zones

- reference: https://docs.kernel.org/admin-guide/mm/concepts.html#zones
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


### virtual kernel memory layout

x86 (32-bits) : You can see in 

```
dmesg | grep -A 10 'virtual kernel memory layout'
```
This is only for 32-bit machine


x86_64: Documentation/x86/x86_64/mm.rst

#### Can I use virt_to_phys for user space memory in kernel module? or Can I use virt_to_phys to get the physical address returned by malloc?

`virt_to_phys`: The returned physical address is the physical (CPU) mapping for the memory address given. It is only valid to use this function on addresses directly mapped or allocated via `kmalloc`. It means It is used by the kernel to translate kernel virtual address (not user virtual address) to physical address.

Example: 

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");

static void *ptr;
int alloc_size = 1024;

static int test_hello_init(void)
{
	phys_addr_t physical_address;
	ptr = kmalloc(alloc_size,GFP_DMA);
	pr_info("Virtual Address DMA:%px\n", ptr);
	physical_address = virt_to_phys(ptr);
	pr_info("Physical Address DMA:%pa\n", &physical_address);
	kfree(ptr);
	ptr = kmalloc(alloc_size,GFP_DMA32);
	pr_info("Virtual Address DMA32:%px\n", ptr);
	physical_address = virt_to_phys(ptr);
	pr_info("Physical Address DMA32:%pa\n", &physical_address);
	kfree(ptr);
	return -1;
}

static void test_hello_exit(void) { }

module_init(test_hello_init);
module_exit(test_hello_exit);
```

### What is the maximum size allocatable using kmalloc?

The upper limit (number of bytes that can be allocated in a single kmalloc request), is a function of:
 - the processor – really, the page size – and
 - the number of buddy system freelists (MAX_ORDER).

On both x86 and ARM, with a standard page size of 4 Kb and MAX_ORDER of 11


@slab.h:
```
#define KMALLOC_SHIFT_MAX       (MAX_ORDER + PAGE_SHIFT - 1)

MAX_ORDER = 11 , PAGE_SHIFT = 12 = 11 + 12 -1 = 22

/* Maximum allocatable size */
#define KMALLOC_MAX_SIZE        (1UL << KMALLOC_SHIFT_MAX) = 2^22 = 4*1024*1024 = 4MB
```

Example:
```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

static void *ptr;
unsigned int alloc_size = 1024;
unsigned int loop  = 8192;
module_param(loop, uint, 0);

static int test_hello_init(void)
{
	int i;
	for(i=1; i < loop; i++) {
		ptr = kmalloc(alloc_size*i, GFP_KERNEL);
		if(!ptr) {
			/* handle error */
			pr_err("memory allocation failed\n");
			return -ENOMEM;
		} else {
			pr_info("Memory allocated of size:%uKB successfully:%px\n", i, ptr);
			kfree(ptr);
			pr_info("Memory freed\n");
		}
	}
	return -1;
}

static void test_hello_exit(void) { }

module_init(test_hello_init);
module_exit(test_hello_exit);
```

By the way, `kmalloc(0)` returns a special `ZERO_SIZE_PTR` value. 

It is a non-NULL value which looks like a legitimate pointer, but which causes a fault on any attempt at dereferencing it.
Any attempt to call `kfree()` with this special value will do the right thing, of course.

 
### What happens if we don't free the memory allocated by kmalloc?

A memory leak will happen. With `malloc`, when the program finish, the memory is returned, but in case of `kmalloc` that is not the case. The memory of the kernel will not be freed.


### ksize

`kmalloc` will internally round up allocations and return more memory than requested.

`ksize()` can be used to determine the actual amount of memory allocated.

The caller may use this additional memory, even though  a smaller amount of memory was initially specified with the kmalloc call.

This function is not often needed; callers to `kmalloc()` usually know what they allocated. It can be useful, though, in situations where a function needs to know the size of an object and does not have that information handy.

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

static void *ptr;

static int test_hello_init(void)
{
        ptr = kmalloc(1, GFP_KERNEL);
        printk("I got: %zu bytes of memory\n", ksize(ptr));
        kfree(ptr);
        ptr = kmalloc(8, GFP_KERNEL);
        printk("I got: %zu bytes of memory\n", ksize(ptr));
        kfree(ptr);
        ptr = kmalloc(8080, GFP_KERNEL);
        printk("I got: %zu bytes of memory\n", ksize(ptr));
        kfree(ptr);
        ptr = kmalloc(8192, GFP_KERNEL);
        printk("I got: %zu bytes of memory\n", ksize(ptr));
        kfree(ptr);
	return -1;  // module installation will fail.
}

static void test_hello_exit(void)
{ }

module_init(test_hello_init);
module_exit(test_hello_exit);
```
You can check with:

```
$ sudo cat /proc/slabinfo 
```

### kzalloc 

`kzalloc` works like kmalloc, but also zero the memory.

```
void *kzalloc(size_t size, gfp_t flags);
```

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");

static char *ptr;
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
		pr_info("Memory allocated successfully:%px\n", ptr);
		pr_info("Content of ptr+2 is %d\n", *(ptr+2));
		pr_info("Content of ptr+102 is %d\n", *(ptr+102));
                // the values with kmallow will be garbage!
	}
	kfree(ptr);
	ptr = kzalloc(alloc_size,GFP_ATOMIC);
	if(!ptr) {
		/* handle error */
		pr_err("memory allocation failed\n");
		return -ENOMEM;
	} else {
		pr_info("Memory allocated successfully:%px\n", ptr);
		pr_info("Content of ptr+2 is %d\n", *(ptr+2));
		pr_info("Content of ptr+102 is %d\n", *(ptr+102));
                // the values with kzalloc will be zeroes.
	}
	kfree(ptr);

	return -1;
}

static void test_hello_exit(void)
{ }

module_init(test_hello_init);
module_exit(test_hello_exit);
```

### krealloc

Memory allocated by `kmalloc()` can be resized by:

```
void *krealloc(const void *p, size_t new_size, gfp_t flags);
```

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

static void *addr;

static int test_hello_init(void)
{
	addr = kmalloc(4096, GFP_KERNEL);
        printk("I got: %zu bytes of memory\n", ksize(addr));
        addr = krealloc(addr, 8192, GFP_KERNEL);
        printk("I got: %zu bytes of memory\n", ksize(addr));
        kfree(addr);
	return -1;
}

static void test_hello_exit(void)
{ }

module_init(test_hello_init);
module_exit(test_hello_exit);
```

### kmalloc example of continuos memory

The `kmalloc()` function returns physically and virtually contiguous memory.

Physically contiguous memory has two primary benefits.
        1.  Many hardware devices cannot address virtual memory.
        2.  A physically contiguous block of memory can use a single large page mapping. This minimizes the translation lookaside buffer (TLB) overhead of addressing the memory

Allocating physically contiguous memory has one downside: it is often hard to find physically contiguous blocks of memory, especially for large allocations

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");

static char *ptr;
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
		pr_info("Memory allocated successfully:%px\t%px\n", ptr, ptr+100);
		pr_info("Physical address:%llx\t %llx\n", virt_to_phys(ptr), virt_to_phys(ptr+100));
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

### vmalloc

Memory returned by `vmalloc()` is only contiguous in virtual memory and not in physical memory

Memory allcoated with `vmalloc()`is freed with `vfree()` 

```

			virtual memory    physical memory
			----------        --------
		   - - -|	 |--------|	 |
	vmalloc	  /	|	 |        |	 |
	---------/	|        |--------|	 |
	|	|	|        |\       |	 |
	|	|   ---	|        | \	  | 	 |
	|	|  /	|        |\ ----- |	 |
	|	| /	|        | \	  |	 |
	---------/	|        |  ------|	 |
			|        |	  |	 | 
			|        |        |      |
			|        |        |      |
			|        |        |      |
			|        |        |      |
			----------        --------

```

The returned memory always comes from HIGH_MEM zone. 

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/vmalloc.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");

static char *ptr;
int alloc_size = 4096*1234;

static int test_hello_init(void)
{
	ptr = vmalloc(alloc_size);
	if(!ptr) {
		/* handle error */
		pr_err("memory allocation failed\n");
		return -ENOMEM;
	} else {
		pr_info("Physical address:%px\t Virtual Address:%llx\n", 
				ptr+4096, virt_to_phys(ptr+(4096*1234)));
	}
	return 0;
}

static void test_hello_exit(void)
{
	vfree(ptr);
	pr_info("Memory freed\n");
}

module_init(test_hello_init);
module_exit(test_hello_exit);
```

#### What is the maximum size allocatable using vmalloc?

The max allocatable mem size for Kmalloc was 4MB, as we saw previously. But what is the max allocatable mem with vmalloc?


```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/vmalloc.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");

static void *ptr;
unsigned int alloc_size = 1024*1024;//1MB
unsigned int loop = 8192;
module_param(loop, uint, 0);

static int test_hello_init(void)
{
	int i;
	for(i = 1; i < loop; i++) {
		ptr = vmalloc(alloc_size*i);
		if(!ptr) {
			/* handle error */
			pr_err("memory allocation failed\n");
			return -ENOMEM;
		} else {
			pr_info("Memory allocated of size:%uMB successfully:%px\n", i, ptr);
			vfree(ptr);
			pr_info("Memory freed\n");
		}
	}
	return -1;
}

static void test_hello_exit(void)
{ }

module_init(test_hello_init);
module_exit(test_hello_exit);
```

The `vmalloc` upper limit is, in theory, the amount of physical RAM on the system.

Kernel reserves an architecture (cpu) specific “range” of virtual memory for the purpose of vmalloc: from `VMALLOC_START` to `VMALLOC_END`.

```
Header file: <asm/pgtable.h>
```


```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/vmalloc.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <asm/pgtable.h>
#include <linux/mm.h>

MODULE_LICENSE("GPL");


static int test_hello_init(void)
{
	pr_info("Vmalloc start:%lx\n", VMALLOC_START);
	pr_info("Vmalloc end:%lx\n", VMALLOC_END);
	pr_info("Vmalloc size:%d MB\n", (VMALLOC_END - VMALLOC_START)/(1024*1024));
	return -1; // module init will fail.
}

static void test_hello_exit(void)
{ }

module_init(test_hello_init);
module_exit(test_hello_exit);
```

#### Can i use ksize with vmalloc?

According to the documentation, "The caller must guarantee that objp points to a valid object previously allocated with either kmalloc() or kmem_cache_alloc()." 


### Differences between vmalloc and kmalloc


1. Physical Memory:
 - kmalloc: Guarantees the pages are physically contiguous and virtually contiguous
 - vmalloc: It allocates virtually contiguous but not necessarily physically contiguous

2. Low Mem vs High Mem:
 - kmalloc: Returns from Low Memory
 - vmalloc: Returns from High Memory	

3. Usage:
 - kmalloc: Memory returned Can  be used by hardware devices(DMA, PCI)
 - vmalloc: Memory returned Cannot be used by hardware devices

4. Interrupt Context:
 - kmalloc: can be used in interrupt context with 'GFP_ATOMIC'
 - vmalloc: cannot be used in interrupt context

5. Allocator:
 - kmalloc: Uses slab allocator which in turn use Page Allocator
 - vmalloc: Directly uses Page Allocator

6. Overhead:
 - kmalloc: less overhead
 - vmalloc: more overhead, as each vmalloc requires page table changes and a translation look aside buffer invalidation.

7. Size:
 - kmalloc: Cannot give large memory
 - vmalloc: Useful for allocating large memory and no requirement of physical contiguous


### kmalloc(0)

`kmalloc(0)` returns a special ZERO_SIZE_PTR value. 

It is a non-NULL value which looks like a legitimate pointer, but which causes a fault on any attempt at dereferencing it.
 Any attempt to call `kfree()` with this special value will do the right thing, of course.


```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");

static int *ptr;

static int test_hello_init(void)
{
	ptr = kmalloc(0,GFP_KERNEL);
	if (ptr) {
		pr_info("Memory Allocated:%px\n", ptr);
		kfree(ptr);
	} else {
		pr_info("Memory not allocated\n");
	}
	return -1; // module init will fail!
}

static void test_hello_exit(void)
{ }

module_init(test_hello_init);
module_exit(test_hello_exit);
```

### vmalloc(0)

```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/vmalloc.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");

static int *ptr;

static int test_hello_init(void)
{
	ptr = vmalloc(0);
	if (ptr) {
		pr_info("Memory Allocated:%px\n", ptr);
		vfree(ptr);
	} else {
		pr_info("Memory not allocated\n");
	}
	return -1; // mdoule init will fail!
}

static void test_hello_exit(void)
{ }

module_init(test_hello_init);
module_exit(test_hello_exit);
```

`vmalloc(0)` will fail.

### Kernel Stack

In a Linux System, every process has 2 stacks:
 - User stack
 - Kernel stack

 - User Stack in x86: Resides in user address space (0-3GB in 32-bit x86)
 - Kernel Stack in x86: Resides in kernel address space(3GB-4GB in 32-bit x86)

User space is afforded the luxury of a large, dynamically growing stack, whereas the kernel has no such luxury

The kernel's stack is small and fixed.

Size of the per-process kernel stacks depends on both the architecture and a compile-time option.

When the option is enabled, each process is given only a single page - 4KB on 32-bit architectures and 8KB on 64-bit architectures.

Why only one page?
  1. Less memory consumption per process
  2. As uptime increases, it becomes increasingly hard to find two physically contiguous unallocated pages.

Historically, interrupt handlers also used the kernel stack of the process they interrupted.

As it placed tighter constraints on the already smaller kernel stack. kernel developers implemented a new feature: interrupt stacks. Interrupts use their own stacks. It consumes only a single page per processor.

Now, we have a kernel stack size of 16KB from Linux 3.15 in x86_64


### CONFIG_FRAME_WARN

This kernel configuration option passes an option to the compiler to cause it to emit a warning when a static stack size for a routine is detected that is larger than the specified threshold.

It requires gcc version 4.4 or later in order to work

The gcc option used is "-Wframe-larger-than=xxx".

By default, CONFIG_FRAME_WARN has the value of 1024, but you can set it to any value from 0 to 8192.

Linux kernel defines stack size 8192 bytes for each process. the sum of the stack frames of all active functions.
should not overflow 8192 bytes.

This warning does not guarantee that you will overflow the stack space; it just shows that this function makes an overflow more likely (when used together with other big-frame functions, or with many smaller functions).

### checkstack.pl

There's a way to get a list of how much stack space each function in your program uses

`checkstack.pl`

It prints out a list of functions and their stack usage, biggest first	

```
$ objdump -D hello.ko | perl ~/linux-5.2.8/scripts/checkstack.pl
```

Note: it can't take into account recursive functions. It only performs static analysis
