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




