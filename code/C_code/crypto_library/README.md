# Crypto library example code

This folder should contain two directories:

- cryptolib : this is the cryptographic library with the stream cipher.
- cryptCLI  : this is the CLI program that use the shared library cryptolib.

Each folder has the source code, its makefile to build the executables, and 
their corresponding test. 

To build the cryptolib library, it is only needed to run 'make' into it's folder. 
This will build the library. To test it, the run './test', and this would test it.

To build cryptCLI, previously the library needs to be build. After that, to build
the CLI program, run 'make' in its folder, this would dynamically link with it the shared library
at the crytolib folder, and build the 'crypt' program. To use it run './crypt' 
with the appropiate options, or set the folder into your PATH variable to use it like 'crypt',
or use 'make install'.

To install 'crypt', run: 'make install', and this would install it into /usr/local/bin.

To test cryptCLI, run the shell script ./test, this would verify different requirements
and possible incorrect uses of the command. 

In both folders, exits a git repo, to verify the workflow. 

