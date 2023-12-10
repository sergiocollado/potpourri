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

- refernece: specifications: https://riscv.org/technical/specifications/

## Specifications organization

The RISC-V ISA is broken up into two parts:

- Volume 1, Unprivileged Specification
- Volume 2, Privileged Specification
- 
To understand why the specification is broken up into two different parts, we must first understand a bit about computer architecture and security. Historically, processors used hierarchical protection domains, often called protection rings, to protect data and code from malicious actors.

![protection rigs](https://upload.wikimedia.org/wikipedia/commons/2/2f/Priv_rings.svg)

- reference: https://commons.wikimedia.org/w/index.php?curid=8950144

he most privileged code runs in “Ring 0” and has access to the entire system. The processor will decide which privileges to grant executing code based on the privilege level. As an example, accessing memory by physical address may be restricted to “Ring 0” such that other rings must reference the virtual address space. Typically the processor can run in only one of the privilege modes at a time and there are special instructions to move between modes. All of these details can change from system to system, however they must follow the rules set out in the specification documents of a given architecture.

RISC-V currently has three privilege levels: User Mode (U-mode), Supervisor Mode (S-mode), and Machine Mode (M-mode). One can think of these as “Ring 2”, “Ring 1”, and “Ring 0” respectively. Other modes like a hypervisor mode (H-mode) will likely be added in the near future. Much like in the figure above, U-mode is for user processes, S-mode is for kernel and/or device drivers, and M-mode is used for bootloader and/or firmware. Each privilege level has access to specific Control and Status Registers (CSRs), and higher privilege levels can access the CSRs of those less privileged levels.


