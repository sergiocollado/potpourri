# Notes on building the kernel 

[linux kernel map](https://makelinux.github.io/kernel/map/)

![linux kernel map](https://github.com/sergiocollado/potpourri/blob/master/image/Linux_kernel_map.png "Linux kernel map")

Here was Linux started: https://groups.google.com/g/comp.os.minix/c/dlNtH7RRrGA/m/SwRavCzVE7gJ

![linus_post](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_Linux/images/starting_Linux.png)

list of Linux subsystems: https://www.kernel.org/doc/html/latest/subsystem-apis.html

 - By the way, the best way to search the kernel code online is: https://elixir.bootlin.com/linux/latest/source/include/linux
 - Core Knowledge That Modern Linux Kernel Developer Should Have: https://www.linuxjournal.com/content/core-knowledge-modern-linux-kernel-developer-should-have
 - Linux programming interface: https://archive.org/details/The_Linux_Programming_Interface/page/n4/mode/1up
 - Index of Documentation for People Interested in Writing and/or Understanding the Linux Kernel: https://www.kernel.org/doc/html/latest/process/kernel-docs.html
 - the linux kernel: https://tldp.org/LDP/tlk/tlk-toc.html
 - Kernel coding style: https://www.kernel.org/doc/html/latest/process/coding-style.html
 - HOWTO do Linux kernel development: https://docs.kernel.org/process/howto.html 
 - Linux kernel documentation: https://www.kernel.org/doc/Documentation/
 - Linux kernel coding style: https://www.kernel.org/doc/html/latest/process/coding-style.html
 - email list: https://lore.kernel.org/
 - Mentorship series: https://events.linuxfoundation.org/lf-live-mentorship-series/
 - Linux kernel labs: https://linux-kernel-labs.github.io/refs/heads/master/
 - Linux Inside: https://0xax.gitbooks.io/linux-insides/content/
 - The Linux Kernel Module Programming Guide: https://sysprog21.github.io/lkmpg/
 - To quickly expore the kernel code -> Elixir cross reference: https://elixir.bootlin.com/linux/latest/source/kernel
 - Kernel play guide: https://nskernel.gitbook.io/kernel-play-guide/
 - Linux Kernel module programming guide: https://linux.die.net/lkmpg/index.html
 - Kernel newbies: kernel newbies : https://kernelnewbies.org/FirstKernelPatch
 - Linux kernel workbook: https://lkw.readthedocs.io/en/latest/index.html 
 - Multimedia and Television Support on Linux: https://www.linuxtv.org/ & https://www.kernel.org/doc/html/v4.9/media/uapi/v4l/v4l2.html 
 - Let's code a Linux Driver: https://www.youtube.com/watch?v=x1Y203vH-Dc&list=PLCGpd0Do5-I3b5TtyqeF1UdyD4C-S-dMa
 - Linux standards (ELF, DWARF, FHS ...) : https://refspecs.linuxfoundation.org/index.shtml
 - kernel mail lists: https://subspace.kernel.org/vger.kernel.org.html#
 - The Kernel in mind: https://lnkd.in/gNHPEJqB
 - [The kernel in mind PDF](https://media.licdn.com/dms/document/media/v2/D561FAQGjyeehzYEt8g/feedshare-document-url-metadata-scrapper-pdf/B56ZckXGwwGsA0-/0/1748661730676?e=1779894000&v=beta&t=cgYwKZQyGIbQRI6R55fsnnC6PH9kYMZSzyPBHXWjy-A)
 - Introduction to linux kernel develop proces hasrh: https://www.linkedin.com/pulse/introduction-linux-kernel-development-process-harsh-mistry/


## Linux kernel development process

references:
 - what is a kernel: https://youtu.be/LLBrBBImJt4
 - Getting to Know the Linux Kernel: A Beginner's Guide: https://www.youtube.com/watch?v=QatE61Ynwrw
 - Tim Beale: Linux Kernel Development for Newbies: https://youtu.be/OkhOoBqLb3Y
 - Kernel challenges: https://github.com/agelastic/eudyptula
 - Write and Submit your first Linux kernel Patch: https://youtu.be/LLBrBBImJt4
 - how to write a patch:  https://www.linkedin.com/pulse/fixing-one-line-learning-whole-process-moon-hee-lee-uu0cc/
 - https://www.slideshare.net/SamsungOSG/a-survivors-guide-to-contributing-to-the-linux-kernel
 - Linux kernel development process: https://docs.kernel.org/process/development-process.html
 - The story of my first Linux Kernel Contribution: https://youtu.be/uLiAc_CnqZE
 - linux kernel mentees: https://wiki.linuxfoundation.org/lkmp/lkmp_mentee_blogs
 - https://www.linkedin.com/pulse/introduction-linux-kernel-development-process-harsh-mistry/

How to contribute:
 - Become a Linux kernel contributor - Part 1: https://javiercarrascocruz.github.io/kernel-contributor-1
 - LKMP: https://medium.com/@andrew.kanner/linux-kernel-bug-fixing-2023-experience-ce37aee844ee
 - https://marliere.net/posts/1/
 - Build a minimal Linux system and run it in QEMU: https://ibug.io/blog/2019/04/os-lab-1/
 - Ramfs, rootfs and initramfs: https://www.kernel.org/doc/html/latest/filesystems/ramfs-rootfs-initramfs.htmlç
 - tiny config: https://youtu.be/u2Juz5sQyYQ?si=J4p8VtCpb-CeA5Vv

### Intro to the development process

references:
- https://www.kernel.org/doc/html/latest/process/development-process.html
- How Linux is built with Greg Kroah-Hartman : https://www.youtube.com/watch?v=7WbREHtc5sU
- https://kernelnewbies.org/FirstKernelPatch
- https://www.linkedin.com/pulse/introduction-linux-kernel-development-process-harsh-mistry/

Linux kernel releases come every 2+ months (10 or 11 weeks). Releases are time based and not feature based. 

When the new version is released a 2 week window is open for merging new pulls for the next release. so mantainers send signed git pull requests in that merge window. After that period is created the first relesase candidate, known as **rc1**. So new features are only included in this first merge window.

At this point the release cycle goes into bug fixes-only mode. So release candidates are generated till mayor bug fixes and regressions are solved.

When enough confidence on the quality of the code is reached, the stable version is released. 

More references:
 - https://www.kernel.org/category/releases.html
 - https://www.kernel.org/doc/linux/MAINTAINERS
 - http://vger.kernel.org/vger-lists.html
 - https://lore.kernel.org/lists.html
 - https://git.kernel.org/

#### kernel trees

- linux_mainline: Linus releases mainline kernels and RC releases
- linux_stable: stable releases branches
- linux-next: code from many subsystems gets pulled into the tree and periodically is released for integration testing.

Check the kernel releaes here: https://www.kernel.org/category/releases.html

The stable releases are here: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/refs/heads

### Download the kernel

To download the kernel with git:

```bash
git clone git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
```
or

```bash
git clone https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git linux-mainline
```

To download the stable branch:

```bash
git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git
cd linux-stable
```



### Patches

A common place to see the paches is: https://patchwork.kernel.org/ , many manteiners check the
patches there. 


Linux development is handled with git as a code repository. 

 - https://git-scm.com/book/en/v2/Getting-Started-A-Short-History-of-Git
 - https://git-scm.com/book/en/v2

to generate a patch:

```bash
git format-patch -1 --pretty=fuller XXXXXXXX
```

the code submitted in patches must be signed off:
 - https://www.kernel.org/doc/html/latest/process/submitting-patches.html#sign-your-work-the-developer-s-certificate-of-origin
 - https://www.kernel.org/doc/html/latest/process/submitting-patches.html#using-reported-by-tested-by-reviewed-by-suggested-by-and-fixes
 
and the patch prefixes are:  [PATCH], [PATCH RFC] or [RFC PATCH] or [PATCH v4] 

To create a patch of version 5, you use for example:

```bash
git format-patch -1 -v5
```

### Portal of Linux Kernel patches

 - reference: https://patchwork.kernel.org/

### To apply a patch:

references:
 - https://www.kernel.org/doc/html/v4.10/process/applying-patches.html <br>

```bash
patch -p1 < ../patch-x.y.z
```
to remove it: 

```bash
patch -R -p1 < ../patch-x.y.z
```


To apply a patch from an email (gmail): <br>
reference: https://stackoverflow.com/questions/23594843/applying-email-patch-with-git <br>

You can apply patches from email-formatted patch using any raw data viewer.

For example, GMail, in the current interface, has support for it. You can apply a patch as a commit from a mail message following these steps:
   - Open the GMail web page in the message with patch data
   - Click at the ellipsis icon located at top-right of this message
   - Click at "Show Original". A new tab will open with the content of the message.
   - Click at "Copy to clipboard"
   - Open a terminal and change current directory to git-based root project directory
   - Certify that the working copy is clean
   - Run `git am`
   - Paste the code
   - Type Ctrl-D to finish the insertion

more references:
- https://kernelnewbies.org/FAQ/HowToApplyAPatch



### Codes of conduct

References:
 - https://www.kernel.org/doc/html/latest/process/code-of-conduct.htm
 - https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/LICENSES/preferred/GPL-2.0
 - https://www.kernel.org/doc/html/latest/process/kernel-enforcement-statement.html


How to configure the kernel: https://www.kernel.org/doc/Documentation/kbuild/kconfig.txt

 - kernel documentation: https://www.kernel.org/doc/Documentation/
 - How to write documentation in the code: https://docs.kernel.org/doc-guide/kernel-doc.html


### Configuration of the development system

References:
 - https://ubuntu.com/tutorials/create-a-usb-stick-on-ubuntu#1-overview
 - https://ubuntu.com/tutorials/create-a-usb-stick-on-windows#1-overview

It is recomended 3GB for the boot partition.

The packaget build-essential is needed in the system.


```bash
sudo apt-get install -y build-essential gcc make vim bc git cscope \
rsync libncurses-dev libssl-dev bison flex libelf-dev \
dwarves bc clang llvm lld libclang-dev python3 git-email
```

It is needed to check the minimal requirements to compile the kernel

```
https://www.kernel.org/doc/html/latest/process/changes.html
```

'git-email' is for sending patches through the **sendmail** configuration option once the **smtp** server is configured.

example configuration for gmail: https://gist.github.com/jasonkarns/4354421, https://coderwall.com/p/qcsiew/setting-up-and-using-git-send-email-with-gmail

https://www.kernel.org/doc/html/latest/process/email-clients.html


### Exploring the linux kernel sources

You should create a directory, to git clone the linux repo, for example the mainline: https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/ 

```bash
>> cd /linux_work
>> git clone git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git linux_mainline
>> cd linux_mainline; ls -h

arch          CREDITS                 drivers  ipc      lib          mm       scripts   usr
block    crypto         fs               Kbuild      LICENSES     net      security  virt
certs        cscope.out          include    Kconfig  MAINTAINERS  README      sound
COPYING    Documentation  init     kernel       Makefile          samples  tools
```

or to clone the stable branche:

```bash
git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git linux_stable
```

You can use `cregit-linux` tool, to explore the code: https://cregit.linuxsources.org/ <br>

for example: https://cregit.linuxsources.org/code/5.11/  <br>

The most part of the linux kernel, is in the 'drivers' subdirectory.

In 'arch' we can see all the supported architectures: https://cregit.linuxsources.org/code/5.11/arch/

You can also use 'git log' to explore the different commmits. 

```bash
git format-patch -1 <commit ID>
```

For everyday tinkering with the kernel, take into account the scripts: scripts/get_maintainer.pl and scripts/checkpatch.pl

Also check the linux-kselftest repo

### Generate documentation

- reference: https://subscription.packtpub.com/book/cloud-and-networking/9781789953435/2/ch02lvl1sec21/generating-the-kernel-documentation-from-source

In the source root, execute: 

```bash
$ make pdfdocs
```
or

```bash
$ make htmldocs
```

to analyze the documentation maybe use: 
```bash
$ make htmldocs > doc.log 2>&1
$ make pdfdocs > doc.log 2>&1
```

Find the generated files at: `Documentation/output/latex`.


#### Kconfig: the kernel build system

Reference: 
 - https://www.linuxjournal.com/content/kbuild-linux-kernel-build-system 
 - https://www.kernel.org/doc/html/latest/kbuild/index.html
 - https://www.linkedin.com/pulse/reading-kernel-starts-kconfig-moon-hee-lee-f6qbc/
 - https://www.linkedin.com/pulse/configuration-comes-first-moon-hee-lee-ru6tc/

The kernel has its own build system: the Kernel build sistem: Kbuild.

It has four main components:

 - **config symbols**: conditions to conditionally compile code, include or exclude components.
 - **kconfig files**: files that define the possible config sysmbols. 'make menuconfig' reads the config sysmbols for the kconfig files.
 - **.config file**: files that stored the value of the confi sysmbols. 'make menuconfig' is used to give those values, or the file edited directly.
 - **makefiles**: normal makefiles


#### Compiling the kernel 

 - reference: A Guide to Compiling the Linux Kernel All By Yourself:  https://itsfoss.com/compile-linux-kernel/
 - reference: http://www.kroah.com/lkn/ -linux kernel in a nutshell
 - reference: https://www.cyberciti.biz/tips/compiling-linux-kernel-26.html
 - reference: https://rev2.vasanthdeveloper.com/compiling-the-linux-kernel-on-ubuntu-debian/index.html
 - example: https://youtu.be/NVWVHiLx1sU 
 - example: https://www.youtube.com/watch?v=APQY0wUbBow
 - example: https://youtu.be/E4yRcmQqvWM
 - reference: https://wiki.gentoo.org/wiki/Kernel/Optimization
 - reference: compiling with CLANG: https://www.kernel.org/doc/html/latest/kbuild/llvm.html
 - example: https://youtu.be/s95hjvFAE5g?t=402
 - tiny config: https://youtu.be/u2Juz5sQyYQ?si=J4p8VtCpb-CeA5Vv
 - compiling with Clang/LLVM: https://docs.kernel.org/kbuild/llvm.html

The kernel configuration is in the file named .config at the top of the kernel source tree.

You may need to install:  `libelf-dev`, `libelf-devel` or `elfutils-libelf-devel`.

Run the following command to generate a kernel configuration file based on the current configuration.

```bash
make oldconfig
```

'make oldconfig' reads the existing .config file that was used for an old kernel and prompts the user for options in the current kernel source that are not found in the file. This is useful when taking an existing configuration and moving it to a new kernel.

**Bonuses** make olddefconfig sets every option to their default value without asking interactively. It gets run automatically on make to ensure that the .config is consistent in case you've modified it manually.

If you want to set up an out-of-tree build directory to keep the source clean, use: 

```bash
make O=../build-mainline defconfig

make O=../build-mainline -j$(nproc)
```

This creates a basic default .config and performs a full build using all available CPU cores. The purpose isn’t to run this kernel, but to populate the build directory with enough .cmd files so the next step — generating the compilation database — works properly.

WATCH OUT!: New releases often introduce new configuration variables and, in some cases, rename the configuration symbols. The latter causes problems, and make oldconfig might not generate a new working kernel. Run make listnewconfig after copying the configuration from /boot to the .config file, to see a list of new configuration symbols. 

 - reference: https://stackoverflow.com/questions/4178526/what-does-make-oldconfig-do-exactly-in-the-linux-kernel-makefile
 - reference: https://www.kernel.org/doc/html/latest/kbuild/kconfig.html


Other way to tune the kernel your system is by using **make localmodconfig**. This option creates a configuration file based on the list of modules currently loaded on your system.

```bash
lsmod > /tmp/my-lsmod
make LSMOD=/tmp/my-lsmod localmodconfig
```

A simpler choice is use **make defconfig**, every kernel has a default configuration, so with the 'defconfig' option that default configuration is used.

otherwise use: 

```bash
make menuconfig
```

or 

```bash
make xconfig
```

you can get help:

```bash
sergio@debian:~/linux_work/linux_stable$ make help
Cleaning targets:
  clean		  - Remove most generated files but keep the config and
                    enough build support to build external modules
  mrproper	  - Remove all generated files + config + various backup files
  distclean	  - mrproper + remove editor backup and patch files

Configuration targets:
  config	  - Update current config utilising a line-oriented program
  nconfig         - Update current config utilising a ncurses menu based program
  menuconfig	  - Update current config utilising a menu based program
  xconfig	  - Update current config utilising a Qt based front-end
  gconfig	  - Update current config utilising a GTK+ based front-end
  oldconfig	  - Update current config utilising a provided .config as base
  localmodconfig  - Update current config disabling modules not loaded
                    except those preserved by LMC_KEEP environment variable
  localyesconfig  - Update current config converting local mods to core
                    except those preserved by LMC_KEEP environment variable
  defconfig	  - New config with default from ARCH supplied defconfig
  savedefconfig   - Save current config as ./defconfig (minimal config)
  allnoconfig	  - New config where all options are answered with no
  allyesconfig	  - New config where all options are accepted with yes
  allmodconfig	  - New config selecting modules when possible
  alldefconfig    - New config with all symbols set to default
  randconfig	  - New config with random answer to all options
  yes2modconfig	  - Change answers from yes to mod if possible
  mod2yesconfig	  - Change answers from mod to yes if possible
  listnewconfig   - List new options
  helpnewconfig   - List new options and help text
  olddefconfig	  - Same as oldconfig but sets new symbols to their
                    default value without prompting
  tinyconfig	  - Configure the tiniest possible kernel
  testconfig	  - Run Kconfig unit tests (requires python3 and pytest)

```

Note: the 'tinyoconfig', think is related to: http://www.tinycorelinux.net/


Once this step is complete, it is time to compile the kernel. Using the '-j' option helps the compiles go faster. The '-j' option specifies the number of jobs (make commands) to run simultaneously:

```bash
make -j3 all
```

or to use all processors

```bash
make -j$(nproc)
```

the end of compilation should be like ...

```bash
  ...
  CC      arch/x86/boot/cpu.o
  AS      arch/x86/boot/compressed/efi_thunk_64.o
  CC      arch/x86/boot/compressed/misc.o
  GZIP    arch/x86/boot/compressed/vmlinux.bin.gz
  MKPIGGY arch/x86/boot/compressed/piggy.S
  AS      arch/x86/boot/compressed/piggy.o
  LD      arch/x86/boot/compressed/vmlinux
  ZOFFSET arch/x86/boot/zoffset.h
  OBJCOPY arch/x86/boot/vmlinux.bin
  AS      arch/x86/boot/header.o
  LD      arch/x86/boot/setup.elf
  OBJCOPY arch/x86/boot/setup.bin
  BUILD   arch/x86/boot/bzImage
Kernel: arch/x86/boot/bzImage is ready  (#1)
```
and it should create a 'vmlinux' image.


```bash
make modules
```

Once the compilation is done, you can install it

```bash
su -c "make modules_install install"
```

Then install the kernel (in case you want to update/test the kernel)

```bash
make install 
```

reference: https://www.cyberciti.biz/tips/compiling-linux-kernel-26.html

This command will install the kernel, and execute 'update-grub' to add it to the grub menu: 

```bash
update-grub
```

Summing up the steps to compile and install the kernel:

```bash
make help
cp /boot/config-$(uname -r) ./.config # in debian based distros
make menuconfig
make -j$(nproc)
make modules
sudo make modules_install install
sudo make install
sudo update-grub
```

Before rebooting the system, we can store some logs to compare it later, and look for regression or new errors

We use the dmesg with the -t option, to not display the timestamps. This will make it easier later for comparation.

```bash
dmesg -t > dmesg_current
dmesg -t -k > dmesg_kernel
dmesg -t -l emerg > dmesg_current_emerg
dmesg -t -l alert > dmesg_current_alert
dmesg -t -l crit > dmesg_current_crit
dmesg -t -l err > dmesg_current_err
dmesg -t -l warn > dmesg_current_warn
```

It is expected to be clean:  emerg, alert, crit, and err level messages

Before testing the new kernel, that we don't know if it will boot, a couple of safety measures:

By default, grub tries to boot the default kernel, which is the newly installed kernel. We change the default grub configuration file /etc/default/grub to the boot menu, and pause for us to be able to select the kernel to boot.
 
In case dmesg_current length is zero, it is quite possible that the secure boot is enabled.  That will prevent to boot the new kernel as it is not signed. It is possible to disable temporaly the secure boot with the **mokutil** (MOK manager) 

To check if the secure boot is enabled: 

```bash
mokutil --sb-state
```

https://askubuntu.com/questions/1119734/how-to-replace-or-remove-kernel-with-signed-kernels

to disable validation:

```bash
sudo mokutil --disable-validation
root password
mok password: 1234567
mok password: 1234567
sudo reboot
```
to re-enable validation:

```bash
sudo mokutil --enable-validation
root password
mok password: 1234567
mok password: 1234567
sudo reboot
```
NOTE: if the kernel fails, and you need to remove it: https://askubuntu.com/questions/176322/removing-old-kernel-entries-in-grub

```
for kernels build from source: 
The solution is to manually delete all the files related to the old kernels in the /boot folder and run sudo update-grub. The extra entries vanished
```


Booting the Kernel:

Let’s take care of a couple of important steps before trying out the newly installed kernel. There is no guarantee that the new kernel will boot. As a safeguard, we want to make sure that there is at least one good kernel installed and we can select it from the boot menu. By default, grub tries to boot the default kernel, which is the newly installed kernel. We change the default grub configuration file **/etc/default/grub** to the boot menu, and pause for us to be able to select the kernel to boot.

Please note that this option only applies to Ubuntu and Debian, and other distributions might have a different way to specify boot menu options.

Increase the GRUB_TIMEOUT value to 10 seconds, so grub pauses in menu long enough to choose a kernel to boot:

``` 
Uncomment GRUB_TIMEOUT and set it to 10: GRUB_TIMEOUT=10
Comment out GRUB_TIMEOUT_STYLE=hidden
```

If the newly installed kernel fails to boot, it is nice to be able to see the early messages to figure out why the kernel failed to boot.

Enable printing early boot messages to vga using the earlyprintk=vga kernel boot option:

```
GRUB_CMDLINE_LINUX="earlyprintk=vga"
```
For information in grub: **'info -f grub -n 'Simple configuration''**

NOTE!: Run **update-grub** to update the grub configuration in /boot

```bash
sudo update-grub
```

```bash
sergio@debian:/etc/default$ sudo update-grub
Generating grub configuration file ...
Found background image: /usr/share/images/desktop-base/desktop-grub.png
Found linux image: /boot/vmlinuz-5.12.10
Found initrd image: /boot/initrd.img-5.12.10
Found linux image: /boot/vmlinuz-4.19.0-16-amd64
Found initrd image: /boot/initrd.img-4.19.0-16-amd64
done
```

Now, it is possibble to restart the system. Once the new kernel comes up, compare the saved dmesg from the old kernel with the new one, and see if there are any regressions. If the newly installed kernel fails to boot, you will have to boot a good kernel, and then investigate why the new kernel failed to boot.

### How the kernel is tested
 
 - Kernel Testing Guide: https://www.kernel.org/doc/html/latest/dev-tools/testing-overview.html
 - How are Linux device drivers being tested? : https://marcelosc.gitlab.io/how-is-linux-tested/
 - https://events.linuxfoundation.org/mentorship-session-kernel-validation-with-kselftest/
 - and more...

### kernel compressed images

Usually the source code of the kernel is at: '/usr/src/'

The kernel images are in the '/boot' directory. This directory tipically will have all the files needed in order to boot the system. The file 'vmlinux' is the actual kernel. Regarding the kernel there are 2 main images that are being use, those are: zImage, and bzImage. both are compressed version of teh linux kernel image. 'zImage' was primarely used in older versions of linux systems, and was design to fit in the limited amount of memory that was available, this 'low-memory' as it was call, was the first 640 kB, so the kernel image was reduced to 512 kB in order to fit, and it was in its compress form, so the kernel was compiled and then compress into zImage. 
In more modern systems, the 'bzImage' is used, it stands for 'Big zImage', so bzImage, can use high memory, around the 1MB mark. Now we have the bzImage, and then it is moved into the /boot directory, it is going to be rename as 'vzlinuz-<kernel-version>.<architecture>'

references:
 - https://unix.stackexchange.com/questions/197225/is-vmlinuz-and-bzimage-really-the-same
 - https://en.wikipedia.org/wiki/Vmlinux

 - **vmlinux**: Plain linux ELF file just the way it was created by the linker, including symbols and everything.
 - **vmlinuz**: gzipped vmlinux file which got stripped of all its symbols
 - **zImage**: bootsect.o + setup.o + misc.o + piggy.o (piggy.o contains the piggy-backed vmlinuz). zImage is bootable because it can decompress and run the kernel it contains.
 - **bzImage**: same as zImage except that it is built slightly differently which enables it to carry bigger kernels.

For obtaining the bzImage, for the kernel compilation use the command: 'make bzImage', and that image will be placed at 'arch/<your_arch>/boot/' 

### Initramfs - Initial randome access memory file system

'Initramfs' is part of the Linux startup process and occours just before the root file system is mounted. 
Everytime a new linux image is generated, a new version of initramfs needs to be generated. That is why there are initramfs files in the '/boot' directory.

To generate an Initramfs, use the command: https://linux.die.net/man/8/mkinitrd or in ubuntu: https://manpages.ubuntu.com/manpages/focal/en/man8/mkinitramfs.8.html

References:
 - https://www.linuxfromscratch.org/blfs/view/svn/postlfs/initramfs.html
 - https://wiki.gentoo.org/wiki/Initramfs/Guide
 - https://landley.net/writing/rootfs-intro.html
 - https://www.kernel.org/doc/Documentation/filesystems/ramfs-rootfs-initramfs.txt

### DKMS - Dynamic Kernel Module Support

Dynamic Kernel Module Support (DKMS) is a program/framework that enables generating Linux kernel modules whose sources generally reside outside the kernel source tree. The concept is to have DKMS modules automatically rebuilt when a new kernel is installed.

References: 
 - https://en.wikipedia.org/wiki/Dynamic_Kernel_Module_Support
 - https://linux.die.net/man/8/dkms

An essential feature of DKMS is that it automatically recompiles all DKMS modules if a new kernel version is installed. This allows drivers and devices outside of the mainline kernel to continue working after a Linux kernel upgrade.

Another benefit of DKMS is that it allows the installation of a new driver on an existing system, running an arbitrary kernel version, without any need for manual compilation or precompiled packages provided by the vendor.

DKMS was written by the Linux Engineering Team at Dell in 2003. It is included in many distributions, such as Ubuntu, Debian, Fedora, SUSE, Mageia and Arch. DKMS is free software released under the terms of the GNU General Public License (GPL) v2 or later.

DKMS supports both the rpm and deb package formats out of the box.


### Debugging kernel panics

https://sanjeev1sharma.wordpress.com/tag/debug-kernel-panics/
https://www.opensourceforu.com/2011/01/understanding-a-kernel-oops/

Decode and Analyze the Panic Message
Panic messages can be decoded using the decode_stacktrace.sh tool. Please refer to decode_stacktrace https://lwn.net/Articles/592724/ : make stack dump output useful again for details on how to use the tool.

https://www.kernel.org/doc/html/latest/trace/events.html
