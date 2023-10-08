   #include <stdio.h>                                                               
                                                                                    
   int main() {                                                                     
          int i = 0;                                                               
          while (i < 6) {                                                          
                 printf("i equals to: %d\n", i);                                  
                 ++i;                                                             
          }                                                                        
          __asm__("int3"); // int3 is an trap that captures a breakpoint                                                         
   }     

/**
sergio@laptop:~/repos/divide-by-zero$ gcc -o int3 interrupt.c 
sergio@laptop:sudo dmesg -WH &
i equals to: 0
i equals to: 1
i equals to: 2
i equals to: 3
i equals to: 4
i equals to: 5
[  +1,920005] traps: int3[7075] trap int3 ip:55f6a6900182 sp:7ffdc37606c0 error:0 in int3[55f6a6900000+1000]
Trace/breakpoint trap (core dumped)

but if we debug the program with gcc:

sergio@laptop:~/repos/divide-by-zero$ gdb ./int3 
GNU gdb (Ubuntu 12.1-3ubuntu2) 12.1
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./int3...

This GDB supports auto-downloading debuginfo from the following URLs:
https://debuginfod.ubuntu.com 
Enable debuginfod for this session? (y or [n]) y
Debuginfod has been enabled.
To make this setting permanent, add 'set debuginfod enabled on' to .gdbinit.
(No debugging symbols found in ./int3)
(gdb) run
Starting program: /home/sergio/repos/divide-by-zero/int3 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
i equals to: 0
i equals to: 1
i equals to: 2
i equals to: 3
i equals to: 4
i equals to: 5

Program received signal SIGTRAP, Trace/breakpoint trap.
0x0000555555555182 in main ()
(gdb) 
the program was ran, and stoped by itself at the int3 (breakpoint trap)

if we continue the program, it will exit normally:

Program received signal SIGTRAP, Trace/breakpoint trap.
0x0000555555555182 in main ()
(gdb) c
Continuing.
[Inferior 1 (process 7187) exited normally]
**/
