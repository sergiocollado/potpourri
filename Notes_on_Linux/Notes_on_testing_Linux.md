# Notes on testing linux

Reference: https://docs.kernel.org/dev-tools/testing-overview.html

## Kselftests

reference: https://docs.kernel.org/dev-tools/kselftest.html <br>
reference: https://kselftest.wiki.kernel.org/ <br>
reference: https://linuxfoundation.org/wp-content/uploads/Mentorship-Session_-Kernel-Validation-With-Kselftest.pdf <br> 

The purpose of kselftest is to provide kernel developers and end-users a quick method of running tests against the Linux kernel. 

The tests are writteng in C language and in shell scripts, and they run in userspace. Kselfetest are very well suited to test
new features from the developers. 

The source code for the kselftest is at: `tool/testing/kselftests` 

You can see passing selftests here: https://staging.kernelci.org/test/ <br>

### Building and running ksefltests

For building:
```
make -C tools/testing/selftests #you may have to use sudo
```

for cleaning
```
make keselftests-clean
```

For building and running
```
make -C tools/testing/selftests run_tests
```

For cross compiling:
``` 
make --silent -C ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- tools/testing/selftests
make --SILENT -C ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- tools/testing/serlftests/timers
```

running a subtest of testss

```
make --silent -C toos/testing/selftest/timers #build  the timer tests
make --silent -C tools/testing/selftests/timers run_tests # run timer tests
```

running tests for a single of multiple sub-systmes using the TARGET variable

```
make --silence TARGETS=<name of the tests> kselftests
make --silent TARGETS="size breakpoints timers" kselftests
```
The advantage of the TARGETS variable is that you can launch several groups of tests.

NOTE: if you run the tests as root, the coverage will be increased, because some tests need to be the root user. 

### Output format

The output is TAB (Test Anything Protocol) 

TAP, the Test Anything Protocol, is a simple text-based interface between testing modules in a test harness. It decouples the reporting of errors from the presentation of the reports.

One of its major uses is for noise reduction; when you have a suite of many tests, making them TAP producers and using a TAP consumer to view them helps ensures that you will see everything you need to notice and diagnose breakage without being distracted by a flood of irrelevant success messages. It can assist other forms of analysis and statistics-gathering as well.

reference: https://testanything.org/

The general format is 

```
TAP version
Plan
test line
```

- TAP version indicates this is TAP
- Plan: it indicates how many tests will run.
- test line: at least one line per tests. result ok or not ok

reference: https://testanything.org/tap-version-14-specification.html


Kselftests supports running the tests and saving output files in a separate directory.

```
make --silent O=/tmp/kselftests kselftests 
   # bulilds and runs all the targets in tools/selftests/Makefile
   # executables are created in 0=/temp/kselftests kselftest
```

```
make --silent TARGETS=timers O=/tmp/kselftest kselftest
   # builds and runs all non-desctructive tests in tools/selftests/timers
   # executables are created in 0=/tmp/kselftest/timers
```

