This folder corresponds to the CLI program for cipher messages.

Under the hood, it uses the dynamic libray at ./../cryptolib to perform the ciphering.

The general program is in main.c, but it uses the auxiliar files: common\_functions.c/.h

To build it, just run: 'make'

To clean the files, run: 'make clean'

To install the program, run: 'make install' and it will be moved to /usr/local/bin. 

A test suit is at the shell script: 'test'. To run it, just command: ./crypt with the wanted parameters

The program invocation shall agree to the following syntax:

```
crypt [-h] -k <key> | -f <key_file> [-o <output_file>] [<input_file>]
```

Parameters:

- -h: the program shall print usage information on standard error and exit. No other parameters shall be
processed nor required when -h is present.
- -k <key>: used to pass the algorithm key in the command line.
- -f <key\_file>: used to provide the algorithm key in a file.
- -o <output\_file>: write the results in <output\_file>. Standard output shall be used if this parameter is not
provided, or if <output\_file> is a dash sign (-).
- <input\_file>: read the input from <input\_file>. Standard input shall be used if this parameter is not given.

Other requirements:

- Must accept any key of length >= 1 and <=256.
- Should be usable as a “filter” from standard shell, reading continuous data from stdin and emitting output
before the input reaches EOF.
