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

For building and running
```
make -C tools/testing/selftests run_tests
```

For cross compiling:
``` 
make --silent -C ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- tools/testing/selftests
make --SILENT -C ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- tools/testing/serlftests/timers
```

for cleaning
```
make keselftests-clean
```

NOTE: if you run the tests as root, the coverage will be increased, because some tests need to be the root user. 




