# Notes on memory management on Linux kernel

 - reference: https://linux-kernel-labs.github.io/refs/heads/master/lectures/address-space.html
 - reference: https://linux-kernel-labs.github.io/refs/heads/master/lectures/memory-management.html

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
