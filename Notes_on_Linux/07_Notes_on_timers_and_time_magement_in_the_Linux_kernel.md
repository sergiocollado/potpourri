# Notes on timers and time management on the Linux Kernel


## Hz

The Linux's kernel works on timer interrupts. The frequency of the timer interrupt is defined on system boot on the preprocessor `define HZ`

So if HZ = 100, the frequency would be 100Hz, so the interrupt happens every 1/100 seconds, that is 100ms. 

The value of `HZ` changes for every architecture. It is defined in <asm/param.h> 

```C
/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __ASM_GENERIC_PARAM_H
#define __ASM_GENERIC_PARAM_H

#include <uapi/asm-generic/param.h>

# undef HZ
# define HZ		CONFIG_HZ	/* Internal kernel timer frequency */
# define USER_HZ	100		/* some user interfaces are */
# define CLOCKS_PER_SEC	(USER_HZ)       /* in "ticks" like times() */
#endif /* __ASM_GENERIC_PARAM_H */
```

Also check: https://elixir.bootlin.com/linux/v6.12.4/A/ident/HZ

The `HZ` value can be checked in your system with: `$grep 'CONFIG_HZ=' /boot/config-$(uname -r)` 

## Jiffies

The kernel mantains a global variable called "jiffies" which holds the number of ticks/timer interrupts from the system boot. 

Every time a time interrupt happens, the value of an internal kernel counter is incremented. 

 - header file: <linux/jiffies.h>

```
extern unsigned long volatile jiffies
```

- check at: https://elixir.bootlin.com/linux/v6.12/A/ident/jiffies

The size of jiffies is:
- in 32-bit architecture: 4 bytes
- in 64-bit architecture: 8 bytes

So, if the tick rate (HZ) is 100, 32-bit jiffies will overflow in 497 days, but if the tick rate (HZ) is 1000, it will overflow in 49.7 days. 

So one solution to avoid overflow is to store the jiffies in a 64-bit variable on all architectures. 

The question arises: why `jiffies` have not directly declared as 64-bit `unsigned long long integer` on x86, but as an `unsigned log` that has a differnent size on 32-bit and 64-bit architectures? 

The answer is that the access to 64-bit variables in 32-bit architectures cannot be done atomically. 

Every read operation on the whole 64-bit requieres some synchronization technique to ensure that the counter is updated while the two 32-bit halves counters are read. 

A second variable is also defined at: <linux/jiffies.h>

```
extern u64 jiffies_64;
```

The ld(1) script used to link the main kernel image (arch/x86/kernel/vmlinux.lds.S on x86) then overlays the jiffies variable over the start of the jiffiies_64 variables.

