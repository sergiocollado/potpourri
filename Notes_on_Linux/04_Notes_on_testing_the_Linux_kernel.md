# Notes on testing the Linux kernel

References:
 - https://docs.kernel.org/dev-tools/testing-overview.html
 - https://sergioprado.blog/how-is-the-linux-kernel-tested/ <br>

## Kselftests

reference: https://docs.kernel.org/dev-tools/kselftest.html <br>
reference: https://kselftest.wiki.kernel.org/ <br>
reference: https://kunit.dev/third_party/kernel/docs/ <br>
reference: https://github.com/torvalds/linux/blob/master/Documentation/dev-tools/kselftest.rst <br>
reference: https://lca-kernel.ozlabs.org/2022-Gow-Kernel-Testing-with-KUnit-Bridging-the-Gap.pdf <br>
reference: https://linuxfoundation.org/wp-content/uploads/Mentorship-Session_-Kernel-Validation-With-Kselftest.pdf <br> 
reference: https://www.youtube.com/watch?v=LQUGxewY1GI "How to write your first kernel selftest" - Michael Ellerman (LCA 2021 Online) <br>
reference: https://www.youtube.com/watch?v=mpO_iDEMqWQ "Mentorship Session: Kernel Validation With Kselftest" <br>

The purpose of kselftest is to provide kernel developers and end-users a quick method of running tests against the Linux kernel. 

The tests are writteng in C language and in shell scripts, and they run in userspace. Kselfetest are very well suited to test
new features from the developers. 

The source code for the kselftest is at: `tool/testing/selftests` 

You can see passing selftests here: https://staging.kernelci.org/test/ <br>

### Building and running ksefltests

For building:
```
make headers
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
reference: https://mairacanal.github.io/kernel-symbol-table-compilation-more/ <br>
reference: https://mairacanal.github.io/from-selftests-to-KUnit/
reference: https://docs.kernel.org/dev-tools/kunit/start.html#writing-your-first-test

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

Writing your first test: https://docs.kernel.org/dev-tools/kunit/start.html#writing-your-first-test

### How to execute Kunit at boot in a VM in Qemu

For building the VM I use the syzkaller method: 
- https://github.com/google/syzkaller/blob/master/docs/linux/setup.md
- https://github.com/google/syzkaller/blob/master/docs/linux/setup_ubuntu-host_qemu-vm_x86-64-kernel.md

In my repo folder, I have a linux folder (with the source code) and an image folder (with the bullseye image)

```
#To kill the running QEMU instance press Ctrl+A 
#syzkaller login: root
#remote access with: ssh -i $IMAGE/bullseye.id_rsa -p 10021 -o "StrictHostKeyChecking no" root@localhost	

- reference: kunit at boot: https://kunit.dev/third_party/kernel/docs/running_tips.html
- reference: make modules_install: https://subscription.packtpub.com/book/iot-and-hardware/9781803240060/2/ch02lvl1sec05/building-and-installing-modules
- reference: https://www.kernel.org/doc/Documentation/kbuild/modules.txt 

#in the linux (src code) directory
vim .config
# set CONFIG_KUNIT=y
# set CONFIG_LONGEST_SYM_KUNIT_TEST=y
make olddefconfig # for updating the options dependencies
time make -j($nproc)
make modules

cd ../image 
#execute the ./create-image.sh script commenting the two last lines
# go and comment those last two lines
./create-image.sh
cd ../linux #install the modules in the ./image/bullseye 
sudo INSTALL_MOD_PATH=./../image/bullseye make modules_install
cd ../image/
# next step is the magic, the local rootfs is copied to the mnt filesystem.
sudo cp -a bullseye/. /mnt/bullseye/. 
sudo umount /mnt/bullseye

cd ..

qemu-system-x86_64 \
        -m 2G \
        -smp 2 \
        -kernel ./linux/arch/x86/boot/bzImage \
        -append "console=ttyS0 root=/dev/sda earlyprintk=serial net.ifnames=0" \
        -drive file=./image/bullseye.img,format=raw \
        -net user,host=10.0.2.10,hostfwd=tcp:127.0.0.1:10021-:22 \
        -net nic,model=e1000 \
        -enable-kvm \
        -nographic \
        -pidfile vm.pid \
        2>&1 | tee vm.log

# you can check the boot log at vm.log file; gedit vm.log &
[   29.744949]     KTAP version 1
[   29.745344]     # Subtest: longest-symbol
[   29.745886]     # module: longest_symbol_kunit
[   29.745899]     1..4
[   29.746953]     ok 1 test_longest_symbol
[   29.748634]     # test_longest_symbol_kallsyms: test_longest_symbol kallsyms: kprobe registered
[   29.750264]     ok 2 test_longest_symbol_kallsyms
[   29.750415]     ok 3 test_longest_symbol_plus1
[   29.752684]     # test_longest_symbol_plus1_kallsyms: test_longest_symbol_plus1 kallsyms: kprobe registered
[   29.754564]     ok 4 test_longest_symbol_plus1_kallsyms
[   29.754581] # longest-symbol: pass:4 fail:0 skip:0 total:4
[   29.755395] # Totals: pass:4 fail:0 skip:0 total:4
[   29.756095] ok 39 longest-symbol
```

## LTP Linux Test Project

references:
- https://github.com/linux-test-project/ltp
- https://linux-test-project.readthedocs.io/en/latest/
- https://ltp.sourceforge.net/documentation/how-to/ltp.php
- https://www.redhat.com/sysadmin/linux-test-project-ltp
- https://linuxlink.timesys.com/docs/wiki/engineering/HOWTO_Use_LTP

Linux Test Project is a joint project started by SGI, OSDL and Bull developed and maintained by IBM, Cisco, Fujitsu, SUSE, Red Hat, Oracle and others. The project goal is to deliver tests to the open source community that validate the reliability, robustness, and stability of Linux.

The LTP testsuite contains a collection of tools for testing the Linux kernel and related features. The goal is to improve the Linux kernel and system libraries by bringing test automation to the testing effort. Interested open source contributors are encouraged to join.


## Sparse

references:
 - https://sparse.docs.kernel.org/en/latest/
 - https://en.wikipedia.org/wiki/Sparse
 - https://kernelnewbies.org/Sparse (how to install)
 - https://lwn.net/Articles/689907/
 - https://www.kernel.org/doc/html/latest/dev-tools/sparse.html


Sparse is a computer software tool designed to find possible coding faults in the Linux kernel.[2] Unlike other such tools, this static analysis tool was initially designed to only flag constructs that were likely to be of interest to kernel developers, such as the mixing of pointers to user and kernel address spaces.

Sparse, the semantic parser, provides a compiler frontend capable of parsing most of ANSI C as well as many GCC extensions, and a collection of sample compiler backends, including a static analyzer also called sparse. Sparse provides a set of annotations designed to convey semantic information about types, such as what address space pointers point to, or what locks function acquires or releases.

Linus Torvalds started writing Sparse in 2003, initially targeting issues such as mixing pointers to user address space and pointers to kernel address space.

Josh Triplett was Sparse’s first maintainer in 2006. This role was taken over by Christopher Li in 2009 and by Luc Van Oostenryck in late 2018.

## lockdep : Runtime locking correctness validator

references: 
 - https://www.kernel.org/doc/Documentation/locking/lockdep-design.txt

   
## Kernel Memory Leak Detector

references:
 - https://www.kernel.org/doc/html/v4.9/dev-tools/kmemleak.html

## Kernel Memory sanitizer KSAN

references: 
 - https://docs.kernel.org/dev-tools/kmsan.html

## skykaller

References:
- https://github.com/google/syzkaller
- bug hunting: https://docs.kernel.org/admin-guide/bug-hunting.html
- https://javiercarrascocruz.github.io/syzbot

## Sparce

- https://lwn.net/Articles/689907/

## Smatch

- https://javiercarrascocruz.github.io/smatch
- https://www.kernel.org/doc/Documentation/dev-tools/testing-overview.rst
- https://mudongliang.github.io/2022/03/16/run-smatch-over-mainline-kernel.html
- https://events.linuxfoundation.org/wp-content/uploads/2022/10/Dan-Carpenter-Smatch-Mentorship-Series-Presentation-Template.pdf
- https://www.youtube.com/watch?v=zZGvKcPYhe0


