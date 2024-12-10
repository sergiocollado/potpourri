# Notes on timers and time management on the Linux Kernel


## Hz

The Linux's kernel works on timer interrupts. The frequency of the timer interrupt is defined on system boot on the preprocessor `define HZ`

So if HZ = 100, the frequency would be 100Hz, so the interrupt happens every 1/100 seconds, that is 100ms. 

The value of `HZ` changes for every architecture. It is defined in <asm/param.h> https://elixir.bootlin.com/linux/v6.12.4/A/ident/HZ

The `HZ` value can be checked in your system with: `$grep 'CONFIG_HZ=' /boot/config-$(uname -r)` 

