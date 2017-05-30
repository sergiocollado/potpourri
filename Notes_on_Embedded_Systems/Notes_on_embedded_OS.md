# NOTES ON EMBEDDED OPERATING SYSTEMS.

# KERNEL ARCHITECTURES

 - Monolitic
 - Microkernel
 - Modular
 

# [CONTIKI](http://www.contiki-os.org/)

This OS is intended for IoT devices. It uses a modular kernel.

It was created by Adam Dunkels  in 2002, and its Open Source. It is specifically designed for network and memory constrained systems. It's
main focus is in low power wireless sensor systems and Internet-of-Things devices. So is a lightweight OS, enought to comply the requirements
of an embedded device, with small memory and battery powered. Its footprint is about 10kb of RAM, and 30kb of ROM.

- It uses protothreads, software flow control.- protothreads, is a mechanism that mixes an event-driven model and threads, to 
provide a sequential flow control without using complex state machines.

- It has a full TPC/IP implementations stack.- Includes IPv4 and IPv6

- It also supports low power wireless standards as: 6LoWPAN, RPL, and CoAP.

- It also provides mechanims for efficient memory allocation.

- It is based in a modular kernel, that supports dynamic module loading and linking at run-time.

- It has a mechanism for estimating the system's power consumpiton.

- It supports several hardware devices.

- It is easy to port Contiki to new harware, with little effort.

- To rapid implementation of wireless networks, it provides the Cojaa Network Simulator.

- It has a Command Line Shell suitable for debugging applications.

Reference: http://www.contiki-os.org/

