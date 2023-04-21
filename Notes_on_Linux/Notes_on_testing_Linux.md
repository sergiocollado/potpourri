# Notes on testing linux

Reference: https://docs.kernel.org/dev-tools/testing-overview.html

## Kselftests

reference: https://docs.kernel.org/dev-tools/kselftest.html <br>
reference: https://kselftest.wiki.kernel.org/ <br>
reference: https://github.com/torvalds/linux/blob/master/Documentation/dev-tools/kselftest.rst <br>
reference: https://lca-kernel.ozlabs.org/2022-Gow-Kernel-Testing-with-KUnit-Bridging-the-Gap.pdf <br>
reference: https://linuxfoundation.org/wp-content/uploads/Mentorship-Session_-Kernel-Validation-With-Kselftest.pdf <br> 
reference: https://www.youtube.com/watch?v=LQUGxewY1GI "How to write your first kernel selftest" - Michael Ellerman (LCA 2021 Online) <br>
reference: https://www.youtube.com/watch?v=mpO_iDEMqWQ "Mentorship Session: Kernel Validation With Kselftest" <br>

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
make kselftests-clean
```

For building and running
```
make -C tools/testing/selftests run_tests
make kselftest
make summary=1 kselftest # outputs a summary
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
make --silent -C tools/testing/selftests/size run_tests summary=1 # reports a summary
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

### Install kselftest

The tests can be installed anywhere you want. The kselftest_install.sh creates run_kselftest.sh, the script provides all the enviroment to run the test.

```
.cd tools/testing/selftests
./kselftest_install.sh <install location>
./kselftests_install.sh /tmp
```

The TARGET option can be used to select a subset of the tests to build

```
make kselftests-install TARGETS="breakpoints timers"
```

to run all the tests that were successfully build: 

```
./run_kselftests.sh -s # -s is for summary
```


### Generation of a kselftest tar ball

to generate a tar tool in tools/testing/selftests 

```
cd tools/testing/selftests
./gen_kselftests_tar.sh [tar | targz | tarbaz2 | tarxz] # default is .gz
```

This is useful for installation on an external DUT (Device Under Tests).


### kselftest example

In `/tools/testing/selftests/user`, in the Makefile we can see the used tests.

```
#!/bin/sh
# SPDX-License-Identifier: GPL-2.0
# Runs copy_to/from_user infratructure using test_user_copy kernel module

# Kselftest framework requirment - SKIP code is 4.
ksfts_skip=4

if ! /sbin/modprove -q -n tests_user_copy; then
        echo "user: module test_user_copy is not found [SKIP]"
        exit $ksft_skip
fi
if /sbin/modprobe -q test_user_copy; then
        /sbin/modprobe -q -r test_user_copy
        echo "user_copy: ok"
else
        echo "user_copy: ok"
else 
        echo "user_copy: [FAIL]"
        exit 1
fi
```


### build/cross-build tests for specific configs

Individual tests add config file with required dependecies
```
ls tools/testing/selftests/*/config
```

`make kselftest-merget`generates kernel config to include individual test config file

```
cd tools/testing/selftests
ls */configs
```

For example: cpugreq/config

It will show the particular test requires all the kernel configuration to be enabled to run. I 

If use `kselftest-merge`, it takes all the config file into a single config file for kernel to build. 

```
cd ../../..
make kselftest-merge
```

what does, it takes all the config options and enable them in .config, it will generate a config for you and then
you can build the kernel wit all those options enabled. 


## KUnit

reference: https://docs.kernel.org/dev-tools/kunit/ <br>
reference: https://kunit.dev/ <br>
reference: https://kunit.dev/third_party/kernel/docs/start.html#writing-your-first-test <br>
reference: https://www.youtube.com/watch?v=507n-t0sfcU LPC2019 - KUnit - Unit Testing for the Linux Kernel <br>
reference: For general information about KUnit and `kunit.py`, please refer to `Documentation/dev-tools/kunit/start.rst`. <br>
reference: https://mairacanal.github.io/kernel-symbol-table-compilation-more/
reference: https://mairacanal.github.io/from-selftests-to-KUnit/

KUnit is a lightweight unit testing framework for the Linux kernel. These tests are able to be run locally on a developer’s workstation without a VM or special hardware.

KUnit is heavily inspired by JUnit, Python’s unittest.mock, and Googletest/Googlemock for C++. KUnit provides facilities for defining unit test cases, grouping related test cases into test suites, providing common infrastructure for running tests, and more.

UML (User-Mode-Linux) is a Linux architecture (ARCH=um) which builds the kernel as a normal user-mode binary. It's used, amonst other things, as the default architecture for KUnit tests, and acts as a very fast, lightweight platform for running and testing kernel code.

To run KUnit tests, you’ll need to provide a ‘.kunitconfig’ file, which contains the list of test modules to build, and their dependencies.

To create a `.kunitconfig`, using the KUnit defconfig:

```
cd $PATH_TO_LINUX_REPO
cp tools/testing/kunit/configs/default.config .kunit/.kunitconfig
``` 

Then, you have to update: `.kunit/.kunitconfig` 

We can then add any other Kconfig options. For example:

```
CONFIG_LIST_KUNIT_TEST=y
```

```
./tools/testing/kunit/kunit.py config
./tools/testing/kunit/kunit.py build
```


Once you have the kunitconfig file, just run your desired test:

```
./tools/testing/kunit/kunit.py run "longest-symbol"
```

Also, You may want to run KUnit with flags like:

```
./tools/testing/kunit/kunit.py run --timeout=30 --jobs=24 --defconfig
``` 

The `--defconfig` flag, uses an default kunitconfig in the kernel source.

For more information on the different flags, use: `./tools/testing/kunit/kunit.py run --help`.

This will build a UML (User Mode Linux) kernel, run the specified tests, and print the results (nicely formatted) to the screen.

```
sergio@laptop:~/repos/linux$ ./tools/testing/kunit/kunit.py run --timeout=30 --jobs=24 --alltests
[20:22:00] Configuring KUnit Kernel ...
Generating .config ...
Populating config with:
$ make ARCH=um O=.kunit olddefconfig
[20:22:03] Building KUnit Kernel ...
Populating config with:
$ make ARCH=um O=.kunit olddefconfig
Building with:
$ make ARCH=um O=.kunit --jobs=24
/usr/bin/ld: warning: arch/x86/um/vdso/vdso.o: missing .note.GNU-stack section implies executable stack
/usr/bin/ld: NOTE: This behaviour is deprecated and will be removed in a future version of the linker
/usr/bin/ld: warning: .tmp_vmlinux.kallsyms1 has a LOAD segment with RWX permissions
/usr/bin/ld: warning: .tmp_vmlinux.kallsyms1.o: missing .note.GNU-stack section implies executable stack
/usr/bin/ld: NOTE: This behaviour is deprecated and will be removed in a future version of the linker
/usr/bin/ld: warning: .tmp_vmlinux.kallsyms2 has a LOAD segment with RWX permissions
/usr/bin/ld: warning: .tmp_vmlinux.kallsyms2.o: missing .note.GNU-stack section implies executable stack
/usr/bin/ld: NOTE: This behaviour is deprecated and will be removed in a future version of the linker
/usr/bin/ld: warning: vmlinux has a LOAD segment with RWX permissions

[20:23:04] Starting KUnit Kernel (1/1)...
[20:23:04] ============================================================
[20:23:05] =============== time_test_cases (1 subtest) ================
[20:23:05] [PASSED] time64_to_tm_test_date_range
[20:23:05] ================= [PASSED] time_test_cases =================
[20:23:05] ================== resource (2 subtests) ===================
[20:23:05] [PASSED] resource_test_union
[20:23:05] [PASSED] resource_test_intersection
[20:23:05] ==================== [PASSED] resource =====================
[20:23:05] ================ sysctl_test (10 subtests) =================
[20:23:05] [PASSED] sysctl_test_api_dointvec_null_tbl_data
[20:23:05] [PASSED] sysctl_test_api_dointvec_table_maxlen_unset
[20:23:05] [PASSED] sysctl_test_api_dointvec_table_len_is_zero
[20:23:05] [PASSED] sysctl_test_api_dointvec_table_read_but_position_set
[20:23:05] [PASSED] sysctl_test_dointvec_read_happy_single_positive
[20:23:05] [PASSED] sysctl_test_dointvec_read_happy_single_negative
[20:23:05] [PASSED] sysctl_test_dointvec_write_happy_single_positive
[20:23:05] [PASSED] sysctl_test_dointvec_write_happy_single_negative
[20:23:05] [PASSED] sysctl_test_api_dointvec_write_single_less_int_min
[20:23:05] [PASSED] sysctl_test_api_dointvec_write_single_greater_int_max

...

[20:23:05] ============== mctp_test_route_input_sk_keys ===============
[20:23:05] [PASSED] direct match
[20:23:05] [PASSED] flipped src/dest
[20:23:05] [PASSED] peer addr mismatch
[20:23:05] [PASSED] tag value mismatch
[20:23:05] [PASSED] TO mismatch
[20:23:05] [PASSED] broadcast response
[20:23:05] [PASSED] any local match
[20:23:05] ========== [PASSED] mctp_test_route_input_sk_keys ==========
[20:23:05] ====================== [PASSED] mctp =======================
[20:23:05] ============================================================
[20:23:05] Testing complete. Ran 391 tests: passed: 384, skipped: 7
[20:23:05] Elapsed time: 65.065s total, 2.901s configuring, 61.347s building, 0.787s running
``` 

`./tools/testing/kunit/kunit.py run --make_options LLVM=1 --arch=um`


To start looking into writing tests, you can look into: `tools/testing/kunit/kunit.py and the example test under lib/kunit/kunit-example-test.c`
