# Notes on Risc-V

- reference: The center of the RISC-V universe of information is the RISC-V website at https://riscv.org/
- events: https://riscv.org/events-all/
- specifications: https://riscv.org/technical/specifications/

### What is RISC and RISC-v 

RISC: Reduced Instruction Set Computer: https://en.wikipedia.org/wiki/Reduced_instruction_set_computer

RISC processors - short for Reduced Instruction Set Computer - were first designed in the 1980s as an evolution of earlier designs.

In practice, the term RISC-V can refer to several different things depending on context:

- The Instruction Set Architecture (ISA)
- The RISC-V community of users and developers who develop and use the ISA
- The RISC-V International Association that manages the ISA intellectual property and guides the community in further development and curation
- The hardware and IP products that are built on the ISA

As you can see, each of these things revolves around the ISA as the central component, but all of these things are RISC-V. In general, we use RISC-V in conversation to refer to the technology components - the ISA and its various specifications - while the other contexts are the RISC-V community, RISC-V International, and RISC-V hardware, respectively.


### What is ISA, and RISC-V ISA? 

ISA: Instruction Set Architecture: https://en.wikipedia.org/wiki/Instruction_set_architecture

In computer science, an instruction set architecture (ISA) is an abstract model of a computer. A device that executes instructions described by that ISA, such as a central processing unit (CPU), is called an implementation.

So what exactly is the RISC-V ISA? ISA refers to the Instruction Set Architecture, an abstract model of a computer - in this case, a Reduced Instruction Set Computer (or RISC). The specification for this set of instructions is the 5th generation of RISC processors, which have been in development since the 1980s. Thus we call it RISC-V, with the 5 spelled out as a Roman numeral (partly as a pun referring to “variations” and “vectors”, implying that the creators intended flexibility as an intentional part of the design).

### How RISC-V started? 

RISC-V’s story begins at UC Berkeley Parallel Computing Lab. To set the stage, we first discuss the importance of open source and open standards, as these directly apply to the development process and open licensing of the RISC-V ISA, plus a small history of RISC processing as well as other open (or semi-open) ISAs.

### History of RISC and open ISAs

Reduced Instruction Set Computers - RISC - have a long and varied history that begins at the University of California at Berkeley (UCB). In many ways, the history of RISC is bound up with the history of MIPS processors, which began at nearly the same time at Stanford in the 1980s. Both processor architectures have had great commercial success in different ways, although RISC architectures are arguably more likely to be recognized through some very popular designs, including Sun Microsystems’ SPARC line, DEC’s Alpha line, Intel’s i860 and i960 processors, and the ubiquitous ARM processors that inhabit billions of devices today from many silicon manufacturers. RISC-V is the latest iteration of this instruction set architecture.

### RISC-V origins: UC Berkeley Architecture Research

Prof. Krste Asanović and graduate students Yunsup Lee and Andrew Waterman started the RISC-V instruction set in May 2010 as part of the Parallel Computing Laboratory (Par Lab) at UC Berkeley, of which Prof. David Patterson was Director. The Par Lab was a five-year project to advance parallel computing funded by Intel and Microsoft for $10M over 5 years, from 2008 to 2013 1. It also received funding from several other companies and the State of California. The Chisel hardware construction language that was used to design many RISC-V processors was also developed in the Par Lab. You can learn more about the Par Lab in "The Berkeley Par Lab: Progress in the Parallel Computing Landscape" book by Patterson, Gannon and Wrinn.

While the project overall did not have federal funding, Yunsup Lee and Andrew Waterman received some funding from the DARPA POEM photonics project, which funded some of the processor implementation development (but not the RISC-V ISA). The funds were 6.1 basic research via MIT as a prime contract with the International Computer Science Institute as the subcontract.

All the projects in the Par Lab were open source using the Berkeley Software Distribution (BSD) license, including RISC-V and Chisel. The following report of the Par Lab is the first publication that describes the RISC-V instruction set: Waterman, A., Lee, Y., Patterson, D. A., and Asanović, K. (2011). The RISC-V Instruction Set Manual, Volume I: Base User-Level ISA (EECS-2011-62).

For RISC-V, the UC Berkeley ParLab industrial sponsors provided the initial funding that was used to develop RISC-V. They didn’t explicitly ask for RISC-V itself - their interest was in parallel processing systems.

Beyond that first publication, major RISC-V milestones include the first tapeout of a RISC-V chip in 28nm FDSOI (donated by ST Microelectronics based in Switzerland) in 2011, publication of a paper on the benefits of open instruction sets in 2014, the first RISC-V Workshop held in January 2015, and the RISC-V Foundation launch later that year with 36 Founding Members.

The ISA specification itself, i.e., the encoding of the instruction set, was released with a permissive license (similar to the language of the BSD license) when the ISA tech reports were published, though the actual tech report text (an expression of the specification) was later put under a Creative Commons license to allow it to be improved by external contributors, including the RISC-V Foundation.

No patents were filed related to RISC-V in any of these projects, as the RISC-V ISA itself does not represent any new technology. The RISC-V ISA is based on computer architecture ideas that date back at least 40 years. RISC processor implementations—including some based on other open ISA standards—are widely available from various vendors worldwide.

The worldwide interest in RISC-V is not because it is a great new chip technology. The interest is because it is a common free and open standard to which software can be ported, and which allows anyone to freely develop their own hardware to run the software. RISC-V International does not manage or make available any open-source RISC-V implementations, only the standard specifications. RISC-V software is managed by the respective open source software projects.

 - reference: RISC-V geneology: https://riscv.org/technical/specifications/risc-v-genealogy/

### Why the name RISC-V? 

How did RISC-V get its name? The RISC portion is fairly obvious, but why is it number 5, and why is this represented with a Roman numeral? The answer lies in a footnote in the introduction of the ISA spec itself:

The name RISC-V was chosen to represent the fifth major RISC ISA design from UC Berkeley (RISC-I [15], RISC-II [8], SOAR [21], and SPUR [11] were the first four). We also pun on the use of the Roman numeral “V” to signify “variations” and “vectors”, as support for a range of architecture research, including various data-parallel accelerators, is an explicit goal of the ISA design.

### What is RISC-v international?

The RISC-V Foundation was founded in 2015 to build an open, collaborative community of software and hardware innovators based on the RISC-V ISA. The Foundation, a non-profit corporation controlled by its members, directed the development to drive the initial adoption of the RISC-V ISA.

- reference: https://riscv.org/

RISC-V International, a Swiss non-profit organization, was formed in order to organize the activity around development of the ISA as well as other artifacts including software, non-ISA specifications, testing and compliance frameworks, and much more. RISC-V is organized by and for its members, which include over 200 large and small organizations as well as many hundreds of individual members who participate on their own, apart from companies or universities. The board of directors includes voting representatives from every membership level, so RISC-V is truly an egalitarian, community-based organization.

## RISC technical overview

## Defining an Instruction Set Architecture ISA

An instruction set architecture (ISA) is an abstract model of a computer. It is also referred to as architecture or computer architecture. A realization of an ISA, such as a central processing unit (CPU), is called an implementation. Some ISAs you may have heard of include x86, ARM, MIPS, PowerPC, or SPARC. All of these ISAs require a license to implement them. On the other hand, the RISC-V ISA is provided under open source licenses that do not require fees to use.

## How RISC-V is different?

The most notable difference between RISC-V and other ISAs is that RISC-V is developed by a member organization that is completely free to join and licenses its ISA with permissive open source licenses. This means that anyone can contribute to the specifications, and no one company or group of companies can drive the direction of the standards.

RISC-V International is governed by its Board of Directors. The Board is composed of members elected to represent all classes of membership to ensure we offer a strategic voice at all levels. In addition, the Technical Steering Committee (TSC) provides leadership to our technical initiatives in setting long term strategy, forming tactical committees and work groups, and approving technical deliverables for ratification or release.

## Collaborative development model

A RISC-V Specification starts its life as a Task Group approved by the Technical Steering Committee (TSC). Once a Task Group has an approved charter, they begin work publicly on GitHub by writing their documents in AsciiDoc format. These repositories on GitHub can only receive pull requests from RISC-V International members, however the work is done publicly and transparently. For groups who choose to take minutes, those minutes from the Task Group meetings are published publicly as well. The public is free to submit issues to the GitHub repository in order to give early feedback on any specification. Non-ISA specifications and standards (e.g. processor trace, architectural tests, software overlay) are developed in a similar fashion.

## Specifications organization

- reference: specifications: https://riscv.org/technical/specifications/

The RISC-V ISA is broken up into two parts:

- Volume 1, Unprivileged Specification: https://drive.google.com/file/d/1s0lZxUZaa7eV_O0_WsZzaurFLLww7ou5/view
- Volume 2, Privileged Specification: https://drive.google.com/file/d/1EMip5dZlnypTk7pt4WWUKmtjUKTOkBqh/view
  
To understand why the specification is broken up into two different parts, we must first understand a bit about computer architecture and security. Historically, processors used hierarchical protection domains, often called protection rings, to protect data and code from malicious actors.

![protection rigs](https://upload.wikimedia.org/wikipedia/commons/2/2f/Priv_rings.svg)

- reference: https://commons.wikimedia.org/w/index.php?curid=8950144

The most privileged code runs in “Ring 0” and has access to the entire system. The processor will decide which privileges to grant executing code based on the privilege level. As an example, accessing memory by physical address may be restricted to “Ring 0” such that other rings must reference the virtual address space. Typically the processor can run in only one of the privilege modes at a time and there are special instructions to move between modes. All of these details can change from system to system, however they must follow the rules set out in the specification documents of a given architecture.

RISC-V currently has three privilege levels: 
- User Mode (U-mode)
- Supervisor Mode (S-mode)
- Machine Mode (M-mode)

One can think of these as “Ring 2”, “Ring 1”, and “Ring 0” respectively. Other modes like a hypervisor mode (H-mode) will likely be added in the near future. Much like in the figure above, U-mode is for user processes, S-mode is for kernel and/or device drivers, and M-mode is used for bootloader and/or firmware. Each privilege level has access to specific Control and Status Registers (CSRs), and higher privilege levels can access the CSRs of those less privileged levels.

## Unprivileged Specification

- Volume 1, Unprivileged Specification: https://drive.google.com/file/d/1s0lZxUZaa7eV_O0_WsZzaurFLLww7ou5/view

the unprivileged specification details items that are not related to machine mode (M-mode) or to Supervisor Mode (S-mode). The unprivileged specification includes the base ISA as well as extensions to that base like integer (I), float (F), double (D), compressed instructions (C), and many more.

The base instruction sets describe the instruction format, basic integer instructions, load and store instructions, and other fundamental details of the ISA. We break these up into several bases:

 - RV32I - Integer 32 bit
 - RV32E - Reduced RV32I for embedded purposes
 - RV64I - Integer 64 bit
 - RV128I - Integer 128 bit

All these “Base ISA’s” either reduce or extend off the RV32I base instruction set. As an example, RV64I widens the integer registers and the supported user address space to 64 bits. This means that the LOAD and STORE instructions work a bit differently than in RV32I and the unprivileged specification contains the chapter explaining these differences.

## Base ISA Extensions

The unprivileged specification also contains the descriptions of the extensions to these base ISAs. Again, any extension that does note require M-mode to operate can be described in the unprivileged specification.

Each extension to the base ISA is developed and maintained by a Task Group:

 - Crypto Task Group working on cryptographic extensions which can move many complex cryptographic algorithms into hardware, improving reliability and speed.
 - B Extension Task Group working on bit manipulation extensions which can speed up many common mathematical tasks.
 - Vector (V) Extension Task Group working on vector instructions which are at the heart of many graphical processing computations.

Once ratified, these extensions are added to the unprivileged specification. The following are some of the ratified extensions that you might see in a RISC-V processor:

- reference: specifications: https://riscv.org/technical/specifications/
- Volume 1, Unprivileged Specification version 20191213: https://drive.google.com/file/d/1s0lZxUZaa7eV_O0_WsZzaurFLLww7ou5/view
- Volume 2, Privileged Specification version 20211203: https://drive.google.com/file/d/1EMip5dZlnypTk7pt4WWUKmtjUKTOkBqh/view
- The RISC-V Instruction Set Manual, Volume I: Base User-Level ISA: https://www2.eecs.berkeley.edu/Pubs/TechRpts/2011/EECS-2011-62.pdf
- The RISC-V Instruction Set Manual, Volume I: User-Level ISA Version 2.0: https://www2.eecs.berkeley.edu/Pubs/TechRpts/2014/EECS-2014-54.pdf
- The RISC-V Instruction Set Manual, Volume I: User-Level ISA Version 2.1: https://www2.eecs.berkeley.edu/Pubs/TechRpts/2016/EECS-2016-118.pdf
- The RISC-V Instruction Set Manual, Volume II: Privileged Architecture Version 1.9: https://www2.eecs.berkeley.edu/Pubs/TechRpts/2016/EECS-2016-129.pdf

“M” Standard Extension <br>
Chapter 7 of the Unprivileged Specification describes how integer multiplication and division should be accomplished. It describes how each of the multiplication instructions (MUL, MULH, MULHU, MULHU, MULW) will behave, which registers are used for the multiplier and multiplicand, and where the result will be stored. It does the same for division since functionally one can view division as simply the inverse of multiplication. It may seem odd to you that this extension is not required. However, for many embedded processors, multiplication can be done in software if it is not required very often or even at all. Removing this logic from a processor will save money on development, keeping the end product cost lower.

“F” Standard Extension <br
Chapter 11 describes how we add single-precision floating-point computational instructions that are compliant with the IEEE 754-2008 arithmetic standard. There are many resources available covering the details of floating-point arithmetic in computing. It is enough to understand that this chapter describes how this process is implemented in RISC-V, and is complimented by Chapter 12 (the D extension) which describes double-precision floating-point computational instructions. Lastly, Chapter 13 covers the Q standard extension for 128-bit quad-precision binary floating-point instructions. All three of these conform to IEEE standards. Again, many embedded applications do not require floating point logic, and hence this extension is not part of the Base ISAs.

“C” Standard Extension <br> 
Chapter 16 describes the compressed instruction-set extension which reduces static and dynamic code size by adding short 16-bit instruction encodings for common operations. Typically, 50%–60% of the RISC-V instructions in a program can be replaced with RVC instructions, resulting in a 25%–30% code-size reduction. The C extension is compatible with all other standard instruction extensions. The C extension allows 16-bit instructions to be freely intermixed with 32-bit instructions, with the latter able to start on any 16-bit boundary. As such, with the addition of the C extension to any system, no instructions can raise instruction-address-misaligned exceptions.

This covers most of the currently ratified extensions in the unprivileged specification. However, it is important to note that many extensions are included in the specification in a “draft” or “frozen” stage. As we discussed in the section on “RISC-V Extension Lifecycle”, these specifications are not yet ratified and any implementation should avoid using them in production.

## The privileged specification: Machine-mode (M-mode) or Supervisor-mode (S-mode)

- Volume 2, Privileged Specification: https://drive.google.com/file/d/1EMip5dZlnypTk7pt4WWUKmtjUKTOkBqh/view

As its name suggests, the privileged specification contains descriptions of the RISC-V ISA which operate in Machine Mode (M-mode) or Supervisor Mode (S-mode). These modes have elevated privileges and are therefore described in a completely separate document from the base ISA and standard extensions. This specification also contains additional functionality required for running rich operating systems like Linux.

The first part of each chapter of the privileged specification details the Control and Status Registers (CSRs) which are only accessible from M-mode and S-mode. We will not cover these details here, but will rather focus on other details specific to these two modes.

### Machine-Level (M-Mode) ISA, Version 1.11

This chapter describes the machine-level features available in machine-mode (M-mode). M-mode is used for low-level access to a hardware platform and is the first mode entered at reset, when the processor finishes initializing and is ready to execute code. M-mode can also be used to implement features that are too difficult or expensive to implement in hardware directly. A good example of this would be a watchdog timer implemented in low level software (firmware) which helps the system recover from faults. We will cover three important features of M-mode described in the specification: 
 - non-maskable interrupts
 - physical memory attributes
 - and physical memory protection

#### Non-Maskable Interrupts (NMIs)

Non-maskable interrupts (NMIs) are only used for hardware error conditions. When fired, they cause an immediate jump to an NMI handler running in M-mode, regardless of how that hardware thread has its interrupt enable bit set. In other words, that interrupt will be serviced without a way to block the service in configuration. Each NMI will have a “mcause” register associated with it. This allows implementations to decide how they wish to handle these interrupts and allows them to define many possible causes. NMIs do not reset processor state which enables diagnosis, reporting, and possible containment of the hardware error.

#### Physical Memory Attributes (PMA)

The physical memory map for a system includes address ranges like: memory regions, memory-mapped control registers, and empty holes in the address space. Some memory regions might not support reads, writes, or execution; some might not support subword or subblock accesses; some might not support atomic operations; and some might not support cache coherence or might have different memory models. In RISC-V systems, these properties and capabilities of each region of the machine’s physical address space are termed physical memory attributes (PMAs).

The PMAs of some memory regions are fixed at chip design time—for example, for an on-chip ROM. Others are fixed at board design time, depending, for example, on which other chips are connected to off-chip buses. Some devices might be configurable at run time to support different uses that imply different PMAs—for example, an on-chip scratchpad RAM might be cached privately by one core in one end-application, or accessed as a shared non-cached memory in another end-application. Most systems will require that at least some PMAs are dynamically checked in hardware later in the execution pipeline after the physical address is known, as some operations will not be supported at all physical memory addresses, and some operations require knowing the current setting of a configurable PMA attribute.

For RISC-V, we separate out specification and checking of PMAs into a separate hardware structure, the “PMA checker”. In many cases, the attributes are known at system design time for each physical address region, and can be hardwired into the PMA checker. Where the attributes are run-time configurable, platform-specific memory-mapped control registers can be provided to specify these attributes at a granularity appropriate to each region on the platform (e.g., for an on-chip static random-access memory (SRAM) that can be flexibly divided between cacheable and uncacheable uses).

The details of PMAs are described in detail in section 3.5 of the Privileged Specification. Advanced users may want to review this section.

#### Physical Memory Protection (PMP)

A common feature of most modern processors is some way of performing secure remote computation or a “trusted execution environment”. Examples of this technology include Intel Software Guard Extensions (SGX), AMD Secure Encrypted Virtualization (SEV), and Arm TrustZone. While the RISC-V ISA does not provide an end-to-end solution for Trusted Execution Environments, the physical memory protection (PMP) capabilities are a solid foundation on which one might construct such a system.

RISC-V PMP limits the physical addresses accessible by software running on a hart (hardware thread). An optional PMP unit provides per-hart machine-mode control registers to allow physical memory access privileges (read, write, execute) to be specified for each physical memory region. The PMP values are checked in parallel with the PMA checks we covered in the last section. The granularity of PMP access control settings are platform-specific and within a platform may vary by physical memory region, but the standard PMP encoding supports regions as small as four bytes. Certain regions’ privileges can be hardwired—for example, some regions might only ever be visible in machine mode but in no lower-privilege layers.

PMP entries are described by an 8-bit configuration register and one 32 (or 64) bit address register. Up to 16 PMP entries are supported. If any PMP entries are implemented, then all PMP CSRs must be implemented, but any PMP CSR fields may be hardwired to zero. PMP CSRs are only accessible to M-mode.

#### Supervisor-Level (S-Mode) ISA

The RISC-V supervisor-level architecture, contains a common core that is used with various supervisor-level address translation and protection schemes. Supervisor mode is deliberately restricted in terms of interactions with underlying physical hardware, such as physical memory and device interrupts, to support clean virtualization. In this spirit, certain supervisor-level facilities, including requests for timer and interprocessor interrupts, are provided by implementation-specific mechanisms. In some systems, a supervisor execution environment (SEE) provides these facilities in a manner specified by a supervisor binary interface (SBI). Other systems supply these facilities directly, through some other implementation-defined mechanism.

RISC-V supports Page-Based 32-bit, 39-bit, and 48-bit virtual memory addressing. The supervisor (S-Mode) memory-management fence instruction (SFENCE.VMA) is used to synchronize updates to in-memory memory-management data structures with current execution. Executing this instruction guarantees that any previous stores already visible to the current RISC-V hart (hardware thread) are ordered before all subsequent implicit references from that hart to the memory-management data structures.

Virtual Memory is a concept which takes several months of graduate level education to grasp and is beyond the scope of this course. It is enough for this course that you understand that RISC-V supports Page-Based virtual memory of several widths, and that there is a special S-Mode instruction used for synchronizing updates between hardware threads.

### Non-ISA Specifications

Task Groups can also work on software or standards that are not part of the ISA. For example, the following groups work on projects that do not lead to specifications being written, but rather standards that encourage communities to develop their products around a common framework:

 - Debug Task Group working on external debugging support and standards.
 - Compliance Task Group working on RISC-V ISA compliance tests and frameworks.
 - Configuration Structure Task Group working on how to represent the configuration structure of a given hardware implementation both in a human-readable format, as well as a binary format.

## RISC-V in practice: Write a simple “Hello World” program in RISC-V 64 bit assembly language & QEMU emulation

For programming assembly instructions, we can use both the ABI reference documentation and the ASM manual to answer any questions we may have along the way. You can find those documents here:

- RISC-V specifications: https://riscv.org/technical/specifications/
- ABI & elf spec: https://github.com/riscv-non-isa/riscv-elf-psabi-doc/blob/master/riscv-elf.adoc
- RISC-V assembler programmers manual: https://github.com/riscv-non-isa/riscv-asm-manual/blob/master/riscv-asm.md

### RISC-V assembly languaje overview

  RISC-V is a “reduced instruction set” architecture, and as such, there are not many instructions to learn. In this tutorial, we only use 3 instructions: **LA** (load absolute address), **ADDI** (add immediate), and **ECALL**. The **ECALL** instruction is used to make a service request to the execution environment. We will only use two calls in our Hello World app, one to “write” and one to “exit”.

  For a full list of instructions you can see the RISC-V Unprivileged Specification Chapter 24 “RV32/64G Instruction Set Listings”. If you’d like to learn more about assembly language programming there are plenty of books and courses available. For more information, visit: https://riscv.org/learn/

### Compiling Required Binaries

Instructions for compiling required binaries can be found in the "RISC-V - Getting Started Guide": https://risc-v-getting-started-guide.readthedocs.io/en/latest/linux-qemu.html

prerequisites for Ubuntu/Debian systems: 

```
sudo apt install autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev \
                 gawk build-essential bison flex texinfo gperf libtool patchutils bc \
                 zlib1g-dev libexpat-dev git
```

  f you are already comfortable with compiling the Linux kernel, QEMU, and software suites like BusyBox, you may want to take things a step further. There is a build system for creating Linux based root file systems and emulating them called the Yocto Project. RISC-V has a “layer” which can be used to create a completely custom Linux distribution. For more details see meta-riscv on GitHub: https://github.com/riscv/meta-riscv

### Environment Overview

Environment Overview

```
-----code-----
# Simple RISC-V Hello World                                                                                       

.global _start                                                                                      

_start: addi  a0, x0, 1
        la    a1, helloworld
        addi  a2, x0, 13
        addi  a7, x0, 64
        ecall

        addi    a0, x0, 0
        addi    a7, x0, 93
        ecall

.data
helloworld:      .ascii “Hello World!\n” 
-----end code-----

There are also two ways of compiling this code, either using GCC or calling “as” and “ld” directly:

-----code-----
# GCC
riscv64-linux-gnu-gcc -o rv-hello rv-hello.s -nostdlib -static                                                                      

# AS & LD
riscv64-linux-gnu-as -march=rv64imac -o rv-hello.o rv-hello.s
riscv64-linux-gnu-ld -o rv-hello rv-hello.o 
-----end code-----
```


