# NOTES ABOUT PROGRAMMING


Unix-like systems use the ELF (executable and linking format) for these programs. 

An ELF file is a relocatable object, with the following sections.

- ELF header ->starts with magic number string: /177ELF
- .text      -> this is the machine code - This is the CODE of the program!! plus literals and static constants
- .rodata    -> read only data, like char strings, or const variables.
- .data      -> global variables
- .bss    -> (block storage start) uninitialized global variables and zero initialized variables.
- .symtab -> symbol table for functions and global variables. local variables are in the stack, not here
- .rel.text -> list of location in the .text section, that will need to be modified by linker, when combining object files. 
- .rel.data ->relocation info of global variables that are referenced but not defined in the current module.
- .debug -> debugging symbols table.
- .line -> mapping between line numbers, and the source code program, and machine code instruction in the .text section.
- .strab -> string table for the sections .symtab and .debug.

These different parts are assembly definitions, so different architectures may have different parts.

A list of Linux tools that can be used to explore object/executable files.

 - ar: creates static libraries.
 - objdump: this is the most important binary tool; it can be used to display all the information in an object binary file.
 - readelf: this provides info about elf files. 
 - strings: list all the printable strings in a binary file.
 - nm: lists the symbols defined in the symbol table of an object file.
 - ldd: lists the shared libraries on which the object binary is dependent.
 - strip: deletes the symbol table information.


When a program is launched for execution, its memory layout usually corresponds with:

```
+----------------+
|                |
|      STACK     |
+--------+-------+
|        |       |
|        v       |
|                |
|                |
|        ^       |
|        |       |
+--------+-------+
|      HEAP      |
+----------------+
| uninitialized  |
|      data      |
|      .bss      |
+----------------+
|      DATA      |
|initialized data|
+----------------+
|                |
|      TEXT      |
+----------------+
```


Variables, the heap, and the stack go in RAM. Constants and machine code go in ROM. Basically, items that can change over time go in RAM and items that do not change go in ROM.

local variables are stored in the stack. But dynamic allocated memory goes into the heap. Allocating memory in the heap is much slower that in the stack, because it is needed to reach the memory manager in the system. But it also can serve much bigger storage than the stack. 


references:

https://www.linuxjournal.com/article/6463

https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html

https://en.wikipedia.org/wiki/Data_segment

http://www.c-faq.com/

https://medium.com/@tyastropheus/the-magic-black-box-of-gcc-explained-54f991f4f6a2

examples for other architectures other than x86:
http://downloads.ti.com/docs/esd/SLAU131O/Content/SLAU131O_HTML/program-loading-and-running.html

http://www.ti.com/lit/ug/slau131u/slau131u.pdf


elf standard:

http://www.sco.com/developers/devspecs/gabi41.pdf


readelf command:

https://linux.die.net/man/1/readelf

https://manybutfinite.com/post/anatomy-of-a-program-in-memory/


objdump

https://linux.die.net/man/1/objdump

Development of the C languaje: https://www.bell-labs.com/usr/dmr/www/chist.html

## CREATION AND ANALYSIS OF A PROGRAM

you can write a simple program. For that we can use GCC. 

GCC is the standard linux compiler. Its name stands for GNU Compiler Collection, as it contains compilers for several languages. Such as C (gcc), C++ (g++), Objective-C, Objective-C++, Java (gcj), Fortran (gfortran), Ada (gnat), Go (gccgo), OpenMP and more.

GCC is part of the GNU toolchain, that includes:

 - GNU Compiler Collection (GCC): a compiler suite that supports many languages, such as C/C++ and Objective-C/C++.
 - GNU Make: an automation tool for compiling and building applications.
 - GNU Binutils: a suite of binary utility tools, including linker and assembler.
 - GNU Debugger (GDB).
 - GNU Autotools: A build system including Autoconf, Autoheader, Automake and Libtool.
 - GNU Bison: a parser generator (similar to lex and yacc).
 
GCC is portable and run in many operating platforms. GCC (and GNU Toolchain) is currently available on all Unixes. They are also ported to Windows (by Cygwin, MinGW and MinGW-W64). GCC is also a cross-compiler, for producing executables on different platforms.

the possible program could be: 

```
# include <stdio.h>
int main(){
   printf(“Hello World!”);
   return 0;
}
```

save it as: helloworld.c

and compile it:  '''gcc hellowold.c'''

- gcc is the C compiler
- g++ is the C++ compiler

a new file will appear: a.out

```
$ chmod a+x a.out
$ ./a.out
```

you can try to execute it with: '''./a.out''' 

and the response will be: '''Hello World!''' 



you can run the preprocesor, and store the result in a file: a.i

'''gcc -E prog.c '''

if you read a.i ( tail -25 a.i)  you can see the created file, with all the include definitions. 


the sequential steps are: 

```
                                  +
                                  |
                                  |   Source files (.c .cpp .h)
                                  |
                                  |
                       +----------v-----------+
                       |                      |
                       |     PREPROCESOR      |
                       |                      |
                       +----------+-----------+
                                  |
                                  |   headers inclusion and micro expansion
                                  |
                       +----------v-----------+
                       |                      |
                       |       COMPILER       |    (gcc, icc, clang, mingw)
                       |                      |
                       +----------+-----------+
                                  |
                                  |   assembly code (.s)
                                  |
                       +----------v-----------+
                       |                      |
                       |      ASSEMBLER       |    (as)
                       |                      |
                       +----------+-----------+
                                  |
                                  |  machine code (.o, .obj)
                                  |
   static              +----------v-----------+
libraries (.a, .lib)   |                      |
             +--------->        LINKER        |    (ld)
                       |                      |
                       +----------+-----------+
                                  |
                                  |   machine code (.exe , ELF)
                                  v
```




Preprocess only; do not compile, assemble or link
'''gcc -E prog.c'''

Compile only, do not assemble or link.
'''gcc -S prog.c '''

Compile and assemble, but do not link
'''gcc -c prog.c '''

Place the output into a file
'''gcc -o <file> prog.c''' 


GCC compiles a C/C++ program into executable in 4 steps as shown in the above diagram. For example, a "gcc -o hello.exe hello.c" is carried out as follows:

Pre-processing: via the GNU C Preprocessor (cpp.exe), which includes the headers (#include) and expands the macros (#define).
```
> cpp hello.c > hello.i
```

The resultant intermediate file "hello.i" contains the expanded source code.

Compilation: The compiler compiles the pre-processed source code into assembly code for a specific processor.
```
> gcc -S hello.i
```
The -S option specifies to produce assembly code, instead of object code. The resultant assembly file is "hello.s".

Assembly: The assembler (as.exe) converts the assembly code into machine code in the object file "hello.o".
```
> as -o hello.o hello.s
```

Linker: Finally, the linker (ld.exe) links the object code with the library code to produce an executable file "hello.exe".
```
> ld -o hello.exe hello.o ...libraries...
```


some common compiler options are:

 - o: specifies the output executable filename. Compile, assemble, and link to the output file.
 - Wall: prints "all" Warning messages.
 - Werror: consider all warnings as errors. 
 - I: include this directory to look for header files.
 - L: include this directory to look for libraries files
 - l: link with a library.
 - g: generates additional symbolic debugging information for use with gdb debugger.
 - std=STANDARD : define which language standard to use.
 - v: verbose mode. displays more information.


to check the current installed version of gcc, use the command:

```
gcc -version
```

for more info

```
man gcc
```

to check how many tool chains are installed, use the command:

```
ls -la /usr/bin/*gcc

```

it is possible to see the ARM cross compiler:
```
arm-none-eabi-gcc
```
Also depending of the architecture of the processor, different compiling flags are available:

For example, for the ARM architecture:

- mcpu   defines target ARM processor and architecture
- march   defines target ARM architecture
- mtune   defines target ARM processor
- mthumb   generates thumb code
- marm   generates code in ARM state
- mlittle-endinan   generates code in little endian mode
- mbig-endian   generates code for big endian mode


More on:

GCC Manual "Using the GNU Compiler Collection (GCC)" @ http://gcc.gnu.org/onlinedocs.

GNU 'make' manual @ http://www.gnu.org/software/make/manual/make.html.

Robert Mecklenburg, "Managing Projects with GNU Make", 3rd Edition, 2004.


## LIBRARIES:

Libraries are precompiled code that can be added to a program in the linking process.

There is two kinds of libraries: static libraries and shared (or dynamic) libraries:

Static libraries have the extension '.a' (from __archive__ in linux systems) or '.lib' (in windows). When a static library is linked the machine code of the library functions is added to the program. The static libraries will be installed with the program as a part of the executable, they are linked into the executable.  They are created using the “archiver” gnu tool, the command 'ar'. 

Shared (or dynamic) libraries: have the extension .so (wich stands for __shared object__ in linux) or .dll (in windows- dynamic linked libraries) in this the operating system loads the machine code of the libraries functions. So the program is smaller. The shared or dynamic libraries are linked at runtime with the executable. So they must be pre installed in the target. They are created with the “shared” flag. Their advantage is that multiple programs can use the same library. To create a shard library, it is needed to compile in gcc, with the -fPIC option, PIC, stands for Possition Independent Code. And link with the -shared option, this will combine object files into a shared library.

in linux:
Files with the “.a” extension are static libraries.
Files with the “.so” extension are dynamically linked shared object libraries. 

GCC uses the following environment variables:

PATH: For searching the executables and run-time shared libraries 

CPATH: For searching the include-paths for headers. It is searched after paths specified in -I<dir> options.

C_INCLUDE_PATH and CPLUS_INCLUDE_PATH can be used to specify C and C++ headers if the particular language was indicated in pre-processing.

LIBRARY_PATH: For searching library-paths for link libraries. It is searched after paths specified in -L<dir> options.


the program: "make" is a program for compiling and building programs or libraries from source code. It is part of the build-essential package.

references: 

https://www.gnu.org/software/make/

https://www.gnu.org/software/make/manual/html_node/index.html

http://www.cmake.org/


### how to decide between static and dynamic libraries

With static libraries, programs will be bigger and harder to upgrade. But they will be easier to deploy.

With dynamic libraries (shared libraries), programs will be smaller and easier to upgrade, but harder to deploy.

A major advantage of shared libraries, is that they save space in the system where they are installed.


## BUILD SYSTEM: MAKE

Only the compilation of small projects is feasible directly invoking the compiler. For the rest of the projects, tools to compile it are used. This is known as build automation.

Make is an executable generating application provided by GNU, it is separate from the GCC toolchain


### MAKE TARGETS AND RULES: 

The main syntaxis rule is:

[target file]: [resources]
  [tab - a real tab character, not spaces!] system commands
	
	
- gcc is the C compiler
- g++ is the C++ compiler
	
	
for example:


```
myprogram: main.o aa.o bb.o 
   g++ -o myprogram main.o aa.o bb.o 
   
main.o : main.cpp header1.handling
   g++ -c main.cpp
   
aa.o : aa.ccpp header1.handling
   g++ -c main.cpp
   
bb.o : bb.cpp header2.h
   g++ -c bb.cpp

clean: 
   rm myprogram \
   main.o aa.o bb.o
```

The "clean" command is actually to remove all the object files, and the backslash is for using just one terminal call.
To use it we call it "make clean".

The program 'make' starts for the first rule, and calls also all the other rules needed. 
   
the sintaxis can be developed further with the use of variables:


```
OBJECTS = main.o aa.o bb.o 

myprogram: $(OBJECTS)
	g++ -o myprogram $(OBJECTS)
   
aa.o : aa.ccpp header1.handling
   g++ -c main.cpp
   
bb.o : bb.cpp header2.h
   g++ -c bb.cpp

clean: 
   rm myprogram \
   main.o aa.o bb.o
```

The "make" program has several implicit rules, so for example, for a given .o file, it is not needed to specify its .cpp file.

so the the make file can be rewritten as:

```
OBJECTS = main.o aa.o bb.o cc.o
myprogram : $(OBJECTS)
	g++ -o myprogram $(OBJECTS)
main.o : header1.h
aa.o :  header1.h header2.h
bb.o : header2.h
clean : rm myprogram \
	$(OBJECTS)
```

Another possibility is to avoid mis-interpret the "clean" with a file named "clean" we use the .PHONY tag. 
We explicitly declare a target as phony, using special target command .PHONY.

So the .PHONY tag points to a target that it is not a file, so then, we cannot confuse the target with a file with that same name. 


```
OBJECTS = main.o aa.o bb.o cc.o
myprogram : $(OBJECTS)
	g++ -o myprogram $(OBJECTS)
main.o : header1.h
aa.o :  header1.h header2.h
bb.o : header2.h
.PHONY : clean
clean : -rm myprogram $(OBJECTS)
```

more variables can be used, like CFLAGS that stand for compilation flags...

 - CFLAGS: flags for the C compiler
 - CPPFLAGS: flags for the C Preprocessor.
 - CXX: flags for C++ compiler (g++ in gnu)
 - CXXFLAGS: extra flags for the C++ compiler. 

```
CC = g++
SOURCES =  main.cpp aa.cpp bb.cpp cc.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = myprogram
CPPFLAGS=-O3 -funroll-loops -c -Wall -Werror
LDFLAGS=-O2 -lm

#Uncomment the following to enable debugging
#CPPFLAGS+=-g -DDEBUG

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@  

.cpp.o: *.h
	$(CC) $(CFLAGS) $< -o $@

clean :
	-rm -f $(OBJECTS) $(EXECUTABLE) ${OBJECTS} *.d

.PHONY: all clean
```

so to compile all we command: "make all"

and to clean, the command is "make clean"

We did use variables for example:  we used $@ for the object file name and $< for the source file name.

Substitution reference: 

the line: OBJECTS=$(SOURCES:.cc=.o) is known as a substitution reference.
this substitutes the value of a variable with alterations that you specify.
 It has the form $(var:x=y) and its meaning is to take the value of the variable var, 
 replace every x at the end of a word with y in that value, and substitute the
 resulting string. So, the line means OBJECTS are all the sources, with .cc replaced by .o.


### AUTOMATIC VARIABLES

In the previous example we can see the use of automatic variables: 

These variables have values computed anew for each rule. 


 - $@   - the name of the target or rule
 - $%   - The target member name, when the target is an archive member
 - $<   - The name of the first prerequisite
 - $?   - The names of all the prerequisites that are newer than the target
 - $^   - The names of all the prerequisites with spaces between them
 - $+   - Similar to '$^', but prerequisites listed more than once are duplicated in the order they were listed in the makefile
 - $*   - The stem with which an implicit rule matches. For example, the target aa.o matches the pattern '%.o', then 'aa' is the stem.


a more advanced script would be:

```
# compiler
CC = g++
# install dir
INSTDIR = /usr/local/bin
# include dir
INCLUDE = .
# for debug
CFLAGS = -g -c -Wall
# for release
# CFLAGS = -O -c -Wall

SOURCES =  main.cpp aa.cpp bb.cpp cc.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = myprogram

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
                $(CC) $(OBJECTS) -o $@

.cpp.o: *.h
        $(CC) $(CFLAGS) $< -o $@

clean :
        -rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean

install: $(EXECUTABLE)
        @ if [ -d $(INSTDIR) ]; \
        then \
           cp $(EXECUTABLE) $(INSTDIR) && \
           chmod a+x $(INSTDIR)/$(EXECUTABLE) && \
           chmod og-w $(INSTDIR)/$(EXECUTABLE) && \
           echo "$(EXECUTABLE) is installed in $(INSTDIR)"; \
        else \
           echo "Warning! $(INSTDIR) does not exist"; \
        fi 
```

for example a make file that is can be used to cross compile:

```
------------------------------------------------
#  the platform has to be defined, like:
#  make build PLATFORM=MSP432
#  make build PLATFORM=HOST
#------------------------------------------------------------------------------
#include sources.mk

# Add your Source files to this variable
SOURCES = \
main.c \
memory.c \
interrupts_msp432p401r_gcc.c \
startup_msp432p401r_gcc.c \
system_msp432p401r.c \

# Add your include paths to this variable
INCLUDES = \
-I ./../include/CMSIS \
-I ./../include/common \
-I ./../include/msp432 \

# General flags for both platforms
GEN_FLAGS = -Wall \
            -Werror \
            -g \
            -O0 \
            -std=c99

TARGET = program

ifeq ($(PLATFORM),HOST)
    #HOST
	CC = gcc      #Compiler
        LD = ld       #Loader
        LDFLAGS = -Wl,-Map=$(TARGET).map 	#Loader flags
        CPPFLAGS = -DHOST -MD                   #C preprocessor flags
        CFLAGS = $(GEN_FLAGS) -I ./../include/common   #C compiler flags
        SOURCES = main.c  memory.c 
	OBJDUMP = objdump
        SIZE = size
else
  ifeq ($(PLATFORM),MSP432)
	CC = arm-none-eabi-gcc
        LD = arm-none-eabi-l
	OBJDUMP = arm-none-eabi-objdu
        SIZE = arm-none-eabi-size
        LINKER_FILE = -T msp432p401r.lds
        LINKER_FILE_PATH = -L ../
        LDFLAGS = -Wl,-Map=$(TARGET).map $(LINKER_FILE_PATH) $(LINKER_FILE)
        CPU = cortex-m4
        ARCH = armv7e-m
        SPECS = nosys.specs
        CPPFLAGS = -DMSP432 -MD
        CFLAGS = -mcpu=$(CPU) -mthumb -march=$(ARCH)
        CFLAGS += --specs=$(SPECS) -mfloat-abi=hard -mfpu=fpv4-sp-d16
        CFLAGS += $(GEN_FLAGS) $(INCLUDES)

  else
        # by default
	CC = gcc
        LD = ld
        SIZE = size
	OBJDUMP = objdump
        SOURCES = main.c  memory.c 
        CFLAGS = -DHOST $(GEN_FLAGS) -I ./../include/common 
  endif
endif

# Pattern Matching - Associate source files with:
OBJS = $(SOURCES:.c=.o)    # Object files
DEPS = $(SOURCES:.c=.d)    # Dependency files
ASMS = $(SOURCES:.c=.asm)  # Assembly files
PREP = $(SOURCES:.c=.i)    # Preprocessed files


%.o : %.c
	$(CC) -c $< $(CPPFLAGS) $(CFLAGS) -o $@

%.i : %.c
	$(CC) -E $< $(CPPFLAGS) $(CFLAGS) -o $@

%.d: %.c
	$(CC) -E $< $(CPPFLAGS) $(CFLAGS) -o $@

%.asm : %.c
	$(CC) -S $< $(CPPFLAGS) $(CFLAGS) -o $@ -E $< -o $@ $(OBJDUMP) -S $@


.PHONY: build
build: all

.PHONY: all
all: $(TARGET).out

.PHONY: compile-all
compile-all: $(TARGET).out

$(TARGET).out: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@
	$(SIZE) $@
	echo ">> Build succeeded!!!"

.PHONY: clean
clean:
	rm -f $(OBJS) $(DEPS) $(ASMS) $(PREP) $(TARGET).out $(TARGET).map *.o *.i *.d *.asm

```

## PREPROCESSOR

The preprocessor allows us to create macros for code readability and also define compilation switches.

its directives are preceded by a # simbol

#define, #undef,
#ifndef, #ifdef, #elif,#else, #endif
#include,
#warning, #error
#pragma  --this one is not standard, so it will not be very portable.

Also the compile time switches: -D<macro_name>


MEMORY

In a program, typically

 R0M -has the program code
 RAM - has the program data. 



