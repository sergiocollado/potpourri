# NOTES ON LINUX DEVICE DRIVERS

## What is a device driver.

A device driver is a code, that contrals a given tye of device in the compuer.

A device driver has three sides
- one side talks to the kernen
- one side talks to the hardware
- one side talks to the user. 

## What is a kernel module?

Tradicionaly the way to add code to the kernel was to recompile the kernel and reboot the system.

Kernel modules, are a piece of ccode that can be load/inserted  and unloaded/removed form the kernel whenever needed.

It can be refered by other names:

- Loadable kernel modules (LKM)
- Modules

Its extension is .ko (Kernel Object)

## Standard location for kernel modules

Modules are located in the /lib/modules/<kernel version> direcory of the rootfs by default

to check them: 

```
cd /lib/modules/`uname -r`/
finx . -name '*.ko' | wc -l # to count the number of kernel modules
```

## Device drivers vs kernel modules

A kernel module doesn't have to be a device driver. 

A driver is like a sub-class of module

modules are used for:
- device drivers
- file system
- system calls
- network drivers: dirvers implementing a network protocol
- tty line disciplines: for terminal devices

## Advantages of kernel modules

1. All parts of the base kernel stay loaded all the time. Modules can save you memory, becasue they are loaded only
when they are requested to be loaded.

2. User would need to rebuild and reboot the kernel every time they would requier a new funcionality

3. A bug in driver which is compiled as a part of kernel will sotp system from loading, whereas module allows systems to load. 

4. Faster to mantain and debug

5. Makes it easier to manatain multiple machines on a single kernel base

## Disadvanteges of kernel modules

1. Size: Moudle management consumes unpeable kernel memory. A basic kernel with a number of modules loaded will consume more memory than an equivalen kernel with the dirvers compiled into th ekernel image itself. This can be an issue on machines with limited physical memory

2. As the kernel modules are loaded very late in the boot process, hence core funcionality has to go 
in the vase kernel (e.g. memory management)

3. Security. if you build your kernel statically and disalbe linux's dynamic module loading feature, youprevent runn-time 
modification of the kernel code.

## Configuration

In orden to suppor module, the kernel must have been build, with the following option enabled:

CONFIG_MODULES=y

```
cd /boot
cat config-`uname -r` | grep CONFIG_MODULES
```

## Types of modules

- In-source tree: modules present in the linux kernel source code
- Out-of-tree: modules not present in the linux kernel 

All modules start out as "out-of-tree" developments, that can be compiled using the 
condtex of a source-tree. 

Once a module gets accepted to be included, it becomes an in-tree module.

## Basic commands

- lsmod: List modules, lsmod ges its information by reading the file /proc/module (previously) or /sys/module
- modinfo: module information, prints the information of the module
- insmod: used like: `sudo insmod ./mymodule.ko` to load modules
- modprobe: add or remove modules
- rmmod: to remove modules

## Hello World kernel module
  
  In C/C++ programming the main() function is the entry point and exit point
  
  Kernel modules must have al least two funcions:
  - a start (initialization function): which is called when the module is loaded into the kernel
  - an end funcion (cleanup), which is called just befor it si removed
  
  This is done with the module_init() and module_exit() macros
  
 ### Licensing
  
  Module should specify which license you are using MODULE_LICENSE() macro
  
  - "GPL" GNU plublic lincese v2 or later
  - GPL v2
  - GPL and addictional rights
  - Dual BSD/GPL
  - Dual MIT/GPL
  - Dual MPL/GPL
  - Propietary (non-free-modules)
  
  In case a module doesn't specify a license, it can be compiled, although it will report a warning. It will be able to be loaded into the kernel, but reporting `module license unspecified taints kernel`.
  
  In case an incorrect license is defined, it will compile, but when the module is loaded, it will report that the kernel is tainted. 
  
  
### Tainted kernel
  
  A taint kernel, means that it is not supported by the community. On top of that, some debuggin functionallyty and API calls may be disalbe when the kernel is tainted.
  
  The kernel may became tainted by several reasons:
   - uses of propietary license
   - use of stagin drivers (which are part of the kernel source code but not fully tested)
   - use of out-of-tree modules that are not include with the linux kernel source code
   - certain critical error conditions, such machine check exceptions and kernel oopses.
  
To check if a given moudle is tainted, check the file `/proc/sys/kernel/tainted`. If it retursn 0, the
kernel is not tainted, any other number, indicates the reason it why it is. To decode that number use
the script `kernel-chktaint`:  https://git.kernel.org/pub/scm/linux/kernel/git/torvals/linux.git/plain/tools/debugging/kerenl-chktaint
  
### Header files
  
  All kernel modules needs to include `linux/module.h` for macro expansion of module_init and module_exit.
  
  `linux/kernel.h` only for the macro expansion for the printk() log level.
  
### HelloWorldModule.c
  
```
#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros __init __exit */
  
  MODULE_LICENSE("GPL")
  
  static int __init test_hello_init(void)
  {
      printk(KERN_INFO "%s: In init\n", __func__);
      return 0;
  }
  
  static void __exit test_hello_exit(void)
  {
       printk(KERN_INFO "%s: In exit\n", __func__);
  }
  
  module_init(test_hello_init);
  module_exit(test_hello_exit);
```
  
### Compiling it
  
To compiile the module, the kermel make file is needed
  
```
ls /lib/modules/'uname -r'/bulid/Makefile
```
  
use the make, with the -C option, that indicates to use the makefile indicated in the folder by -C
  
``` 
make -C /lib/modules/`uname -r/build/
``` 
just this, will not be enought. this makefile uses a makefile, so a small makefile needs to be added
  
 
```
cat Makefile
obj-m := hello.o
```
 
obj-m : stands for module. 
  
```
make -C /lib/modules/'uname -r'/build/ M={PWD} modules
```
 
The file .ko, should be generated 
 
At to this point, this is an out-of-tree module. To load it to the kernel, the 'insmod' command is used.
  
```
sudo insmod ./helloWorld.ko
lsmod # to check if the module indeed has been loaded
sudo rmmod helloWorld # to remove the module
```
  
In the code there is a 'printk', this is not printed in the console, for that the command 'dmesg' is needed.
  

### Compile and clean module commands

 To build a module, use:
 ```
  make -C /lib/modules/`uname -r`/build M=${PWD} modules
 ```
  
 T clean the module: 
 ```
  make -C /lib/modules/`uname -r`/build M=${PWD} clean
 ```
  
The `-C` option state to to change the directory provided, instead of using the current directory use the one provided by the -C option.
  
The `M=` argument causes the Makefile tomove back into your module source directory before trying to build modules. 
  
The kernel Makefile will read the local makefile to findout what to build, this is indicated by writing: obj-m +=HelloWorldModule.o

### Cross compiling kernel modules
    
It is possible to emulate other architectures with QUEMU, and make developments for those other architectures, for that we need to cross compile.
  
There are two variables that the kernel uses to select the target architecture: 
  - ARCH
  - CROSS_COMPILE
  
The default vaues for both are found in the top-level Makefile and the values of both may be overridden on the command line.
  
ARCH: architecture targetes as the kernel knows it.
  
CROSS_COMPILE: set this to the prefix of your toolchain (including the trailing dash "-")
So if the toolchain is invoked as say x86_64-pc-linux-gnu-gcc, just remove the trailing gcc and that is what should be used: `x86_64-pc-linux-gnu-`.
  
example:
```
$ make ARCH=arm CROSS_COMPILE=arm-buildroot-linux-uclibgnueabi- -C /home/..../..../output/build/linux-X.Y:Z m=${PWD} modules  
```

 ### Overview of compiling kernel modules
  
  Kernel use the kbuild system to build the kernel modules. The kbuild system reads the assignment of `obj-m := modulename.o` from the local makefile. The the kbuild system knows that it has to build the "modulename.o" and will look for "modulename.c" for the source. 
  
   In case the files are not pressent in the directory passsed to `M=`, the compiling will stop with an error. If the files are present the source file is compiled to a modulename.", and "modulename.mod.c" is created which is compiled to "modulename.mod.o"
  
  The modulename.mod.c is a file that basically contains the information about th emodule (Version information etc)  
  
  The mdoulename.o and the modulename.mod.o are linekd together by modpost in the next stage to create the "modulename.ko"
  
  The file "module.symvers" will contain any of the external symobls that is defined in your module and not present in the module.symvers of the kernel.
  
  The file "modules.order" is used in case several modules are compiled together, it will list out th eorder in which the compiilation and createion of .ko is done. 
  
  
 ### Printk
  
`printf()` is a function from the standard C library. `printk()` is a kernel level function.
  
`printk' function is called with one argumet:
  
 ```
 printk(KERN_log_prority "hello world!");
 ```
 The log_priority is one of eight values, predefined in linx/kernel.h,
  
 - EMERG, ALERT, CRIT, ERR, WARNING, NOTICE, INFO, DEBUG
  
 `printk()`writes in the kernel buffer.
  
### Simplified makefile
  
So to build a module, the command is use:
  
```
make -C /lib/modules/`uname -r`/build/build M=${PWD} modules
```
  
and to clean the module, the command:
  
```
make -C /lib/modules/ùname -r/build M=${PWD} clean
```

This is a bit bothersome, so a new makefile can be used:
  
```
obj-m := hello.o
  
all:
   make -C /lib/modules/`uname -r`/build/build M=${PWD} modules
  
clean:
   make -C /lib/modules/`uname -r`/build M=${PWD} clean
```

### What happens when we do insmod in a module
  
  The kernel module is a piece of kernel code (.ko in elf format) which can be added to the running kernel, and when loaded can be removed from the kernel.
  
1- It calls init_Module() to inform the querken that a module is attemp to be loaded an transfers the control to the kernel 
  
2- In the kernel, `sys_init_module()`is run. It does the following operations
  - Verify that the user has the permissions to load the moduel
  - The load_module function is called
  - The load_module function assigns temporary memory and copies the elf module from the user space to kernel memory using 'copy_from_user'.
  - Checks the sanity of the ELF file.
  - Based on the ELF file interpretation, it generates offset in the temporary memory space allocated. This is called the convenience variables
  - User arguments to the module are also copied to the kernel memory
  - Symbol resolution is done
  - The load_module function returns a reference to the kernel module.
  - The reference to the module returned by load_module is added to a doubly linked list that has a list of all the modules loaded in the system.
  
  
### What happens if a -1 is returned from the init function.
  
Tradicionaly in linux a function that returns zero means success, and a non zero means failure.
  
The loading of the module would fail, and the module will not be loaded. It can be tested with lsmod.
  
### How to give another name to a module.

modify the makefile like:
  
```
obj-m := linux.o
linux-objs := hello.o
  
all:
   make -C /lib/modules/`uname -r`/build/build M=${PWD} modules
  
clean:
   make -C /lib/modules/`uname -r`/build M=${PWD} clean  
```
  
if we check the name of the modules, with lsmode, we would find the linux module
  
### Module composed of several files
 
We can have a module in several files. For example:
  
HelloWorldModule.c:
  
```
  #include <linux/kernel>
  #include <linux/module>
  
  MODULE_LICENSE("GPL")
  
  static int __init test_hello_init(void)
  {
      printk(KERN_INFO "%s: In init\n", __func__);
      furnc();
      return 0;
  }
  
  static void __exit test_hello_exit(void)
  {
       printk(KERN_INFO "%s: In exit\n", __func__);
  }
  
  module_init(test_hello_init);
  module_exit(test_hello_exit);
```
 
and the file func.c:
```
#include <linux/kernel.h>
void func(void)
{
    printk(KERN_INFO "Hey there!");
}
```

The module must be udpated, to add the file:
  
```
obj-m := linux.o
linux-objs := hello.o func.o
  
all:
   make -C /lib/modules/`uname -r`/build/build M=${PWD} modules
  
clean:
   make -C /lib/modules/`name -r`/build M=${PWD} clean  
```

### Two kernel modules in a single makefile

You can use a single makefile to generate more than one modules.

  ```
obj-m := hello1.o
obj-m += hello2.o
# or also obj-m := hello1.o hello2.o

all:
   make -C /lib/modules/`uname -r`/build/build M=${PWD} modules
  
clean:
   make -C /lib/modules/`uname -r`/build M=${PWD} clean  
```

### dmesg command
  
`dmesg` is used to control or print the kernel ring buffer, that has the log of the kernel eveents
  
The kernel keeps all the event logs in a ring bugger. This is done to avoid the boot logs being lost until the syslog daemon starts and collects them and stores them in /var/log/dmesg.
  
- to clear the ring buffer. You may need to lauch it with sudo (for permissions)
 ```
  dmesg -c # will clear the ring buffer after printing (by default in the console). C stands for Clear
  dmesg -C # will clear the ring buffer, but will not print its contents
 ```

- to don't print the time stamps
 ```
  dmesg -t # will not print the timestamps
 ```
- restrict dmesg command to list of levels
 ```
  dmesg -l err,warn # will print only error and warn messages
 ```
- print human readable timestamps
 ```
  dmesg -T # will print timestamps in readable format. watch out! the timestamp could be inaccurate.
 ```
- Display the log level in the output
 ```
  dmesg  -x # will print the log level in the output
 ```
- You can combine the options, so dmesg -Tx will print both human friendly and loglevel
 ```
  dmesg -Tx
 ```
- To follow/update messages
 ```
  dmesg -w & # the & is to run it in background. 
 ``` 

### kernel module without an exit function?
  
When the is not exit function, the module will not be possible to be removed. When try to be removed, it
will report an EBUSY module. This is defined in `kernel/module.c` at `SYSCALL_DEFINE2(delete_module, ...`
  
### kernel module without an init function?
  
The module may be loaded, but it will do nothing at the beginig. This is defined at kernel/module.c at `SYSCALL_DEFINE3(init_module, ...`

### insmod vs modprove
  
- `insmod` loads the module given 0insmod /path/to/module.ko' 
- `modprobe` loads the module only in /lib/moduels/$(uname -r) 'modprobe /home/test/hello.ko' will not work
  
- `insmod` dependencies if present are not loaded
- `modprobe` calculates dependencies, and loads the dependencies and then the main module.
  
`modprobe` depends on the tool `depmod`to calculate the dependencies. `depmod` calculates the dependencies of all the modules present in /lib/modules/$(uname -r) folder, and places the dependencies information in /lib/modules/$(uname -r)/modules.dep file. See `man depmod`.
  
 It is possible to reload the modules.dep file with `depmod -a`
  
### Understanding module_init & module_exit functions
  
 On `insmod` the function passed in the `module_init` is called, and on `rmmod` the argument passed in `module_exit` is called
  
 Lets review the definiton of thos macros, defined in linux/module.h
  
 ```
  /* Each module must use one moude_init(). */
  #define module_init(intifn)                \
      static inline intcall_t __inittest(void)      \
      { return initfn; }           \
      int init_module(void) __attribute__((alias(#initfn)));
  
  /* This is only required if you wnat to be unloadable. */
  #define module_exit(exitfn)          \
      static inline exitcallt_t __exittest(void)     \
      { return extinfn; }           \
      void cleanup_module(void) __attribute__((alias(#exitfn)));
 ```
 
The purpose of defining `__inittest` function is to check during compile time, the function passed to `module_init()` macro is compatible wit the `initcall_t` type
  
`initcall_t` is defined in linux/init.h (is defined as a function pointer)
  
  ```
  typedef int (*initcall_t)(void);
  ```
  
 If it is declared a module_init functino which returns void instead of int, the compiler will thrown a warning
  
  The gcc attribuete alias is used to sepcify multiple aliases (other names) for a given symbol (function/variable)  
  
  The `alias` attribute of gcc is used to assign another name to the init module, so you can have a better name for tye driver. ( eg. cdrom_inint instead of initd_modue), so not each driver has a init_module named function. 
  
  It would be possible to create a module without a module_init or module_exit functions, if the module had init_module(void) and cleanup_module(void) functions. But we would lost the chance to have dedicated names for those functions. 

 ### Passing parameters to kernel modules
  
 It is possilbe to pass parameters to a modules. Passing pametes may be intersting to change the behavior of the module, for example to enable/disable debug logs, or tu suppor different workgin modes. 
  
  Passing parameters to a module is declared in moduleparam.h file
  
  ```
  #define module_params(name, type, perm)
     module_param_named(name, name, type, perm)
  ```
  
  name: name of the variable <br>
  type: type of the variable. Supported types are charp (char pointer) , bool, invbool (inverse bool), long, chort, uint, unlong, ushort <br>
  per: permissions fo rthe sysfs entry <br>
  EgS_IRUGO: Only read by all users <br>
         0 : No sysfs entry <br>
  It is possible to use numberic values line 0644 for permissions entry.
  
  Example: 
  ```
  #include <linux/kernel.h>
  #include <linux/module.h>
  
  MODULE_LICENSE("GPL");
  char* name = "Embedded";
  int loop_count = 1;
  module_param(name, charp, S_IRUGO);
  module_param(loop_count, int, S_IRUGO);
  
  static int test_arguments_init(void) 
  {
      int i; 
      printk(KERN_INFO"%s: In init\n", __func__);
      printk(KERN_INFO"%s: Loop count: %d\n", __func__, loop_count);
      for( i = 0; i < loop_count; i++) 
          printk(KERN_INFO"%s: Hi %s\n", __func__, name);
      return 0;
  }
                                 
  static void test_arguments_exit(void)
  {
       printk(KERN_INFO"%s: In exit\n", __func__);                              
  }
  
  module_init(test_arguments_init);
  module_exit(test_arguments_exit);
  MODULE_AUTHOR("Nemo");
  MODULE_DESCRIPTION("Arguments Passing Example");
  ```
  
  This module can be tested with:
                                 
 ```
 sudo dmesg -C
 sudo insmod ./arguments.ko
 dmesg                          
 ```
 to give value to the parameter
  
 ```
 sudo rmmod arguments                                
 sudo dmesg -C
 sudo insmod ./arguments.ko loop_count=5 name="Nemo"
 dmesg                          
 ```
  
  If we use `modinfo` it will report the usage of parametes in the modules.
                                 
  Also if check `/sys/module/arguments/parameters/` the parameters are visible, and you can `cat` their values. So in case it is needed to check the values of already loaded modules, it is possible to check them in this way.
  
  In the case if incorrect values are passed to the module parameters, an error reporting invalid parameters will appear.
                                
  For module parameters of builtin modules, those are passed throught the command line: <br>
  syntax: `<module_name>.<parameter_name>=value` <br>
  
  To pass parameter to modules loaded with `modprobe` this is used with th efile `/etc/modprobe.conf', modprove reads that file for the parameters.
  
  To pass multiple words as a parameter, has to be done like: 
  ```
  sudo insmod ./module_name.ko name='"Hello World!"' 
  ```
  
  This happens because if we only use simple quotes `''` or double quotes `""` the shell removes hos quotes an passes it to `insmod`, so about add single quotes over a string. 
  
  In case it is needed to pass an array as a parameter, then it is needed to use the macro `module_param_array()`, instead of the `module_param()` function
  
  ```
  # define module_param(name, type, perm)
  
  · module_param_array: a parameter which is an array 
  · @name: the anme of the arrray variable
  · @type: tye type 
  · @nump: optional pointer filled wiin with the nuber written
  · @perm: visibility in sysfs
  
  #define module_param_array(name, type, nump, perm)
  ```
  
  and to pass the array parameter: <br>
  ```
  sudo insmod ./module_name.ko param_array=1,2,3
  ```  
  
  and example: 
  
  ```
  #include <linux/kernel.h>
  #include <linux/module.h>
  #include <linux/moduleparam.h>
  
  MODULE_LICENSE("GPL");
  
  int param_array[4];
  static int argc_count = 0;
  module_param_array(param_array, int, &argc_count, S_IWUSR | S_IRUSR);
  
  static int __init test_arguments_init(void)
  {
          int i = 0;
          printk("%s\n", __func__);
          printk("%Argc count:%d\n", argc_count);
          printk("Array elements:\n");
          for (i=0; i < sizeof(param_array)/sizeof(param_array[i]); ++i) {
              printk("%d:\t%d\n", i, param_array[i]);                                                         
          }
          return 0;
  }
                                                                   
  static void __exit test_arguments_exit(void)
  {
          printk("%s\n", __func__);                      
  }
  
  module_init(test_arguments_init);
  module_exit(test_arguments_exit);
  MODULE_AUTHOR("Nemo");
  MODULE_DESCRIPTION("Arguments Passing Array Example");
  ```
 
### Symbol and symbol table

A symbol is name given to a space in memory, like: data (variables) or instructions (functions). 
                                                                   
A symbol table is a data sttrcuture created by the compiler containing all the symbols used in the program.
                                                                   
Every kerenl image build has a symbol table with it. The Linux kernel symbol table contains names and addresses of all the 
kernel symbols. When the kernel is installed it will be pressen in `/boot/System.map-<linux-version>
 
TODO: GET SCREENSHOT EXMAPLE!!
  
When a new function is defined in a moudle, the default behavior of this function is local, only the
module which the function is defined can access it, it cannot be accessed by other modules
  
  To export this module it is needed to use EXPORT_SYMBOL or EXPORT_SYMBOL_GPL
  
- `EXPORT_SYMBOL' : the exported symbol can be used by any kernel module
- `EXPORT_SYMBOL_GPL` : the exported symbol can be used by only GPL licensed code.
  
  
The difference between System.map and /proc/cakksyms
  
 - `/proc/kallsysms`: contains the symbols of dynamically loaded modules as well as builtin modules
 - `system.map` : contains symbols of only builtin modules.
  
Example of exporting a function:
  
```
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/jiffies.h>
 
MODULE_LICENSE("GPL");
 
void print_jiffies(void)
 {
     printk(KERNEL_INFO "%s: Jiffies:%ld\n", __func__, jiffies);
 }
  
static int test_export_init(void)
{
     printk(KERN_INFO "%s: In init\n", __func__);
     return 0;
}

static void test_export_exit(void)
{
     printk(KERN_INFO "%s: In exit\n", __func__);  
}
  
EXPORT_SYMBOL_GPL(print_jiffies);
  
module_init(test_export_init);
module_exit(tests_export_exit);
```

To check if the symbol has ben exported, load it: `sudo insmod ./symbold_export.ko'  and check: `cat /proc/kallsyms | grep print_jiffies`
 
  
 ### Export a variable or a function
  
Use: `EXPORT_SYMBOL(<variable_name>)`.
  
To check if it was exported, use: `cat /proc/kallsyms | grep <exported_symbol>`
  
  
 ### Module stacking
  
  Module stacking is when new modules use the symobls exported by previous loaded modules.
  
  Example: 
   1. A moudle which exports  function that performs an addition
   2. A second module which uses the exported function 
  
 ```
#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros __init __exit */  
  
MODULE_LICENSE("GPL")

int myadd(int a, int b) 
{
    pr_inf("%s: Adding %d with %d\t Result:%d\n", __func__, a, b, a+b);
    return a+b;
}
  
EXPORT_SYMBOL(myadd);

static int module1_init(void)
{
    pr_info("%s: In init\n", __func__);
    return 0;
}
  
static void module1_exit(void)
{
    pr_info("%s: In exit\n", __func__);  
}
  
module_init(module1_init);
module_exit(module1_exit);
```

  
  
```
#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros __init __exit */  
  
MODULE_LICENSE("GPL")
  
extern int myadd(int a, int b);
  
static int module2_init(void)
{
    pr_info("%s: In init\n", __func__);
    pr_info("%s: Add:%d\n", __func__, myadd(3, 5));
    return 0;
}
  
static void module2_exit(void)
{
    pr_info("%s: In exit\n", __func__); 
}
  
module_init(module2_init);
module_exit(module2_exit);
```
  
the makefile:
```
obj-m := module2.o
obj-m += module1.o
  
all: 
     make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
     make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```
 
  
If the module 2 is loaded fist, it will report an error: Unknown symbol in module, because module2 depends on module1.
  
First the module1 is loaded: `sudo insmod ./module1.ko´ <br>
Next, verify if the symbols was indeed exported with: `sudo cat /proc/kallsyms | grep myadd' 
  
Then load the second module: `sudo insmod ./module2.ko`
  
For using `modprobe`:
  
  ```
  sudo ln -s /<full_path>/module1.ko /lib/modules/$(uname -r)/kernel/drivers/misc  # create soft links
  sudo ln -S /<full_path>/module2.ko /lib/modules/$(uname -r)/kernel/drivers/misc
  
  sudo depmod -a
  
  sudo modprobe module2
  
  # check lsmod, module1 shoud be automatically loaded.
  ```
  
### Version magic
  
version magic: `vermagic` is a string present in the Linux kernel and added into the .modinfo section of the Linux kernel modules.
  
It is used to verify wheter the kernel module was compiled for the particular kernel version or not.
  
When loading a module, the strings in the vermagic value are checked if they match. In case the strings don't match, an error will be reported and the module will not be loaded. 
  
 `VERMAGIC_STRING` is generated by the kernel configuration.
  
  ``` 
  #define VERMAGIC_STRING  \
     UTS_RELEASE " " \
     MODULE_VERMAGIC_SMP MODULE_VERMAGIC_PREEMT \
     MODULE_VERMAGIC_MODULE_UNLOAD MODULE_VERMAGIC_MODVERSIONS \
     MODULE_ARCH_VERMAGIC \
     MODULE_RANDSTRUCT_PLUGIN
  ```
  
 ```
#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/vermagic.h>     /* Needed for vermagic */
  
MODULE_LICENSE("GPL")

static int vermagic_init(void)
{
    pr_info("VERMAGIC_STRING = " VERMAGIC_STRING "\n");
    return 0;
}
  
static void vermagic_exit(void){}
  
module_init(vermagic_init);
module_exit(vermagic_exit);  
```
 
 To check the vermagic of a module: ' sudo modinfo ./<module_name>.ko`
  
 To change the value of vermagic, use: `MOUDLE_INFO()`.
  
 ```
#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/vermagic.h>
  
MODULE_LICENSE("GPL")

static int vermagic_init(void)
{
    pr_info("VERMAGIC_STRING = " VERMAGIC_STRING "\n");
    return 0;
}
  
static void vermagic_exit(void){}
  
module_init(vermagic_init);
module_exit(vermagic_exit);  
MODULE_INFO(vermagic, "123454321");
```
  
### Module metadata
  
To find the version of a given .ko file, what kernel was it build for? using the `modinfo` command, that will report the vermagic number, and with that the kernel version is known.
  
Metadata can be added to a module, with the macros:
  
  - MODULE_DESCRITION: short description of the module.
  - MODULE_AUTHOR: declares the author.
  - MODULE_VERSION: sets de version of the module.
  
It is possible to add custom iformation like: `MODULE_INFORMATION(<your_tag_name>, <your_tag_value>)`
  
### objdum of a ko file
  
 A .ko file is an ELF object. And ELF object file consist on various named sections, for example the .text 
section contains the executable code that the loaded loads. 
  
To see all the sections:
```
objdump --section-heades ./<module_name>.ko  
```
 
To see the contents of the .modinfo section

```
objdump --section-heades --section=.modinfo --full-contents ./<module_name>.ko
```
  
  
  
  

  
  

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
Reference: https://lwn.net/Kernel/LDD3/
 
