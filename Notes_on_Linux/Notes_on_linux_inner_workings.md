# Notes on Linux inner workings


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


## Linux kernel development process

references:
 - what is a kernel: https://youtu.be/LLBrBBImJt4
 - Getting to Know the Linux Kernel: A Beginner's Guide: https://www.youtube.com/watch?v=QatE61Ynwrw
 - Tim Beale: Linux Kernel Development for Newbies: https://youtu.be/OkhOoBqLb3Y
 - Kernel challenges: https://github.com/agelastic/eudyptula
 - Write and Submit your first Linux kernel Patch: https://youtu.be/LLBrBBImJt4
 - https://www.slideshare.net/SamsungOSG/a-survivors-guide-to-contributing-to-the-linux-kernel
 - Linux kernel development process: https://docs.kernel.org/process/development-process.html
 - The story of my first Linux Kernel Contribution: https://youtu.be/uLiAc_CnqZE
 - linux kernel mentees: https://wiki.linuxfoundation.org/lkmp/lkmp_mentee_blogs

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

```
git clone git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
```

to download the stable branch:

```
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

```
git format-patch -1 --pretty=fuller XXXXXXXX
```

the code submitted in patches must be signed off:
 - https://www.kernel.org/doc/html/latest/process/submitting-patches.html#sign-your-work-the-developer-s-certificate-of-origin
 - https://www.kernel.org/doc/html/latest/process/submitting-patches.html#using-reported-by-tested-by-reviewed-by-suggested-by-and-fixes
 
and the patch prefixes are:  [PATCH], [PATCH RFC] or [RFC PATCH] or [PATCH v4] 

To create a patch of version 5, you use for example:

```
git format-patch -1 -v5
```

### Portal of Linux Kernel patches

 - reference: https://patchwork.kernel.org/

### To apply a patch:

 - reference: https://www.kernel.org/doc/html/v4.10/process/applying-patches.html <br>

```
patch -p1 < ../patch-x.y.z
```
to remove it: 

```
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


### Sending patches

References: 
 - https://nickdesaulniers.github.io/blog/2017/05/16/submitting-your-first-patch-to-the-linux-kernel-and-responding-to-feedback/
 - https://www.kernel.org/doc/html/v4.17/process/submitting-patches.html
 - https://kernelnewbies.org/PatchPhilosophy
 - https://docs.kernel.org/process/submitting-patches.html


### To send a patch with gmail

References: 
- https://flusp.ime.usp.br/git/sending-patches-by-email-with-git/
- https://mirrors.edge.kernel.org/pub/software/scm/git/docs/git-send-email.html
- https://stackoverflow.com/questions/68238912/how-to-configure-and-use-git-send-email-to-work-with-gmail-to-email-patches-to
- https://gist.github.com/jasonkarns/4354421
- https://support.google.com/accounts/answer/185833?hl=en
- https://stackoverflow.com/questions/68238912/how-to-configure-and-use-git-send-email-to-work-with-gmail-to-email-patches-to/68238913#68238913
- https://gist.github.com/winksaville/dd69a860d0d05298d1945ceff048ce46
- https://git-scm.com/docs/git-send-email#_use_gmail_as_the_smtp_server
- https://www.freedesktop.org/wiki/Software/PulseAudio/HowToUseGitSendEmail/
- https://stackoverflow.com/questions/28038662/how-to-solve-unable-to-initialize-smtp-properly-when-using-using-git-send-ema
- https://morefedora.blogspot.com/2009/02/configuring-git-send-email-to-use-gmail.html
- https://mudongliang.github.io/2018/03/20/setting-up-git-send-email-with-gmail-to-send-linux-kernel-patch.html
- https://mudongliang.github.io/2018/03/20/one-simple-patch-to-linux-kernel.html
- https://medium.com/@akram009.ma/using-git-send-email-with-gmail-7a2c036ee3cb
- https://blog.bisect.de/2012/01/how-to-send-patches-via-git-send-email.html

### Other resources for email workflow and patches

References:
- Kernel mailing list replies for Linux with lore, git and gmail: https://paldan.altervista.org/kernel-mailing-list-replies-for-linux-with-lore-git-and-gmail/?doing_wp_cron=1741727391.2954950332641601562500
- Setting Up Neomutt with Gmail : https://medium.com/@anupnewsmail/setting-up-neomutt-with-gmail-76f24da3601a
- Using lei, b4, and mutt to do kernel development: https://josefbacik.github.io/kernel/2021/10/18/lei-and-b4.html

```
# first configure git:
$ git config --global sendemail.smtpserver smtp.gmail.com
$ git config --global sendemail.smtpserverport 587
$ git config --global sendemail.smtpencryption tls
$ git config --global sendemail.smtpuser your_email@gmail.com

# check with:
$ git config -l
```

```
# the commit must be signed
git commit -s

# generate the patch
git format-patch -1 --base=auto
vim 0001-fix-one-dead-link-in-ia64-xen.txt.patch

# to generate a given version of the patch
git format-patch -1 --base=auto -subject-prefix="PATCH v2"
# or even better as pointed here: https://nickdesaulniers.github.io/blog/2017/05/16/submitting-your-first-patch-to-the-linux-kernel-and-responding-to-feedback/
git format-patch -v2 -1 --base=auto 

# check the patch
./scripts/checkpatch.pl 0001-fix-one-dead-link-in-ia64-xen.txt.patch

# get manteiner list
./scripts/get_maintainer.pl Documentation/ia64/ -f

# send patch check with --dry-run
git send-email  --dry-run --smtp-server /usr/bin/msmtp --to corbet@lwn.net --to yamada.masahiro@socionext.com --to slyfox@gentoo.org --to tony.luck@intel.com --to bjorn.forsman@gmail.com --to mudongliangabcd@gmail.com -cc linux-doc@vger.kernel.org -cc linux-kernel@vger.kernel.org 0001-fix-one-dead-link-in-ia64-xen.txt.patch

# send patch
git send-email  --dry-run --smtp-server /usr/bin/msmtp --to corbet@lwn.net --to yamada.masahiro@socionext.com --to slyfox@gentoo.org --to tony.luck@intel.com --to bjorn.forsman@gmail.com --to mudongliangabcd@gmail.com -cc linux-doc@vger.kernel.org -cc linux-kernel@vger.kernel.org 0001-fix-one-dead-link-in-ia64-xen.txt.patch

git send-email --to xx@mail.com 0001-your.patch
```
```
sergio@laptop:~/repos/my-rust-4-linux$ git format-patch -1
0001-Kunit-to-check-the-longest-symbol-length.patch


sergio@laptop:~/repos/my-rust-4-linux$ ./scripts/checkpatch.pl 0001-Kunit-to-check-the-longest-symbol-length.patch 
Traceback (most recent call last):
  File "/home/sergio/repos/my-rust-4-linux/scripts/spdxcheck.py", line 6, in <module>
    from ply import lex, yacc
ModuleNotFoundError: No module named 'ply'
WARNING: added, moved or deleted file(s), does MAINTAINERS need updating?
#53: 
new file mode 100644

total: 0 errors, 1 warnings, 141 lines checked

NOTE: For some of the reported defects, checkpatch may be able to
      mechanically convert to the typical style using --fix or --fix-inplace.

0001-Kunit-to-check-the-longest-symbol-length.patch has style problems, please review.

NOTE: If any of the errors are false positives, please report
      them to the maintainer, see CHECKPATCH in MAINTAINERS.


sergio@laptop:~/repos/my-rust-4-linux$ ./scripts/get_maintainer.pl lib/kunit
Brendan Higgins <brendan.higgins@linux.dev> (maintainer:KERNEL UNIT TESTING FRAMEWORK (KUnit))
David Gow <davidgow@google.com> (maintainer:KERNEL UNIT TESTING FRAMEWORK (KUnit))
linux-kselftest@vger.kernel.org (open list:KERNEL UNIT TESTING FRAMEWORK (KUnit))
kunit-dev@googlegroups.com (open list:KERNEL 
```

```bash
git send-email \
--dry-run \
--to 'David Gow <davidgow@google.com>' \
--to 'Rae Moar <rmoar@google.com>' \
--to 'linux-kselftest@vger.kernel.org' \
--to 'kunit-dev@googlegroups.com' \
--to 'Miguel Ojeda <ojeda@kernel.org>' \
--to 'Alex Gaynor <alex.gaynor@gmail.com>' \
--cc 'Boqun Feng <boqun.feng@gmail.com>' \
--cc 'Gary Guo <gary@garyguo.net>' \
--cc 'Björn Roy Baron <bjorn3_gh@protonmail.com>' \
--cc 'Benno Lossin <benno.lossin@proton.me>' \
--cc 'Andreas Hindborg <a.hindborg@samsung.com>' \
--cc 'Alice Ryhl <aliceryhl@google.com>' \
--cc 'David Rheinsberg <david@readahead.eu>' \
--cc 'rust-for-linux@vger.kernel.org' \
--cc 'x86@kernel.org' v8-0001-Kunit-to-check-the-longest-symbol-length.patch
```

#### example sending a patch

The patch:
```bash
sergio@laptop:~/repos/orig-linux$ git show
commit 76bcfe1f941af0196e0618426a6b53156e0345e3 (HEAD -> master)
Author: Sergio González Collado <sergio.collado@gmail.com>
Date:   Sun Apr 14 18:40:21 2024 +0200

    Add room for insn-enconding and symbol name
    
    The longest length of a symbol (KSYM_NAME_LEN) was increased to 512
    in the reference [1]. This patch adds room for insn-encoding and a
    symbol name, as proposed in [2]
    
    [1] https://lore.kernel.org/lkml/20220802015052.10452-6-ojeda@kernel.org/
    [2] https://lore.kernel.org/lkml/16641a56-9139-4396-a5a8-89606bedd1f1@app.fastmail.com/
    
    Signed-off-by: Sergio González Collado <sergio.collado@gmail.com>

diff --git a/arch/x86/tools/insn_decoder_test.c b/arch/x86/tools/insn_decoder_test.c
index 472540aeabc2..add51bfc2260 100644
--- a/arch/x86/tools/insn_decoder_test.c
+++ b/arch/x86/tools/insn_decoder_test.c
@@ -10,6 +10,7 @@
 #include <assert.h>
 #include <unistd.h>
 #include <stdarg.h>
+#include <linux/kallsym.h>
 
 #define unlikely(cond) (cond)
 
@@ -106,7 +107,7 @@ static void parse_args(int argc, char **argv)
        }
 }
 
-#define BUFSIZE 256
+#define BUFSIZE (256 + KSYM_NAME_LEN)
 
 int main(int argc, char **argv)
 {
```

format the patch:
```bash
sergio@laptop:~/repos/orig-linux$ git format-patch -1
0001-Add-room-for-insn-enconding-and-symbol-name.patch
```

check the patch:
```bash
sergio@laptop:~/repos/orig-linux$ ./scripts/checkpatch.pl 0001-Add-room-for-insn-enconding-and-symbol-name.patch 
WARNING: Prefer a maximum 75 chars per line (possible unwrapped commit description?)
#15: 
[2] https://lore.kernel.org/lkml/16641a56-9139-4396-a5a8-89606bedd1f1@app.fastmail.com/

total: 0 errors, 1 warnings, 15 lines checked

NOTE: For some of the reported defects, checkpatch may be able to
      mechanically convert to the typical style using --fix or --fix-inplace.

0001-Add-room-for-insn-enconding-and-symbol-name.patch has style problems, please review.

NOTE: If any of the errors are false positives, please report
      them to the maintainer, see CHECKPATCH in MAINTAINERS.
sergio@laptop:~/repos/orig-linux$ 
```
get mantainers:
```bash
sergio@laptop:~/repos/orig-linux$ ./scripts/get_maintainer.pl arch/x86/tools/insn_decoder_test.c
Thomas Gleixner <tglx@linutronix.de> (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT))
Ingo Molnar <mingo@redhat.com> (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT))
Borislav Petkov <bp@alien8.de> (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT))
Dave Hansen <dave.hansen@linux.intel.com> (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT))
x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT))
"H. Peter Anvin" <hpa@zytor.com> (reviewer:X86 ARCHITECTURE (32-BIT AND 64-BIT))
"Sergio González Collado" <X@gmail.com> (commit_signer:1/1=100%,authored:1/1=100%,added_lines:2/2=100%,removed_lines:1/1=100%)
linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND 64-BIT))
sergio@laptop:~/repos/orig-linux$ 
```
test send the patch:
```bash
#not sure what  --smtp-server /usr/bin/msmtp is doing there :/
sergio@laptop:~/repos/orig-linux$ git send-email  --dry-run --smtp-server /usr/bin/msmtp --to 'X@gmail.com' 0001-Add-room-for-insn-enconding-and-symbol-name.patch
0001-Add-room-for-insn-enconding-and-symbol-name.patch
(mbox) Adding cc: =?UTF-8?q?Sergio=20Gonz=C3=A1lez=20Collado?= <X@gmail.com> from line 'From: =?UTF-8?q?Sergio=20Gonz=C3=A1lez=20Collado?= <X@gmail.com>'
(body) Adding cc: Sergio González Collado <X@gmail.com> from line 'Signed-off-by: Sergio González Collado <X@gmail.com>'
Dry-OK. Log says:
Sendmail: /usr/bin/msmtp -i X@gmail.com
From: =?UTF-8?q?Sergio=20Gonz=C3=A1lez=20Collado?= <X@gmail.com>
To: X@gmail.com
Subject: [PATCH] Add room for insn-enconding and symbol name
Date: Sun, 14 Apr 2024 19:05:41 +0200
Message-Id: <20240414170541.10250-1-sergio.collado@gmail.com>
X-Mailer: git-send-email 2.39.2
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit

Result: OK
```

send the patch: 
```bash
sergio@laptop:~/repos/orig-linux$ git send-email --to 'sergio.collado@gmail.com' 0001-Add-room-for-insn-enconding-and-symbol-name.patch
0001-Add-room-for-insn-enconding-and-symbol-name.patch
(mbox) Adding cc: =?UTF-8?q?Sergio=20Gonz=C3=A1lez=20Collado?= <sergio.collado@gmail.com> from line 'From: =?UTF-8?q?Sergio=20Gonz=C3=A1lez=20Collado?= <sergio.collado@gmail.com>'
(body) Adding cc: Sergio González Collado <sergio.collado@gmail.com> from line 'Signed-off-by: Sergio González Collado <sergio.collado@gmail.com>'

From: =?UTF-8?q?Sergio=20Gonz=C3=A1lez=20Collado?= <sergio.collado@gmail.com>
To: sergio.collado@gmail.com
Subject: [PATCH] Add room for insn-enconding and symbol name
Date: Sun, 14 Apr 2024 19:24:04 +0200
Message-Id: <20240414172404.10690-1-sergio.collado@gmail.com>
X-Mailer: git-send-email 2.39.2
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit

    The Cc list above has been expanded by additional
    addresses found in the patch commit message. By default
    send-email prompts before sending whenever this occurs.
    This behavior is controlled by the sendemail.confirm
    configuration setting.

    For additional information, run 'git send-email --help'.
    To retain the current behavior, but squelch this message,
    run 'git config --global sendemail.confirm auto'.

Send this email? ([y]es|[n]o|[e]dit|[q]uit|[a]ll): y
OK. Log says:
Server: smtp.gmail.com
MAIL FROM:<sergio.collado@gmail.com>
RCPT TO:<sergio.collado@gmail.com>
From: =?UTF-8?q?Sergio=20Gonz=C3=A1lez=20Collado?= <sergio.collado@gmail.com>
To: sergio.collado@gmail.com
Subject: [PATCH] Add room for insn-enconding and symbol name
Date: Sun, 14 Apr 2024 19:24:04 +0200
Message-Id: <20240414172404.10690-1-sergio.collado@gmail.com>
X-Mailer: git-send-email 2.39.2
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit

Result: 250 
```

### Backporting

To download the stable version: 
```
git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git
cd linux-stable
```

 References:
  - questions about backporting: https://groups.google.com/g/syzkaller/c/aSvzuUHiDIQ
  - https://www.kernel.org/doc/html/next/process/backporting.html#submitting-backports-to-stable
  - https://www.kernel.org/doc/html/next/process/backporting.html
  - https://www.kernel.org/doc/html/latest/process/stable-kernel-rules.html
  - backporting linux kernel patches: https://www.youtube.com/watch?v=sBR7R1V2FeA

 cherry-pick with -x option - this will inform of the original commit.
 
 After the first line add the message: `[ Upstream commit <xxxx_your_commit_patch> ]
 
 using e.g. `git format-patch --subject-prefix='PATCH 6.1.y' `, 
 
 ```
>> # ALWAYS SIGN-OFF THE COMMITS!!!
 >> git cherry-pick <XXXX>
 >> git commit --amend -s  // to sign the patchf
 >> git format-patch -1 --subject-prefix='PATCH 6.1.y'
 >> ./script/checkpatch.p <patch-name>
 >> # send to: stable@vger.kernel.org 
 ```
### Pach series

reference: https://kernelnewbies.org/PatchSeries

```
# example for a patch backporting serie

# ALWAYS SIGN-OFF THE COMMITS!
sergio@laptop:~/repos/linux-stable$ mkdir patches
sergio@laptop:~/repos/linux-stable$ git format-patch --cover-letter --subject-prefix='PATCH 6.12.y' -2  -o ./patches --base=auto
./patches/0000-cover-letter.patch
./patches/0001-Kunit-to-check-the-longest-symbol-length.patch
./patches/0002-x86-tools-Drop-duplicate-unlikely-definition-in-insn.patch

./scripts/checkpacth patches/*.patch

git send-email \
--dry-run \
--to 'stable@vger.kernel.org' \
--to 'Greg KH <gregkh@linuxfoundation.org>' \
--to 'Sasha Levin <sashal@kernel.org>' \
--cc 'Miguel Ojeda <ojeda@kernel.org>' ./patches/*.patch	
```


 

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


```
sudo apt-get install -y build-essential gcc make vim bc git cscope rsync libncurses-dev libssl-dev bison flex libelf-dev
sudo apt-get install git-email
```

It is needed to check the minimal requirements to compile the kernel

```
https://www.kernel.org/doc/html/latest/process/changes.html
```

git-email is for sending patches through the **sendmail** configuration option once the **smtp** server is configured.

example configuration for gmail: https://gist.github.com/jasonkarns/4354421, https://coderwall.com/p/qcsiew/setting-up-and-using-git-send-email-with-gmail

https://www.kernel.org/doc/html/latest/process/email-clients.html


### Exploring the linux kernel sources

You should create a directory, to git clone the linux repo, for example the mainline: https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/ 

```
>> cd /linux_work
>> git clone git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git linux_mainline
>> cd linux_mainline; ls -h

arch          CREDITS                 drivers  ipc      lib          mm       scripts   usr
block    crypto         fs               Kbuild      LICENSES     net      security  virt
certs        cscope.out          include    Kconfig  MAINTAINERS  README      sound
COPYING    Documentation  init     kernel       Makefile          samples  tools
```

or to clone the stable branche:

```
git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git linux_stable
```

You can use `cregit-linux` tool, to explore the code: https://cregit.linuxsources.org/ <br>

for example: https://cregit.linuxsources.org/code/5.11/  <br>

The most part of the linux kernel, is in the 'drivers' subdirectory.

In 'arch' we can see all the supported architectures: https://cregit.linuxsources.org/code/5.11/arch/

You can also use 'git log' to explore the different commmits. 

```
git format-patch -1 <commit ID>
```

For everyday tinkering with the kernel, take into account the scripts: scripts/get_maintainer.pl and scripts/checkpatch.pl

Also check the linux-kselftest repo

### Generate documentation

- reference: https://subscription.packtpub.com/book/cloud-and-networking/9781789953435/2/ch02lvl1sec21/generating-the-kernel-documentation-from-source

In the source root, execute: 

```
$ make pdfdocs
```
or

```
$ make htmldocs
```

to analyze the documentation maybe use: 
```
$ make htmldocs > doc.log 2>&1
$ make pdfdocs > doc.log 2>&1
```

Find the generated files at: `Documentation/output/latex`.


### Writing a kernel patch

$(uname -r) displays the running Kernel version .

 Clone the stable kernel tree
 
```
git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git linux_stable
cd linux_stable
git branch -a | grep linux-5
    remotes/origin/linux-5.0.y
    remotes/origin/linux-5.1.y
    remotes/origin/linux-5.2.y
git checkout linux-5.2.y
 ```
 
 Next you have to copy the configuration file from your current kernel, from /proc/config.gz or /boot, and copy it to  linux_stable/.config
 
 for example:
 
 ```
 ls /boot
config-5.0.0-20-generic        memtest86+.bin
config-5.0.0-21-generic        memtest86+.elf  //< this is the latest configuration
efi                            memtest86+_multiboot.bin
grub                           System.map-5.0.0-20-generic
initrd.img-5.0.0-20-generic    System.map-5.0.0-21-generic
initrd.img-5.0.0-21-generic    vmlinuz-5.0.0-20-generic
lost+found                     vmlinuz-5.0.0-21-generic
```

The easy thing to do, is to copy your actual config file (in /boot/) and move it to where the linux source is, and name it as .config.

```
cp /boot/<config-5.0.0-21-generic> .config
```
To submint a patch: https://www.kernel.org/doc/html/v6.0/process/submitting-patches.html#using-reported-by-tested-by-reviewed-by-suggested-by-and-fixes

#### The kernel build system

Reference: 
 - https://www.linuxjournal.com/content/kbuild-linux-kernel-build-system 
 - https://www.kernel.org/doc/html/latest/kbuild/index.html

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

```
make oldconfig
```

'make oldconfig' reads the existing .config file that was used for an old kernel and prompts the user for options in the current kernel source that are not found in the file. This is useful when taking an existing configuration and moving it to a new kernel.

WATCH OUT!: New releases often introduce new configuration variables and, in some cases, rename the configuration symbols. The latter causes problems, and make oldconfig might not generate a new working kernel. Run make listnewconfig after copying the configuration from /boot to the .config file, to see a list of new configuration symbols. 

 - reference: https://stackoverflow.com/questions/4178526/what-does-make-oldconfig-do-exactly-in-the-linux-kernel-makefile
 - reference: https://www.kernel.org/doc/html/latest/kbuild/kconfig.html

**Bonuses** make olddefconfig sets every option to their default value without asking interactively. It gets run automatically on make to ensure that the .config is consistent in case you've modified it manually.

Other way to tune the kernel your system is by using **make localmodconfig**. This option creates a configuration file based on the list of modules currently loaded on your system.

```
lsmod > /tmp/my-lsmod
make LSMOD=/tmp/my-lsmod localmodconfig
```

A simpler choice is use **make defconfig**, every kernel has a default configuration, so with the 'defconfig' option that default configuration is used.


otherwise use: 

```
make menuconfig
```

or 

```
make xconfig
```

you can get help:

```
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

Note: the tinyoconfig, think is related to: http://www.tinycorelinux.net/


Once this step is complete, it is time to compile the kernel. Using the '-j' option helps the compiles go faster. The '-j' option specifies the number of jobs (make commands) to run simultaneously:

```
make -j3 all
```

or to use all processors

```
make -j$(nproc)
```

the end of compilation should be like ...

```
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


```
make modules
```

Once the compilation is done, you can install it

```
su -c "make modules_install install"
```

Then install the kernel (in case you want to update/test the kernel)

```
make install 
```

reference: https://www.cyberciti.biz/tips/compiling-linux-kernel-26.html

This command will install the kernel, and execute 'update-grub' to add it to the grub menu: 

```
update-grub
```

Summing up the steps to compile and install the kernel:

```
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

```
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

```
mokutil --sb-state
```

https://askubuntu.com/questions/1119734/how-to-replace-or-remove-kernel-with-signed-kernels

to disable validation:

```
sudo mokutil --disable-validation
root password
mok password: 1234567
mok password: 1234567
sudo reboot
```
to re-enable validation:

```
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

```
sudo update-grub
```

```
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

### Submitting patches

https://www.kernel.org/doc/html/latest/process/submitting-patches.html

https://kernelnewbies.org/FirstKernelPatch


All the commits need to be signed-off:   

Create a .gitconfig file in your home directory.
- Name is the full legal author name 
- email is the email address for the commit 
- signoff = true 

reference: https://www.kernel.org/doc/html/latest/process/submitting-patches.html

```
git commit -s
```

To accept a patch, the name, and signed-off-by must match. 

https://www.kernel.org/doc/html/latest/process/submitting-patches.html <br>
https://www.kernel.org/doc/html/latest/process/kernel-enforcement-statement.html <br>

Kernel Configuration

The Linux kernel is completely configurable. Drivers can be configured to be installed and completely disabled. Here are three options for driver installation:

- Disabled
- Built into the kernel (vmlinux image) to be loaded at boot time (avoid for long booting times!)
- Built as a module to be loaded as needed using modprobe.

It is a good idea to configure drivers as modules, to avoid large kernel images. Modules (.ko files) can be loaded when the kernel detects hardware that matches the driver. Building drivers as modules allows them to be loaded on demand, instead of keeping them around in the kernel image even when the hardware is either not being used, or not even present on the system.

A good option is generating the new configuration with the old configuration as the starting point. New releases often introduce new configuration variables and, in some cases, rename the configuration symbols. The latter causes problems, and make oldconfig might not generate a new working kernel.

https://www.kernel.org/doc/html/latest/kbuild/kconfig.html

Run 'make listnewconfig' after copying the configuration from '/boot' to the .config file, to see a list of new configuration symbols. Kconfig make config is a good source about Kconfig and make config ( https://www.kernel.org/doc/html/latest/kbuild/kconfig.html ) . Please refer to the Kernel Build System to understand the kernel build framework and the kernel makefiles.

https://www.kernel.org/doc/html/latest/kbuild/kconfig.html

https://www.kernel.org/doc/html/latest/kbuild/index.html

previously to any change create a new branch from the linux_mainline repository you cloned earlier to write your first patch. We will start by adding a remote first to do a rebase (pick up new changes made to the mainline).

```
cd linux_mainline
git branch -a
* master
  remotes/linux/master
  remotes/origin?HEAD -> origin/master
  remotes/origin/master
```

Then  add git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git as the remote named linux. Adding a remote helps us fetch changes and choose a tag to rebase from.

We can pick a tag to rebase to. In this case, there is only one new tag. Let’s hold off on the rebase and start writing a new patch

To check out a branch do:

```
git checkout -b work
master
* work
  remotes/linux/master
  remotes/origin/HEAD -> origin/master
```

Now you can make a change, to a driver, for example. You can list the modules with **lsmod**. You can find the .c and .h files for that driver in the linux kernel repository. 
Or even searching through the Makefiles, or even with 'git grep' 

For example with the uvcvideo driver is a USB Video Class (UVC) media driver for video input devices, such as webcams. It supports webcams on laptops. Let’s check the source files for this driver.

You can look for it with:

```
git grep uvcvideo -- '*Makefile'
drivers/media/usb/uvc/Makefile:uvcvideo-objs := uvc_driver.o uvc_queue.o uvc_v4l2.o uvc_video.o uvc_ctrl.o drivers/media/usb/uvc/Makefile:uvcvideo-objs += uvc_entity.o
drivers/media/usb/uvc/Makefile:obj-$(CONFIG_USB_VIDEO_CLASS) += uvcvideo.o
```

Kernel code style: https://www.kernel.org/doc/html/latest/process/coding-style.html

 - https://events.linuxfoundation.org/mentorship-session-kernel-validation-with-kselftest/

KERNEL TESTS 

- The kernel CI: https://kernelci.org/
- issues: https://lists.01.org/hyperkitty/
- linaro QA: https://qa-reports.linaro.org/lkft/
- buildBot: https://kerneltests.org/

APPLYING PATCHES:

 Each Linux patch is a self-contained change to the code that stands on its own, unless explicitly made part of a patch series. New patches are applied as follows:

```
patch -p1 < file.patch
git apply --index file.patch
```

Either command will work; however, when a patch adds a new file and, if it is applied using the patch command, git does not know about the new files, and they will be treated as untracked files. The git diff command will not show the files in its output and the git status command will show the files as untracked. You can use git diff HEAD to see the changes.

For the most part, there are no issues with building and installing kernels; however, the git reset --hard command will not remove the newly created files and a subsequent git pull will fail.

SOLUTION1 
When a patch that adds new files is applied using the patch command, run git clean to remove untracked files before running git reset --hard. For example, git clean -dfx will force the removal of untracked directories and files, ignoring any standard ignore rules specified in the .gitignore file. You could include the -q option to run git clean in quiet mode, if you do not care to know which files are removed.​

SOLUTION2
An alternate approach is to tell git to track the newly added files by running git apply --index file.patch. This will result in git applying the patch and adding the result to the index. Once this is done, git diff will show the newly added files in its output and git status will report the status correctly, tagging these files as newly created files.

CHECK KERNEL LOGS

```
dmesg -t -l emerg
dmesg -t -l crit
dmesg -t -l alert
dmesg -t -l err
dmesg -t -l warn
dmesg -t -k
dmesg -t
```

STRESS TEST,

 lauch several kernel compilations in parallel ... :/
 
 ```
 time make all
 ```
 
DEBUGING KERNEL PANICS 

https://sanjeev1sharma.wordpress.com/tag/debug-kernel-panics/
https://www.opensourceforu.com/2011/01/understanding-a-kernel-oops/

Decode and Analyze the Panic Message
Panic messages can be decoded using the decode_stacktrace.sh tool. Please refer to decode_stacktrace https://lwn.net/Articles/592724/ : make stack dump output useful again for details on how to use the tool.

https://www.kernel.org/doc/html/latest/trace/events.html



HOW TO BUILD THE KERNEL DOCUMENTATION

There is a script which checks if you have all the needed dependencies to build the documentation. This script is called automatically when you run

make htmldocs

Alternatively, you can call the script directly by running:

./scripts/sphinx-pre-install

Once you have all the requirements, you can do the building by running:

make htmldocs > doc_make.log 2>&1

Check for warnings and other errors you might find and see if you can fix them.



TODO: 
- Kernel-bypass techniques for high-speed network packet processing : https://youtu.be/MpjlWt7fvrw
- Kernel-bypass networking for fun and profit : https://youtu.be/noqSZorzooc
- Data plane development kit DPDK: DPDK deep-dive : https://youtu.be/VJ8CVN3oXMw
- Linux Networking - eBPF, XDP, DPDK, VPP - What does all that mean? (by Andree Toonk) : https://youtu.be/hO2tlxURXJ0
- Linux packet journey,napi, hardware queue,skb : https://youtu.be/6Fl1rsxk4JQ
- Introduction to Memory Management in Linux :  https://youtu.be/7aONIVSXiJ8
- Steven Rostedt - Learning the Linux Kernel with tracing : https://youtu.be/JRyrhsx-L5Y
- Design Microservice Architectures the Right Way: https://youtu.be/j6ow-UemzBc
- Mastering Chaos - A Netflix Guide to Microservices : https://youtu.be/CZ3wIuvmHeM
- tcddump: https://www.youtube.com/watch?v=hWc-ddF5g1I
- Device trees for dummies! https://www.youtube.com/watch?v=m_NyYEBxfn8
- Different I/O access methods for linux: https://www.youtube.com/watch?v=27Xz21RJoUA

TODO: Linux security implementations - TPM, FDE, LUKS, HSM, etc.

tpm : https://en.wikipedia.org/wiki/Trusted_Platform_Module && https://www.kernel.org/doc/html/latest/security/tpm/index.html

UEFI Secure Boot: https://wiki.debian.org/SecureBoot










## Linux networking basics

### Switches
 to connect two computers a switch is needed. (A switch can only serve communication within a network)
 
 To see the interfaces, 
 
```
ip link
```

**ip link** is to display and modify interfaces n a linux host.

if the switch has for example the ip: 192.168.1.0. and the computers (A and B)to communicate have the ips. 192.168.1.10 (A)  and 192.168.1.11 (B) 

we add both ip computers with:

**ip addr** is to display the ips of the interfaces, adn **ip addr add** to add ip addresses to the network interfaces.

```
ip addr add 192.168.1.10/24 dev eth0
```

```
ip addr add 192.168.1.11/24 dev eth0
```

### Routing

For connceting different networks a router in needed. Like the router connects with two networks it has two ip addresses assinged, one in each network.

Imaging another network wit a switch (192.168.2.0) and two computers C (192.168.2.10) and D(192.168.2.11). How can system A communicate with C?

In the first network the router has the ip: 192.168.1.1 and in the second network it is identified with the ip: 192.168.2.1

So to communicate between the networks the **gateway** must be defined:

To display the existing routing configuration in a system, use the **route** command

```
route
```

This will display the kernel's routing table.

The **route** or **ip route** command display the routing table

To configure a gateway, so a computer can reach another computer in another network, use the command: **ip route add**

```
ip route add 192.168.2.0/24 via 192.168.1.1
```
- 192.168.1.1 would be the address of the router
- 192.168.2.0/24 would be the range of addresses requested to be accessed through the router

Other example, one of the computers, need to reach an address in the internet (172.217.194.0), you ask to route to that address through the router

```
ip route add 172.217.194.0/24 via 192.168.1.1
```

For not having to define all the ips, outside the own networ, a default policy can be defined:

```
ip route add default via 192.168.2.1
```

or intead of default, it can be defined also as 0.0.0.0, this means any destination


### How to set a linux host a router (fordwarding packets in a linux host)

By default in linux, packets are not forwarded from one interface to the next. 

Wether a host can fordward packets between interfaces is defined in a setting in the system, at the file:

```
/proc/sys/net/ipv4/ip_fordward
```

by default, the value in this file, is set to 0, that states for **not fordward**. 

if you set this value to one, the system will allow fordwarding packets from one interface to other.

```
echo 1 > /proc/sys/net/ipv4/ip_fordward
```

Only setting this value, will not persist in case the system is rebooted, or turned off. For that you must modify this value in:

```
in the file: /etc/sysctl.conf
net.ipv4.ip_fordward = 1
```


# System calls

references:
 - https://man7.org/linux/man-pages/man2/intro.2.html
 - https://man7.org/linux/man-pages/man2/syscalls.2.html
 - https://man7.org/linux/man-pages/man2/syscall.2.html
 - https://lwn.net/Articles/604287/
 - https://lwn.net/Articles/604515/
 - https://medium.com/@ssreehari/implementing-a-system-call-in-linux-kernel-4-7-1-6f98250a8c38

The kernel provides user-space a series of interfaces to interact whit the system, its hardware and underlying systems. 
Those interfaces for example requests dynamic memory allocations, read or write files ... This interface provides and
abstraction layer  to the user-space, so it can request read or write files, but doesn't need to handle 
the possible diffent file systems. Also this interface guards the systems, so the kernel can handle permissions, or 
make sure that a user-space process doesn't overlay with other user-space process. 


## visualizing syscalls with strace

With the strace application it is possible to get the system calls of an application for example

```
strace ls mytext.txt
```

```
sergio@debian:~$ strace ls mytext.txt
execve("/usr/bin/ls", ["ls", "mytext.txt"], 0x7ffd50072ff8 /* 47 vars */) = 0
brk(NULL)                               = 0x5585d8765000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=96140, ...}) = 0
mmap(NULL, 96140, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fe69b9f8000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libselinux.so.1", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0@k\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=155296, ...}) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fe69b9f6000
mmap(NULL, 2259632, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fe69b7ce000
mprotect(0x7fe69b7f3000, 2093056, PROT_NONE) = 0
mmap(0x7fe69b9f2000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x24000) = 0x7fe69b9f2000
...
mprotect(0x7fe69ba37000, 4096, PROT_READ) = 0
munmap(0x7fe69b9f8000, 96140)           = 0
set_tid_address(0x7fe69b572650)         = 19158
set_robust_list(0x7fe69b572660, 24)     = 0
rt_sigaction(SIGRTMIN, {sa_handler=0x7fe69b5796b0, sa_mask=[], sa_flags=SA_RESTORER|SA_SIGINFO, sa_restorer=0x7fe69b585730}, NULL, 8) = 0
rt_sigaction(SIGRT_1, {sa_handler=0x7fe69b579740, sa_mask=[], sa_flags=SA_RESTORER|SA_RESTART|SA_SIGINFO, sa_restorer=0x7fe69b585730}, NULL, 8) = 0
rt_sigprocmask(SIG_UNBLOCK, [RTMIN RT_1], NULL, 8) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
statfs("/sys/fs/selinux", 0x7ffef371fe30) = -1 ENOENT (No such file or directory)
statfs("/selinux", 0x7ffef371fe30)      = -1 ENOENT (No such file or directory)
brk(NULL)                               = 0x5585d8765000
brk(0x5585d8786000)                     = 0x5585d8786000
openat(AT_FDCWD, "/proc/filesystems", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0444, st_size=0, ...}) = 0
...
lstat("mytext.txt", 0x5585d8766b68)     = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/share/locale/locale.alias", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=2995, ...}) = 0
...
openat(AT_FDCWD, "/usr/share/locale/en/LC_MESSAGES/libc.mo", O_RDONLY) = -1 ENOENT (No such file or directory)
write(2, ": No such file or directory", 27: No such file or directory) = 27
write(2, "\n", 1
)                       = 1
close(1)                                = 0
close(2)                                = 0
exit_group(2)                           = ?
+++ exited with 2 +++

```

if we check the first call:

```
execve("/usr/bin/ls", ["ls", "mytext.txt"], 0x7ffd50072ff8 /* 47 vars */) = 0
```

It is 'execve' the call to invoque a program. Then it is the binary to execute "/usr/bin/ls",
then the parameters passed to 'main()', arg0, is the name of the program "ls", then the 
first parameter, the file: "mytext.txt", and then a pointer to the enviroment variables "/* 47 vars*/".


## Syscall numbers.

Each syscall is assigned and identified with an unique number. When user-space call a syscall, it doens't invoque it by name. 
Once this number is assined to a given syscall, this cannot be changed, because already compiled applications would break. 
it exits a not implemented syscall: 'sys_ni_syscall()', that does nothing but return -ENOSYS error. The kernel keeps a list of regitered
syscalls at 'sys_call_table'. It is architecture dependand, and usually defiend in entry.S.

As noted in syscalls(2): https://man7.org/linux/man-pages/man2/syscalls.2.html

Roughly speaking, the code belonging to the system call with number __NR_xxx defined in /usr/include/asm/unistd.h can be found in the Linux kernel source in the routine sys_xxx().

For example to an x86 abd x86_64 arch: 

 - https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/arch/x86/entry/syscall_32.c?h=v5.4.144 <br>
 - https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/arch/x86/entry/syscall_64.c?h=v5.4.144 <br> 

This file contains the system call numbers, based on the layout of the x86-64 architecture:  

 - https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/include/uapi/asm-generic/unistd.h?h=v5.4.144

root/include/linux/syscalls.h - Linux syscall interfaces (non-arch-specific): 

 - https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/include/linux/syscalls.h?h=v5.4.144

32-bit system call numbers and entry vectors: 

https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/arch/x86/entry/syscalls/syscall_32.tbl?h=v5.4.144

entry_32.S contains the system-call and low-level fault and trap handling routines : 

https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/arch/x86/entry/entry_32.S?h=v5.4.144

## Syscall handler

The code in user-space cannot call a system call directly, due it is in kernel-space and it is in a protected memory space. 
So, the user-space applications must signal the kernel to execute a system call and have to somehow switch to kernel mode. 
This is done by means to signal the kernel with a software interrupt. Call an exception and then, the
system will switch to kernel-mode and execute the exception handler. That exception handler will be the system call handler __**system_call()**__
which is an architectural dependand call. 

The system has to identify the system call number desired to be called. On x86, this is passed by puting the system call number in the __eax__ register. 
Other architectures do something similar. This number is checked comparing tis value to NR_syscals to verify it is smaller, if it is not it returns, -ENOSYS. 
If the verification is ok, then it is called: 

```
call *sys_call_table(, %eax, 4)
```

Not only the syscall number must be passed, but also the parameters needed for the syscall. Usually those are passed also in the other 
registers.


## Syscalls files overview

entry_32.S contains the system-call and low-level fault and trap handling routines : https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/arch/x86/entry/entry_32.S?h=v5.4.144

```
 SPDX-License-Identifier: GPL-2.0 */
/*
 *  Copyright (C) 1991,1992  Linus Torvalds
 *
 * entry_32.S contains the system-call and low-level fault and trap handling routines.
 *
 * Stack layout while running C code:
 *	ptrace needs to have all registers on the stack.
 *	If the order here is changed, it needs to be
 *	updated in fork.c:copy_process(), signal.c:do_signal(),
 *	ptrace.c and ptrace.h
 *
 *	 0(%esp) - %ebx
 *	 4(%esp) - %ecx
 *	 8(%esp) - %edx
 *	 C(%esp) - %esi
 *	10(%esp) - %edi
 *	14(%esp) - %ebp
 *	18(%esp) - %eax
 *	1C(%esp) - %ds
 *	20(%esp) - %es
 *	24(%esp) - %fs
 *	28(%esp) - %gs		saved iff !CONFIG_X86_32_LAZY_GS
 *	2C(%esp) - orig_eax
 *	30(%esp) - %eip
 *	34(%esp) - %cs
 *	38(%esp) - %eflags
 *	3C(%esp) - %oldesp
 *	40(%esp) - %oldss
 */

```


32-bit system call numbers and entry vectors: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/arch/x86/entry/syscalls/syscall_32.tbl?h=v5.4.144

```
#
# 32-bit system call numbers and entry vectors
#
# The format is:
# <number> <abi> <name> <entry point> <compat entry point>
#
# The __ia32_sys and __ia32_compat_sys stubs are created on-the-fly for
# sys_*() system calls and compat_sys_*() compat system calls if
# IA32_EMULATION is defined, and expect struct pt_regs *regs as their only
# parameter.
#
# The abi is always "i386" for this file.
#
0	i386	restart_syscall		sys_restart_syscall		__ia32_sys_restart_syscall
1	i386	exit			sys_exit			__ia32_sys_exit
2	i386	fork			sys_fork			__ia32_sys_fork
3	i386	read			sys_read			__ia32_sys_read
4	i386	write			sys_write			__ia32_sys_write
5	i386	open			sys_open			__ia32_compat_sys_open
6	i386	close			sys_close			__ia32_sys_close
7	i386	waitpid			sys_waitpid			__ia32_sys_waitpid
8	i386	creat			sys_creat			__ia32_sys_creat
9	i386	link			sys_link			__ia32_sys_link
10	i386	unlink			sys_unlink			__ia32_sys_unlink
11	i386	execve			sys_execve			__ia32_compat_sys_execve
12	i386	chdir			sys_chdir			__ia32_sys_chdir
13	i386	time			sys_time32			__ia32_sys_time32
14	i386	mknod			sys_mknod			__ia32_sys_mknod
15	i386	chmod			sys_chmod			__ia32_sys_chmod
16	i386	lchown			sys_lchown16			__ia32_sys_lchown16
...
432	i386	fsmount			sys_fsmount			__ia32_sys_fsmount
433	i386	fspick			sys_fspick			__ia32_sys_fspick
434	i386	pidfd_open		sys_pidfd_open			__ia32_sys_pidfd_open
435	i386	clone3			sys_clone3			__ia32_sys_clone3
```

https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/include/uapi/asm-generic/unistd.h?h=v5.4.144

```
/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#include <asm/bitsperlong.h>

/*
 * This file contains the system call numbers, based on the
 * layout of the x86-64 architecture, which embeds the
 * pointer to the syscall in the table.
 *
 * As a basic principle, no duplication of functionality
 * should be added, e.g. we don't use lseek when llseek
 * is present. New architectures should use this file
 * and implement the less feature-full calls in user space.
 */

#ifndef __SYSCALL
#define __SYSCALL(x, y)
#endif

#if __BITS_PER_LONG == 32 || defined(__SYSCALL_COMPAT)
#define __SC_3264(_nr, _32, _64) __SYSCALL(_nr, _32)
#else
#define __SC_3264(_nr, _32, _64) __SYSCALL(_nr, _64)
#endif

#ifdef __SYSCALL_COMPAT
#define __SC_COMP(_nr, _sys, _comp) __SYSCALL(_nr, _comp)
#define __SC_COMP_3264(_nr, _32, _64, _comp) __SYSCALL(_nr, _comp)
#else
#define __SC_COMP(_nr, _sys, _comp) __SYSCALL(_nr, _sys)
#define __SC_COMP_3264(_nr, _32, _64, _comp) __SC_3264(_nr, _32, _64)
#endif

#define __NR_io_setup 0
__SC_COMP(__NR_io_setup, sys_io_setup, compat_sys_io_setup)
#define __NR_io_destroy 1
__SYSCALL(__NR_io_destroy, sys_io_destroy)
#define __NR_io_submit 2
__SC_COMP(__NR_io_submit, sys_io_submit, compat_sys_io_submit)
#define __NR_io_cancel 3
__SYSCALL(__NR_io_cancel, sys_io_cancel)
#if defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#define __NR_io_getevents 4
__SC_3264(__NR_io_getevents, sys_io_getevents_time32, sys_io_getevents)
#endif

/* fs/xattr.c */
#define __NR_setxattr 5
__SYSCALL(__NR_setxattr, sys_setxattr)
#define __NR_lsetxattr 6
__SYSCALL(__NR_lsetxattr, sys_lsetxattr)
#define __NR_fsetxattr 7
__SYSCALL(__NR_fsetxattr, sys_fsetxattr)
#define __NR_getxattr 8
__SYSCALL(__NR_getxattr, sys_getxattr)
#define __NR_lgetxattr 9
__SYSCALL(__NR_lgetxattr, sys_lgetxattr)
#define __NR_fgetxattr 10
__SYSCALL(__NR_fgetxattr, sys_fgetxattr)
#define __NR_listxattr 11
__SYSCALL(__NR_listxattr, sys_listxattr)
#define __NR_llistxattr 12
__SYSCALL(__NR_llistxattr, sys_llistxattr)
#define __NR_flistxattr 13
__SYSCALL(__NR_flistxattr, sys_flistxattr)
#define __NR_removexattr 14
__SYSCALL(__NR_removexattr, sys_removexattr)
#define __NR_lremovexattr 15
__SYSCALL(__NR_lremovexattr, sys_lremovexattr)
#define __NR_fremovexattr 16
__SYSCALL(__NR_fremovexattr, sys_fremovexattr)

/* fs/dcache.c */
#define __NR_getcwd 17
__SYSCALL(__NR_getcwd, sys_getcwd)
```

https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/include/linux/syscalls.h?h=v5.4.144

```
/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * syscalls.h - Linux syscall interfaces (non-arch-specific)
 *
 * Copyright (c) 2004 Randy Dunlap
 * Copyright (c) 2004 Open Source Development Labs
 */

#ifndef _LINUX_SYSCALLS_H
#define _LINUX_SYSCALLS_H

...

*
 * These syscall function prototypes are kept in the same order as
 * include/uapi/asm-generic/unistd.h. Architecture specific entries go below,
 * followed by deprecated or obsolete system calls.
 *
 * Please note that these prototypes here are only provided for information
 * purposes, for static analysis, and for linking from the syscall table.
 * These functions should not be called elsewhere from kernel code.
 *
 * As the syscall calling convention may be different from the default
 * for architectures overriding the syscall calling convention, do not
 * include the prototypes if CONFIG_ARCH_HAS_SYSCALL_WRAPPER is enabled.
 */
#ifndef CONFIG_ARCH_HAS_SYSCALL_WRAPPER
asmlinkage long sys_io_setup(unsigned nr_reqs, aio_context_t __user *ctx);
asmlinkage long sys_io_destroy(aio_context_t ctx);
asmlinkage long sys_io_submit(aio_context_t, long,
			struct iocb __user * __user *);
asmlinkage long sys_io_cancel(aio_context_t ctx_id, struct iocb __user *iocb,
			      struct io_event __user *result);
asmlinkage long sys_io_getevents(aio_context_t ctx_id,
				long min_nr,
				long nr,
				struct io_event __user *events,
				struct __kernel_timespec __user *timeout);
asmlinkage long sys_io_getevents_time32(__u32 ctx_id,
				__s32 min_nr,
				__s32 nr,
				struct io_event __user *events,
				struct old_timespec32 __user *timeout);
asmlinkage long sys_io_pgetevents(aio_context_t ctx_id,
				long min_nr,
				long nr,
				struct io_event __user *events,
				struct __kernel_timespec __user *timeout,
				const struct __aio_sigset *sig);

```

# Interrupts and interrupt handlers. 

reference: https://www.kernel.org/doc/html/latest/core-api/irq/index.html<br>
reference: https://linux.die.net/lkmpg/x1256.html <br>


An IRQ is an **interrupt request** from a device. Currently they can come in over a pin, or over a packet. Several devices may be connected to the same pin thus sharing an IRQ.

An **IRQ number** is a kernel identifier used to talk about a hardware interrupt source. Typically this is an index into the global irq_desc array, but except for what linux/interrupt.h implements the details are architecture specific.

Interrups allow the hardware to signal events and communicate to the kernel. The hardware will generate interrupts asynchronously to the processos's clock.
The **interrupt controller** will signal interrupts to the processor, and the kernel will be notified to handle that interrupt. Diferent devices generate different
interrupts, so each interrupt can be addressed accordinly with a unique handler. Those interrupt values are called interrupt requests (IRQ) 

Note!: similar to **interrupts** are the **exceptions**, that occour synchronoulsy with the processor's clock. Sometimes they are called synchronous interrupts. Those exceptions happen when the processor executes a wrong instruction, like dividing by zero. Those exceptions are handled very much like interrupts in many architectures. 

For a given interrupt, the kernel responds with the corresponding interrupt handler or interrupt service routine (ISR). Interrupt handlers are normal C functions, that are invoked by the kernel, in response to interrupts. An interrupt is importat that is fast, so it doesn't halt the system. The minimum that the interupt handler has to do is to acknoledge the interrupt has been receibed. 

To be as fast as possible, the processing of interrupts is split in two parts: the **top half** and the **bottom half**. The top half is executed immediately upon receiving the interrupt and performs the most critical work, and the rest is delayed and handled in the bottom half. The bottom half will run later. 

As interrupts are desired to be as fast as possible, the top half of the interrupt, has to be as brief as possible. 

reference: IRQs: the Hard, the Soft, the Threaded and the Preemptible - https://youtu.be/-pehAzaP1eg <br>
reference: Understanding Linux Interrupt Subsystem - https://youtu.be/LOCsN3V1ECE?list=RDCMUCfX55Sx5hEFjoC3cNs6mCUQ <br>
reference: https://linux.die.net/lkmpg/x1256.html <br>
reference: https://www.kernel.org/doc/html/latest/core-api/irq/index.html<br>
reference: https://www.kernel.org/doc/html/latest/core-api/genericirq.html <br>

## Interrupt types

There are different types of interrupts accordging to its classification

**Hardware interrutps**, caused by external devices, timers, network cards, or the keyboard are examples of hardware interrupts
 
**Software interrupts**, caused by special instructions, like page-faults, overflows, or division by zero. 
 
**Maskable interrutps** - can be ingnored. Those can be delayed.

**Non maskable interrupts** - cannot be ignored. This could be a critical event, like hardware failure.

**Shared interrupts**, different hardware, can share interrupts among some devices.

**Sporius interrupts**, these are interrupts of very short duration, those are considered as glitches (sporius.c) 

**GIC specific interrutps**, ARM Generic Interrupt Controller. PPI, SPI, SGI.
 - PPI : Private Peripheral Interrupt. Interrupts private to one core, and cannot be executed in other core. 
 - SPI : Shared Peripheral Interrupts. Interrupts that can be shared between cores.
 - SGI : Used for interprocess communication. 

## /proc/interrupts

The procfs filesystem is a virtual filesystem that is used to provide information and has information related to te interrupts of the system.

To see the interrupts occurring on your system, run the command:
```
> watch -n1 "cat /proc/interrupts"

           CPU0       CPU1
 0:         330          0   IO-APIC-edge      timer
 1:       11336          0   IO-APIC-edge      i8042
 4:           2          0   IO-APIC-edge
 6:           3          0   IO-APIC-edge      floppy
 ...
NMI:          0          0   Non-maskable interrupts
LOC:    5806923    6239132   Local timer interrupts
 ...
 ```
 
The watch command executes another command periodically, in this case "cat /proc/interrups". The -n1 option tells watch to execute the command every second.

Teh funcion that displays that information is **show_interrupts()**, and is architecture dependant. 

reference: https://www.linuxjournal.com/content/watch-live-interrupts#:~:text=To%20see%20the%20interrupts%20occurring,6239132%20Local%20timer%20interrupts%20...

## important data stuctures

 - struct irq_domain - https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/include/linux/irqdomain.h?h=v5.4.144#n134
 - struct irq_desc - the interrupt description structure for a given irq
 - struct irq_chip - https://www.kernel.org/doc/html/latest/core-api/genericirq.html#c.irq_chip
 - struct irq_data - https://www.kernel.org/doc/html/latest/core-api/genericirq.html#c.irq_data

This structures are connected one with each other:

```
irq_domain -> irq_desc -> irq_data -> irq_domain && irq_chip
```

### irq_domain
 
This structure is used for hardware interrupt number translation. The interrupt number for a particular device given in a device tree
is the iq_number, and the interrupt's controller local interrupt number is called hardware iq number. When there is only
a single interrupt controller in the system, the same irq_number that is from the device tree can be used as controller local 
irq number that is hardware iq, butin the system with multiple controllers the kernel must ensure that each one gets 
assigned non-overlapping allocations of iq_number, for that reason is neede a mechanism to separate controller local 
interrupt number from the linux iq_number. The controller local number is alerted using irq_domain operations. 

irq_domain -> https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/include/linux/irqdomain.h?h=v5.4.144#n134

```
struct irq_domain {                            // struct irq_domain - Hardware interrupt number translation object
	struct list_head link;                 // Element in global irq_domain list.
	const char *name;                      // Name of interrupt domain
	const struct irq_domain_ops *ops;      // Pointer to irq_domain methods
	void *host_data;                       // private data pointer for use by owner. Not touched by irq_domain core code.
	unsigned int flags;                    // host per irq_domain flags
	unsigned int mapcount;                 //

	/* Optional data */
	struct fwnode_handle *fwnode;          // Pointer to firmware node associated with the irq_domain.
	enum irq_domain_bus_token bus_token;  
	struct irq_domain_chip_generic *gc;    // Pointer to a list of generic chips.
#ifdef	CONFIG_IRQ_DOMAIN_HIERARCHY
	struct irq_domain *parent;             // Pointer to parent irq_domain to support hierarchy irq_domains
#endif
#ifdef CONFIG_GENERIC_IRQ_DEBUGFS
	struct dentry		*debugfs_file;
#endif

	/* reverse map data. The linear map gets appended to the irq_domain */  //  Revmap data, used internally by irq_domain
	irq_hw_number_t hwirq_max;             // The largest hwirq that can be set for controllers that support direct mapping
	unsigned int revmap_direct_max_irq;
	unsigned int revmap_size;              // Size of the linear map table @linear_revmap[]
	struct radix_tree_root revmap_tree;    // Radix map tree for hwirqs that don't fit in the linear map
	struct mutex revmap_tree_mutex;
	unsigned int linear_revmap[];          // Linear table of hwirq->virq reverse mappings
};
```



## Irq implementation

Some basic functions for implementing new interrupt handlers 

- to register a new interrupt handler:  **request_irq()**
- to freeing an interrupt handler: **free_irq()**
- to declare and interrupt handler: **intr_handler()**

The way to implement an interrupt handler is with **request_irq()** to get your interrupt handler called when the relevant IRQ is received. This function receives the IRQ number, the name of the function, flags, a name for /proc/interrupts and a parameter to pass to the interrupt handler. Usually there is a certain number of IRQs available. How many IRQs there are is hardware dependant. The flags can include SA_SHIRQ to indicate you're willing to share the IRQ with other interrupt handlers (usually because a number of hardware devices sit on the same IRQ) and SA_INTERRUPT to indicate this is a fast interrupt. This function will only succeed if there isn't already a handler on this IRQ, or if you're both willing to share.
	
There are three main levels of abstraction in the interrupt code:
 
 - High-level driver API
 - High-level IRQ flow handlers
 - Chip-level hardware encapsulation

Detailed information is here: https://www.kernel.org/doc/html/latest/core-api/genericirq.html

## irq implementation example

reference: https://linux.die.net/lkmpg/x1256.html

```
/*
 *  intrpt.c - An interrupt handler.
 *
 *  Copyright (C) 2001 by Peter Jay Salzman
 */

/* 
 * The necessary header files 
 */

/* 
 * Standard in kernel modules 
 */
#include <linux/kernel.h>	/* We're doing kernel work */
#include <linux/module.h>	/* Specifically, a module */
#include <linux/sched.h>
#include <linux/workqueue.h>
#include <linux/interrupt.h>	/* We want an interrupt */
#include <asm/io.h>

#define MY_WORK_QUEUE_NAME "WQsched.c"

static struct workqueue_struct *my_workqueue;

/* 
 * This will get called by the kernel as soon as it's safe
 * to do everything normally allowed by kernel modules.
 */
static void got_char(void *scancode)
{
	printk(KERN_INFO "Scan Code %x %s.\n",
	       (int)*((char *)scancode) & 0x7F,
	       *((char *)scancode) & 0x80 ? "Released" : "Pressed");
}

/* 
 * This function services keyboard interrupts. It reads the relevant
 * information from the keyboard and then puts the non time critical
 * part into the work queue. This will be run when the kernel considers it safe.
 */
irqreturn_t irq_handler(int irq, void *dev_id, struct pt_regs *regs)
{
	/* 
	 * This variables are static because they need to be
	 * accessible (through pointers) to the bottom half routine.
	 */
	static int initialised = 0;
	static unsigned char scancode;
	static struct work_struct task;
	unsigned char status;

	/* 
	 * Read keyboard status
	 */
	status = inb(0x64);
	scancode = inb(0x60);

	if (initialised == 0) {
		INIT_WORK(&task, got_char, &scancode);
		initialised = 1;
	} else {
		PREPARE_WORK(&task, got_char, &scancode);
	}

	queue_work(my_workqueue, &task);

	return IRQ_HANDLED;
}

/* 
 * Initialize the module - register the IRQ handler 
 */
int init_module()
{
	my_workqueue = create_workqueue(MY_WORK_QUEUE_NAME);

	/* 
	 * Since the keyboard handler won't co-exist with another handler,
	 * such as us, we have to disable it (free its IRQ) before we do
	 * anything.  Since we don't know where it is, there's no way to
	 * reinstate it later - so the computer will have to be rebooted
	 * when we're done.
	 */
	free_irq(1, NULL);

	/* 
	 * Request IRQ 1, the keyboard IRQ, to go to our irq_handler.
	 * SA_SHIRQ means we're willing to have othe handlers on this IRQ.
	 * SA_INTERRUPT can be used to make the handler into a fast interrupt.
	 */
	return request_irq(1,	/* The number of the keyboard IRQ on PCs */
			   irq_handler,	/* our handler */
			   SA_SHIRQ, "test_keyboard_irq_handler",
			   (void *)(irq_handler));
}

/* 
 * Cleanup 
 */
void cleanup_module()
{
	/* 
	 * This is only here for completeness. It's totally irrelevant, since
	 * we don't have a way to restore the normal keyboard interrupt so the
	 * computer is completely useless and has to be rebooted.
	 */
	free_irq(1, NULL);
}

/* 
 * some work_queue related functions are just available to GPL licensed Modules
 */
MODULE_LICENSE("GPL");
```

## irq related files

-Check the folder: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/kernel/irq?h=v5.4.144

 - https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/kernel/irq/handle.c?h=v5.4.144

```
// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 1992, 1998-2006 Linus Torvalds, Ingo Molnar
 * Copyright (C) 2005-2006, Thomas Gleixner, Russell King
 *
 * This file contains the core interrupt handling code. Detailed
 * information is available in Documentation/core-api/genericirq.rst
 *
 */

```

## Bottom Halves

The bottom halves continue the process, stated by the interrupt handler and the top halves. This should be the most of the work, as the first part
should be as fast as possible, but never the less some minimum work, as acknoledge the reception of the interrupt, and copy the needed data. 

This division between top and bottom halves is needed, due the interrupt handler runs asyncrously, and it interrupts other routines. Not only that,
when the interrupt handle runs, it runs with the current interrupt disable, in the best case, and if it is the worst case, interrupt handlers registered
with SA_INTERRUPT, run with all local interrupts disabled. The goal of the bottom halves is to minimize the time in the interrupt handle, so interrupts are
disabled for the minimun time. Bottom halves, can run, with the interrupts enabled. 

There are several ways to implement bottom halves: 

 - softirqs
 - tasklts 
 - workqueues


## Softirqs

It is the basic mechanis for bottom haves. Tasklets are implemented on top of them. 

Softirqs are allocated statically at compile time. Softirqs represetned by the structure 'softirq_action' defined in <linux/interrupt.h>

https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/include/linux/interrupt.h?h=v5.4.144#n541

```
struct softirq_action
{
	void	(*action)(struct softirq_action *);
};
```
an array of this structure is defined at: kernel/softirq.c

https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/kernel/softirq.c?h=v5.4.144#n55

```
static struct softirq_action softirq_vec[NR_SOFTIRQS] __cacheline_aligned_in_smp;
```

So actually it is not possible to allocate more that NR_SOFTIRQS.


# Linux scheduler

 The linux kernel is multithreaded. The scheduler is the system that decides which task runs at each time. In linux the
scheduling is based in threads, not in processes. 

 The scheduler shares the cpu utilization between the tasks.
 
 It selects the next task to run (on each CPU) when:
 - running tasks ends
 - running task sleeps (or waits for an event)
 - a new task is created or a sleeping task wakes up
 - running task time-slice is over.

 The scheduler has scheduling policies with scheduling classes 
 - The scheduling class with highier priority is served first
 - a task can migrate between cpus, scheduling policies and scheduling classes
 - the scheduling classes are: stop, dl (deadline), rt (real-time), cfs(complete fair scheudling), idle.


  _**_schedule()** is the main scheduler function: https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/kernel/sched/core.c#n6127

  static struct task_struct ***pick_next_task()** : https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/kernel/sched/core.c#n5547
 
```
/*
 * Pick up the highest-prio task:
 */
static inline struct task_struct *
__pick_next_task(struct rq *rq, struct task_struct *prev, struct rq_flags *rf)
{
	const struct sched_class *class;
	struct task_struct *p;

	/*
	 * Optimization: we know that if all tasks are in the fair class we can
	 * call that function directly, but only if the @prev task wasn't of a
	 * higher scheduling class, because otherwise those lose the
	 * opportunity to pull in more work from other CPUs.
	 */
	if (likely(prev->sched_class <= &fair_sched_class &&
		   rq->nr_running == rq->cfs.h_nr_running)) {

		p = pick_next_task_fair(rq, prev, rf);
		if (unlikely(p == RETRY_TASK))
			goto restart;

		/* Assume the next prioritized class is idle_sched_class */
		if (!p) {
			put_prev_task(rq, prev);
			p = pick_next_task_idle(rq);
		}

		return p;
	}

restart:
	put_prev_task_balance(rq, prev, rf);

	for_each_class(class) {
		p = class->pick_next_task(rq);
		if (p)
			return p;
	}

	/* The idle class should always have a runnable task: */
	BUG();
}
```


 Each task (that represents a thread) is defined with the structure 'struct task_struct' (include/linux/sched.d) 
 
 reference: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/include/linux/sched.h?h=v5.4.144#n624

```
struct task_struct {
#ifdef CONFIG_THREAD_INFO_IN_TASK
	/*
	 * For reasons of header soup (see current_thread_info()), this
	 * must be the first element of task_struct.
	 */
	struct thread_info		thread_info;
#endif
	/* -1 unrunnable, 0 runnable, >0 stopped: */
	volatile long			state;

	/*
	 * This begins the randomizable portion of task_struct. Only
	 * scheduling-critical items should be added above here.
	 */
	randomized_struct_fields_start

	void				*stack;
	refcount_t			usage;
	/* Per task flags (PF_*), defined further below: */
	unsigned int			flags;
	unsigned int			ptrace;

#ifdef CONFIG_SMP
	struct llist_node		wake_entry;
	int				on_cpu;
#ifdef CONFIG_THREAD_INFO_IN_TASK
	/* Current CPU: */
	unsigned int			cpu;
#endif
	unsigned int			wakee_flips;
	unsigned long			wakee_flip_decay_ts;
	struct task_struct		*last_wakee;

	/*
	 * recent_used_cpu is initially set as the last CPU used by a task
	 * that wakes affine another task. Waker/wakee relationships can
	 * push tasks around a CPU where each wakeup moves to the next one.
	 * Tracking a recently used CPU allows a quick search for a recently
	 * used CPU that may be idle.
	 */
	int				recent_used_cpu;
	int				wake_cpu;
#endif
	int				on_rq;

	int				prio;
	int				static_prio;
	int				normal_prio;
	unsigned int			rt_priority;

	const struct sched_class	*sched_class;
	struct sched_entity		se;
	struct sched_rt_entity		rt;
#ifdef CONFIG_CGROUP_SCHED
	struct task_group		*sched_task_group;
#endif
	struct sched_dl_entity		dl;
...
```

Each task can have different states (defined also at include/linux/sched.)

reference: https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/include/linux/sched.h?h=v5.4

```
/* Used in tsk->state: */
#define TASK_RUNNING			0x0000
#define TASK_INTERRUPTIBLE		0x0001
#define TASK_UNINTERRUPTIBLE		0x0002
#define __TASK_STOPPED			0x0004
#define __TASK_TRACED			0x0008
/* Used in tsk->exit_state: */
#define EXIT_DEAD			0x0010
#define EXIT_ZOMBIE			0x0020
#define EXIT_TRACE			(EXIT_ZOMBIE | EXIT_DEAD)
/* Used in tsk->state again: */
#define TASK_PARKED			0x0040
#define TASK_DEAD			0x0080
#define TASK_WAKEKILL			0x0100
#define TASK_WAKING			0x0200
#define TASK_NOLOAD			0x0400
#define TASK_NEW			0x0800
#define TASK_STATE_MAX			0x1000
```

 -  reference: https://oska874.gitbooks.io/process-scheduling-in-linux/content/chapter5.html
 - reference: https://www.kernel.org/doc/html/latest/scheduler/index.html
 - reference: Graphing Tools for Scheduler Tracing:  https://inria.hal.science/hal-04001993/preview/RR-9498.pdf
 - reference: ftrace - function tracer. https://docs.kernel.org/trace/ftrace.html.
 - reference: https://www.trace-cmd.org/
 - https://github.com/sched-ext/scx
  
  
### Scheduling classes

There are different scheduling classes, defined at include/linux/sched.h

The scheduling classes are: stop, dl (deadline), rt (real-time), cfs(complete fair scheudling), idle.

They are defined at: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/kernel/sched/sched.h?h=v5.4.144#n1802

```
#define for_class_range(class, _from, _to) \
	for (class = (_from); class != (_to); class = class->next)

#define for_each_class(class) \
	for_class_range(class, sched_class_highest, NULL)

extern const struct sched_class stop_sched_class;
extern const struct sched_class dl_sched_class;
extern const struct sched_class rt_sched_class;
extern const struct sched_class fair_sched_class;
extern const struct sched_class idle_sched_class;
```

The following code is the code that represents a scheduling class.

reference: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/kernel/sched/sched.h?h=v5.4.144#n1712

```
struct sched_class {

    const struct sched_class *next;
    void (*enqueue_task) (struct rq *rq, struct task_struct *p, int flags);
    void (*dequeue_task) (struct rq *rq, struct task_struct *p, int flags);
    void (*yield_task) (struct rq *rq);
    bool (*yield_to_task) (struct rq *rq, struct task_struct *p, bool preempt);
    void (*check_preempt_curr) (struct rq *rq, struct task_struct *p, int flags);
    struct task_struct * (*pick_next_task) (struct rq *rq);
    void (*put_prev_task) (struct rq *rq, struct task_struct *p);
#ifdef CONFIG_SMP
    int (*select_task_rq)(struct task_struct *p, int sd_flag, int flags);
    void (*pre_schedule) (struct rq *this_rq, struct task_struct *task);
    void (*post_schedule) (struct rq *this_rq);
    void (*task_waking) (struct task_struct *task);
    void (*task_woken) (struct rq *this_rq, struct task_struct *task);
    void (*set_cpus_allowed)(struct task_struct *p, const struct cpumask *newmask);
    void (*rq_online)(struct rq *rq);
    void (*rq_offline)(struct rq *rq);
#endif
    void (*set_curr_task) (struct rq *rq);
    void (*task_tick) (struct rq *rq, struct task_struct *p, int queued);
    void (*task_fork) (struct task_struct *p);
    void (*switched_from) (struct rq *this_rq, struct task_struct *task);
    void (*switched_to) (struct rq *this_rq, struct task_struct *task);
    void (*prio_changed) (struct rq *this_rq, struct task_struct *task,  int oldprio);
    unsigned int (*get_rr_interval) (struct rq *rq,  struct task_struct *task);
#ifdef CONFIG_FAIR_GROUP_SCHED
    void (*task_move_group) (struct task_struct *p, int on_rq);
#endif
};
```
This is a skeleton of function pointers. 

All the scheduling classes in the linux kernel are in a linked list, ordered by highiest priority, and the next pointer, points to the next scheduler class. 

The scheduler walksthrough the highest scheduling class, to the lowest scheduling class. 

```
stop_sched_class → dl_shed_class → rt_sched_class → fair_sched_class → idle_sched_class → NULL
```

Stop and Idle are special scheduling classes. Stop is used to schedule the per-cpu stop task which pre-empts everything and can be pre-empted by nothing. It is used only for maintinance within the kernel, to stop everything and run some kernel specific routines.


Idle is used to schedule the per-cpu idle task (also called swapper task) which is run if no other task is runnable. The other two are for the previously mentioned real time and normal tasks. It is for CPU idle, so no tasks is associated with it

### Scheduling classes and policies

 - Stop
    - no policy
 - Deadline
    - SCHED_DEADLINE
 - Real Time
    - SCHED_FIFO
    - SCHED_RR
 - Fair
   - SCHED_NORMAL
   - SCHED_BATCH
   - SCHED_IDLE
 - Idle
   - no policy


-reference: https://intellipaat.com/community/62280/linux-schedother-schedfifo-and-schedrr-differences

SCHED_FIFO and SCHED_RR are called as "real-time" policies. They implement these fixed-priority real-time scheduling specified by the POSIX standard. Tasks with certain policies preempt every different task, which can easily go into starvation (if they don't release the CPU).

The difference between these SCHED_FIFO and SCHED_RR is that between the jobs with equal preference, SCHED_RR performs one round-robin with some certain timeslice; SCHED_FIFO, instead, requires the task to explicitly yield one processor.

SCHED_OTHER is one common round-robin time-sharing scheduling policy that schedules a job for a specific timeslice depending on each other tasks working in your system.

Update: since Linux 3.14, there is an extra policy called SCHED_DEADLINE. This policy executes the Constant Bandwidth Server (CBS) algorithm on the head of the Earliest Deadline First queues. Each duty under this policy is allowed a deadline, and the earliest-deadline task is executed. The best source describing the algorithm is Deadline scheduling in the Linux kernel.

Update 2: since Linux 4.13, SCHED_DEADLINE should replace CBS with the Greedy Reclamation of Unused Bandwidth (GRUB) algorithm.

Update 3: since Linux 6.6, EEVDF CPU scheduler (The "Earliest Eligible Virtual Deadline First" (EEVDF) scheduling algorithm) -> https://lwn.net/Articles/925371/  


#### stop_sched_class (STOP)

- stop_sched_class is the highiest priority class
- only present in SMP, not in User Plane. Because it is used to stop other CPUs. 
- it can preempt anything, and nothing can preempt it. 
- it is a mechanism to stop running everything else and run a specific function on a CPU.
- it has no scheduling policies
- it is used for tasks migrations, cpu migration, RCU, ftrace, clockevents, etc...

reference: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/kernel/sched/stop_task.c?h=v5.4.144#n119

#### dl_sched_class (DEADLINE)

 - Added by Dario Faggioli && Juri Lelli (3.14) (2013). it matches the EDF (Earliest Deadline first) 
 - Higiest priority class task in the system.
 - policy is SCHED_DEADLINE
 - implemented with a red-black tree (self balancing)
 - used for periodic real time tasks 

reference: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/kernel/sched/deadline.c?h=v5.4.144#n2436

reference: https://www.kernel.org/doc/html/latest/scheduler/sched-deadline.html

#### rt_sched_class (REAL TIME)

- this matches the POSIX real-tasks specs
- the priorities go from 0 to 99, being 0 the highest priority in kernel and 99 the lowest priority in user space
- policies
   - SCHED_FIFO: (First In First Out)
   - SCHED_RR:   (Round Robin) by default 100 ms slice time.
- implemented with linked lists
- used for short tasks, latency sensitive.

reference: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/kernel/sched/rt.c?h=v5.4.144#n2369

reference: https://www.kernel.org/doc/html/latest/scheduler/sched-rt-group.html

#### fair_sched_class CFS (Completelly Fair Scheduling)

- Scheduling Policies
   - SCHED_NORMAL: for normal task
   - SCHED_BATCH:  for cpu bounded tasks
   - SCHED_IDLE:   for low priority tasks
- Implemented with red-black trees (self-balancing)
- tracks the virtual time of tasks (the amount of time a task has run) 
- Task with shortes vruntime runs first
- the priority affects the weight of the task, and that will affect the runtime
- the task priority is: 120 + nice value (-20 to +19)
- used for all the system tasks. 

reference: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/kernel/sched/fair.c?h=v5.4.144#n10529

reference: https://www.kernel.org/doc/html/latest/scheduler/sched-design-CFS.html

#### idle_sched_class (Idle)

- lowes priority scheduling tasks
- no scheduling policies
- One thread (idle) per CPU: "swapper/N"
- the idle thread runs when there is nothing else to run
- idle thread may take the CPU to a lower power state.

reference: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/kernel/sched/idle.c?h=v5.4.144#n456

### Scheduling Policies

#### SCHED_DEADLINE 

In the Real-time literature SCHED_DEADLINE is the EDF (Earliest Dead-line First) scheduler. It the highes priority

This scheduling is more aggressive that SCHED_FIFO, but is harder to handle, and properly manage.

reference: https://www.kernel.org/doc/html/latest/scheduler/sched-deadline.html


#### SCHED_FIFO (First in First Out)

it is a real time scheduling class, defined by POSIX. It runs to completion the higiest prioririty task, with preemptions. it is deterministic

In general real-time tasks, will run until two causes
- complete and exit
- yield, sleep, activate a higher priority or blocked on secondary resource (system call)
- interrupt raised
 
#### SCHED_RR (Round Robin) 

It is also a real-time scheduling scheme, in order of priority tasks run in a round-robin fashion. If a RT (realtime) task is running no other task will be allowed to have processor times. task priority is defined by its rt_priority. it is deterministic. It uses time slices. 

In general real-time tasks, will run until two causes
- complete and exit
- yield, sleep, activate a higher priority or blocked on secondary resource (system call)
- interrupt raised

#### SCHED_OTHER or SCHED_NORMAL

It is the normal scheduling policy por linux. The CFS (Completely fair scheduler). The priority of this tasks in the "nice priority". The nice values ranges from -20 (highiest) to 19 (lowest priority) 

https://www.skillsire.com/read-blog/180_linux-scheduler-profiling.html

### SCHED_BATCH

It is when we want the task to run for longer, to take advantage of cashes for example. 

### SCHED_IDLE 

sCHED_IDLE is not the same as the schedule class 'idle'. SCHED_IDLE is for really low priority tasks.  

### The main runqueue (rq)

 Per CPU there is a runqueue with is a group of all the runnable tasks. rq is defined at kernel/sched.c. The runqueue (rq) also handles some statistics about the CPU load, and scheduling domains for load balancing between the CPUs. 
 
 - Each CPU has an instance of 'struct rq'. 
 - Each runqueue has DL, RT and CFS runqueues with it
 - Runnable taks are enqueued on those runqueues.
 - Many more information is available in the rq. 

reference: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/kernel/sched/sched.h?h=v5.4.144#n842

the rq has inside it references to the runqueues fo the different classes

```
struct rq {
...

	struct cfs_rq		cfs;
	struct rt_rq		rt;
	struct dl_rq		dl;
...

```
 
 
### Scheduler Topology

ref: https://www.kernel.org/doc/html/latest/scheduler/sched-capacity.html?highlight=topology#scheduler-topology

In the scheduler, it is describe what is refered as "CPU topoloy", this describes the memory/cache layouts, and what CPUs are sharing computing capacity (for example intel's hyperthreading), which CPUs are sharing the same caches (so it is possible to easily migrate tasks between CPUs without lossing the caches advantage [LLC: last level of Cache]), what CPUs are on the same dies, or if there is a numa system, it will describe the distance between nodes. 

This described as:

**Sched_domain** it the level in which is described the relation between CPUs

**Sched_group** is a group of CPUs in a Sched_domain. (it is possible to have a sched_group of only one CPU)

In the Sched_domain, flags are used to describe the dependecies between sched_groups

- SD_ASYN_CPUPACITY: between the groups, there are different computing capacities (some CPUs are bigger than others: like in ARM big-little architecture)
- SD_SHARE_CPUCAPACITY: the cpus in these groups will share some computing capacity.
- SD_SHARE_POWERDOMAIN: in case there are cpus that share the same power domain
- SD_SHARE_PKG_RESOURCES: when the cpus are sharing the cache and the access to the memory	

### Build Domain

In the scheduler the is a default sheduler topology, but it is possible to redefine it with **set_shed_topology()**, for each level, must provide cpu's mask, flags, name.

All levels of the scheduler topology are defined at Init.

It scheduler topology is rebuild at each topology change, for example: capacity update, cpu hotplug, cgroup partitioning

reference: https://www.kernel.org/doc/html/latest/scheduler/sched-domains.html

### Scheduler metrics

Metrics are used to decide in which CPU place the tasks, to adjust the CPU performace (scale it frequency) 

the main metrics are:

- for CFS scheduler: vruntime
- CPU capacity: the CPU computing capcity 
- PELT: Per Entity Load Tracking (entity can be a task or a group of tasks) 

#### vruntime

v is for virtual. vruntime is the virtualruntime of CFS scheduler. It is virtual because the metric is ponderated according to the task.

 - the vruntime is local for each CPU, it means the CPU that is running the task. 
 - vruntime weights the real running time with priority of the task
 - Nice 0 is the reference: vruntime == real runtime
 - Nice < 0: vruntime increases slower than real time -> so from the scheduler point of view, it will try to give the task more running time.
 - Nice > 0: vruntime increases faster than real time -> so from the scheudler point of view, it will try to provide less running time to that task.
 - the vruntime will be normalized for a sleeping task, so the scheduler dont provide too much time to a sleeping task.
 - the vruntime is normalized when a task is migrated to another CPU, so the scheduler don't provide too much time to a newly migrated task.

This will try to give more running time to the task with highier priority (lower nice). 
And the Scheduler, selects the next task, w/ lowerst vruntime. 

So the nice priority is used to compute the weight that would be applied to the task. The desider goal is that when your nices is reduced in 1, (priority is incresed by one) it task would have a 10% increment on the runtime. The priorities are precomputed in **sched_prio_to_weight array*

reference code: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/kernel/sched/core.c?h=v5.4.144#n8023

reference code: https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/kernel/sched/fair.c?h=v5.4.144#n7027

- **sched_period** tipical time for run all the tasks.
- **sched_slice** tipical time allocated for a given task.



	
reference: https://oska874.gitbooks.io/process-scheduling-in-linux/content/chapter2.html

reference: BKK19-TR03 - The Linux Kernel Scheduler - Overview: https://www.youtube.com/watch?v=oOiaRHC9ZDg

reference: https://linutronix.de/videos/2021_A_guided_tour_through_the_Preempt-RT_castle.mp4?m=1625133660&

reference: https://linutronix.de/PDF/2021_A_guided_tour_through_the_Preempt-RT_castle.pdf?m=1625133387&

reference: Real-Time Linux Kernel Scheduler: https://www.linuxjournal.com/article/10165

reference: YVR18-220:The Linux Kernel Scheduler (For Beginners):  https://www.youtube.com/watch?v=5WtnnzpwEuA&t=723s

reference: BKK19-TR06 - Deep dive in the scheduler: https://www.youtube.com/watch?v=1xhK0cH2Dkg

reference: A Checklist for Writing Linux Real-Time Applications - John Ogness, Linutronix GmbH: https://www.youtube.com/watch?v=NrjXEaTSyrw

reference: a guided tour to the preempt castle: https://linutronix.de/videos/2021_A_guided_tour_through_the_Preempt-RT_castle.mp4?m=1625133660&

## Linux for Real time

- reference: An introduction to real-time Linux : https://youtu.be/-wAo6bWh4jM
- reference: Building Hard Real-Time Linux Systems with Xenomai - Jan Kiszka, Siemens https://www.youtube.com/watch?v=ErZtYnDXhHk
- reference: Xenomai & Real-Time Linux: Driving OSS Projects for Siemens: https://youtu.be/G7PZF92aqkw
- reference: what aobut preemt-rt: https://youtu.be/KOYDloDBEds
- reference: preempt_rt list: https://youtube.com/playlist?list=PLmDQKQxAsgbak5aWa6WDKPvZeLcRKTUDE&si=tK6VlMa4mqmJ7BoO
- reference: preempt_rt pi: https://youtu.be/ntu55fiU18w 

For linux is possible to use extensions or patches for real-time

Linux uses to run under a fair scheduling system
- CFS completely fair schedule
- CFQ completely fair queue for I/O

The fair scheduling in linux is based on a round robin scheme, with some improvements as priority decay and other things, but you can even use a total round robin with SCHED_RR (round-robin)

But for real-time systems fair schedulers are not appropiate.

So for linux, we have the POSIX RT extensions. 

In multi-core systems, as we want determinism and simplicity, AMP (Asymetric Multi-processing) is preferred to SMP (Symetric Multi-processing), because SMP tends to load bance the cores, and this is not optimal for determinims. 

For linux real-time systems we would preffer AMP policy, because each work/task, can be assigned to each corresponding core. For this we can use thread affinity and by-pass SMP in linux, and emulate then an AMP affinity. AMP makes easier to model the behavior of the system, and then its predicitility. 

For linux real-time, the preferredy scheduling policy is SCHED_FIFO, because it is the policy priority preentive run to completion (this make it deterministic). Also basic synchronization mechanisms are needed, it can induce blocking but sometimes synchronization is needed. Also linux has included another scheduling policy EDF (Earliest Death-time First).

In linux a NPLT thread stands as the structure of a service. https://man7.org/linux/man-pages/man7/nptl.7.htm

references:
 - https://man7.org/linux/man-pages/man7/pthreads.7.html
 - https://en.wikipedia.org/wiki/Native_POSIX_Thread_Library
 - https://man7.org/linux/man-pages/man7/sched.7.html
 - https://www.kernel.org/doc/html/latest/scheduler/index.html
 - https://man7.org/linux/man-pages/man7/pthreads.7.html
 - https://man7.org/linux/man-pages/man7/posixoptions.7.html
 - https://man7.org/linux/man-pages/man7/standards.7.html


pthreads in user space are mapped into kernel tasks

RTOS on linux kernel dispacher runs:
 - on Entry point into kernel following inintialization
 - loops (idle) until task or tasks ar in the ready queue.
    - dispatches the highest priority task from the ready queue
    - Idle is not a task context, is a kernel context.
 - tasks or threads become ready and are dispatched when:
    - a sequencer or Interrupt Service Routine release ( as: semGive(), or sem_post())
    - as a result of a system call( as: mq_send(), taskActivate(), pthread_create())
    - the return of an ISR


 - Reference: Scheduling Algorithms for Multiprogramming in a Hard-Real-Time Environment https://dl.acm.org/doi/10.1145/321738.321743


NPTL provides a framework for:

 - fixed priority preemptive
    - rate monotonic
    - deadline monotonic
 
 - dynamic priority preemptive:
    - edf
    - llf 
  
 - non-preentive cooperation
    - multi-frequency executive
    - dataflow

different scheduling policies, for linux with real-time extensions: n <kernel/sched/rt.c>

https://www.kernel.org/doc/html/latest/scheduler/index.html#

SCHED_FIFO - priority preentive & run to completion. like RTOS. It is unfair and determistic. It is implemented with pthreads. 
And runs at priority until:
- complete and exit
- yield, sleep, activate a higher priority or blocked on secondary resource (system call)
- interrupt raised

SCHED_RR (round-robin) - fixed priority preentive: fair, higher overhed (due the tasks rotation in time slices), and it is deterministic.

SCHED_DEADLINE - dynamic priority alternative: adaptative and harder to model. this scheduler is also refered in the literature as EDF (Earliest death-line First) http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.517.771&rep=rep1&type=pdf

SCHED_OTHER: - CFS (Completelly fair scheduler) fair and hard to model. it is a best effort, scalable scheduler.

there are other schedulers as : SCHED_BATCH or SCHED_IDLE...


for hard real-time is recomended SCHED_FIFO, and for soft-real is recommended SCHED_DEADLINE.



```
                                              ┌───────────────────────────────────────────────────┐
                                              │                                                   │
                                              │                                                   │
                                              │                                                   │
                                              │                                                   │
                                              │                                                   │
                                              │                                                   │
                                                                                                  │
                      ◄─────────────────  EXECUTING   ──────────────►                             │
         Waiting on                                                    YielD anD                  │
           ReSourceS                        ▲   │                          WakeUp                 │
                                            │   │                                                 │
  sigWait()    │                            │   │                            │                    │
               │                            │   │ PREEMTED                   │                    │
mutex_lock()   │                   DipacheD │   │   OR YIELD                 │   usleep()         │   Suspended a in an
               │                            │   │   Sched_yield()            │                    │
               │                            │   │                            │    pauSe()         │   exeption (Division by 0)
               │                            │   │                            │                    │
               │                            │   │                            │                    │
               ▼        mutex_unlock()      │   ▼                            │                    │   sigsuspenD()
                                                                             ▼                    │
            PENDING   ─────────────────►    READY  ◄──────────────────   DELAYED                  │
                                                                                                  │
             │  ▲                            │  ▲                          ▲  │                   │
             │  │                            │  │                          │  │                   │
             │  │                            │  │                          │  │                   │
             │  │                            │  │                          │  │                   │
             │  │                            ▼  │                          │  │                   │
             │  │                                                          │  │                   │
             │  │                         SUPENDED                         │  │                   │
             │  └──────────────────────                ────────────────────┘  │                   │
             │                            + DELAYED                           │                   │
             └────────────────────────►                ◄──────────────────────┘                   │
                                           + PENDING                                              │
                                                                                                  │
                                               ▲                                                  │
                                               │                                                  │
                                               │                                                  │
                                               │                                                  │
                                               └──────────────────────────────────────────────────┘
```


For a given task, you can check its status with the `ps` command. Check `man ps` to see the different values:

```
$ man ps
...
PROCESS STATE CODES
       Here are the different values that the s, stat and state output specifiers (header "STAT" or "S") will display to describe the state of a process:

               D    uninterruptible sleep (usually IO)
               I    Idle kernel thread
               R    running or runnable (on run queue)
               S    interruptible sleep (waiting for an event to complete)
               T    stopped by job control signal
               t    stopped by debugger during the tracing
               W    paging (not valid since the 2.6.xx kernel)
               X    dead (should never be seen)
               Z    defunct ("zombie") process, terminated but not reaped by its parent

```


### Linux scheduler profiling

#### ftrace

Ftrace in an internal tracer (ftrace stands for Function Trace), which can be used for tracing, debugging and analyzing latencies. 

It is a root only tool, and it is mount in /sys/kernel/tracing 


 - reference: https://blogs.vmware.com/opensource/2019/11/12/ftrace-linux-kernel/
 - reference: https://www.kernel.org/doc/html/latest/trace/index.html
 - ref: https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux_for_real_time/7/html/tuning_guide/appe-detailed_description_of_ftrace

reference: compressed talk: Kernel Recipes 2017 - Understanding the Linux Kernel via Ftrace - Steven Rostedt https://www.youtube.com/watch?v=2ff-7UTg5rE&list=PL4mdyC_fNm4C0G2ycAenfNItroxA4_dXU

commands:

```
#cat trace
#cat available-traces

#echo function > current_tracer
#cat trace

#echo function_graph > current_tracer
#cat trace

#echo 0 > tracing_on ##disables writing to the ring-buffer... so the overhead is still there.

#echo 1 > tracing_on ##enable back it. !!watch out: there is no space between 1>

#cat available_filter_functions ##list the available tracers
```
There are several tracers. One of the most interesting ones for learning how the kernel works is the function tracer. 
It let you see almost all the functions running on the kernel. 

To limit the traces:
- set_ftrace_filter
- set_ftrace_notrace
- set_ftrace_pid
- set_graph_function
- set_graph_notrace

Setting the filters:

- by function name: `echo schedule > set_ftrace_filter`
- by glob matches: `echo 'mutex' > set_ftrace_filter`
- by extended glob matches: `echo '?raw_*lock' > set_ftrace_filter`
- **appending** the filter: `echo '*rcu' >> set_ftrace_filter
- clearing the filter: `echo > set_trace_filter`	

one example to trace the scheduler:

```
#echo scheduler > set_ftrace_filter
#echo function > current_tracer
#cat trace
```
a neat trick to trace only a process we are interested in:

```
#echo 0> tracing_on
#echo function> current_tracer
#sh -c 'echo $$> set_ftrace_pid; echo 1> tracing_on;
> exec echo hello
#cat trace
```

Also is possible to use the `set_graph_function`. It is similar to set_ftrace_filter,
but it picks a function to graph, and see what that function does.

example:
```
#echo Sys_read> set_graph_function
#echo function_graph> current_tracer
#cat trace
```

 - references: https://jvns.ca/blog/2017/03/19/getting-started-with-ftrace/
 - reference: https://www.youtube.com/watch?v=mlxqpNvfvEQ
 - reference: https://lwn.net/Articles/608497/


#### trace-cmd

trace-cmd in a command that works with ftrace 

reference: https://man7.org/linux/man-pages/man1/trace-cmd.1.html

#### kernel shark

its a front-end for trace-cmnd 

#### Perf

 perf creates a dump for later analyzing the events. 
 
references: https://www.skillsire.com/read-blog/180_linux-scheduler-profiling.html



linux preempt patch 

what is preempt_rt: https://linuxfoundation.org/blog/intro-to-real-time-linux-for-embedded-developers/

https://rt.wiki.kernel.org/index.php/CONFIG_PREEMPT_RT_Patch

overview: https://lwn.net/Articles/146861/

https://wiki.linuxfoundation.org/realtime/documentation/howto/applications/preemptrt_setup

https://www.kernel.org/doc/html/latest/scheduler/sched-rt-group.html

A realtime developer's checklist:  https://lwn.net/Articles/837019/
 

references:

https://man7.org/linux/man-pages/man7/sched.7.html

https://www.kernel.org/doc/html/latest/scheduler/index.html#

https://bootlin.com/doc/books/lkn.pdf

a complete guide to linux scheduling: https://trepo.tuni.fi/bitstream/handle/10024/96864/GRADU-1428493916.pdf

https://wiki.linuxfoundation.org/realtime/rtl/blog#the_real-time_endgame_is_moving_quickly_now

https://en.wikibooks.org/wiki/The_Linux_Kernel/Processing

https://www.kernel.org/doc/html/latest/scheduler/

https://www.kernel.org/doc/html/latest/scheduler/sched-energy.html

http://www.embeddedlinux.org.cn/rtconforembsys/5107final/toc.html

https://hpc-tutorials.llnl.gov/posix/

http://retis.sssup.it/~giorgio/paps/2005/rtsj05-rmedf.pdf

how to compile PREMPT patch https://www.youtube.com/watch?v=RjTfKF7gcIo

A realtime developer's checklist:  https://lwn.net/Articles/837019/


### Linux posix threads 

https://hpc-tutorials.llnl.gov/posix/

https://en.wikipedia.org/wiki/POSIX

https://www.cs.utexas.edu/~witchel/372/lectures/POSIX_Linux_Threading.pdf

https://www.amazon.com/POSIX-4-Programmers-Guide-Programming-World/dp/1565920740

posix real-time : https://www.ctr.unican.es/publications/mgh-1993a.pdf

https://www.gnu.org/software/libc/manual/html_node/POSIX.html#POSIX


### Time in linux

ref: https://man7.org/linux/man-pages/man7/time.7.html

linux with its posix real-time extension support both: absolute and relative time

Relative time is based in a hardware timer, based on PIT (Programmable Interval Timer) and TSC (Time Stamp Counter) or it is based in SCT (system Clock Time).

https://man7.org/linux/man-pages/man8/hwclock.8.html

Absolute time, that also is at times not really properly addresed as Real-time, is based on a baterry packed clock or in NTP (network time protocol).

Some times it may be interesting using the Julian Calendar instead of the Gregorian calendar (the calendar we use). Because the Julian Calendar increases monotincally. Also is interesting using the UTC.

Other time measurements TAI (Atomic Interantional Time), UTC, GPS ...

https://man7.org/linux/man-pages/man4/rtc.4.html

Posix RT- timer services for timeouts -> sem_timedwait()

https://cyberglory.wordpress.com/2011/08/21/jiffies-in-linux-kernel/

linux kernel in a nutshell: https://bootlin.com/doc/books/lkn.pdf




## preempt_rt

what is preempt_rt: https://linuxfoundation.org/blog/intro-to-real-time-linux-for-embedded-developers/

https://wiki.linuxfoundation.org/realtime/preempt_rt_versions

main website: https://wiki.linuxfoundation.org/realtime/start

https://emlid.com/raspberry-pi-real-time-kernel/

We’ve used cyclictest program to obtain data with the following parameters:

cyclictest -l10000000 -m -n -a0 -t1 -p99 -i400 -h400 -q 





## Notes on Linux kernel security overview 

- reference: Linux Security Module Usage: https://docs.kernel.org/admin-guide/LSM/index.html
- refernece: SE Linux: https://docs.kernel.org/admin-guide/LSM/SELinux.html

Notes on the talk https://www.youtube.com/watch?v=L7KHvKRfTzc&t=945s  - James Morris
Other reference: https://www.youtube.com/watch?v=McuP1_mvE_g

reference:  https://kernsec.org/

DAC - Discrection Acess control - This was the UNIX security mechanism. Linux is based in UNIX. This was the first approach. 

But UNIX was not desinged for security. DAC is not appropiate for the modern security threads. 

POSIX ACL (Access Control List), are stensions of DACs. https://www.usenix.org/legacy/publications/library/proceedings/usenix03/tech/freenix03/full_papers/gruenbacher/gruenbacher_html/main.html
https://linux.die.net/man/5/acl

There is an audit subsitem in the kernel; check https://linux.die.net/man/8/auditctl. Implemented to comply with goverment certification requirementes (similar to C2 ¿?) 
https://www.tecmint.com/linux-system-auditing-with-auditd-tool-on-centos-rhel/


Other security mechanism is **seccommp** : https://man7.org/linux/man-pages/man2/seccomp.2.html  https://outflux.net/teach-seccomp/  

Other security mechanism are **namespaces**: cgroup, ipc, network, pid, user, mount, uts, 

APIS: clone(2), setns(2), unshare(2), pam_namespace(8) 

In fact, linux containers are namespaces + cgroups, 

- Linux Namespaces: https://medium.com/@teddyking/linux-namespaces-850489d3ccf
- network namespaces: https://www.youtube.com/watch?v=j_UUnlVC2Ss
- Introduction to Linux Network Namespaces: https://www.youtube.com/watch?v=_WgUwUf1d34
- Understanding user namespaces - Michael Kerrisk: https://www.youtube.com/watch?v=83NOk8pmHi8
- Cgroups, namespaces, and beyond: what are containers made from?: https://www.youtube.com/watch?v=sK5i-N34im8


Regarding networking is the: **Netfilter**

Also the **Cryptograpy API**, also the keys managers, key rings, tokens ... In userland: **keyctl(1)**

serveral types of keys:

- per process, session
- trusted keys: TPM generated and sealed
- encrypted keys: kernel generated and encrypted

**LSM** : SELinux framework. Linux Security Modules: Allows, different access control schemes to be plugged into the kernel. https://www.starlab.io/blog/a-brief-tour-of-linux-security-modules

- https://www.kernel.org/doc/html/v5.0/admin-guide/LSM/index.html
- Overview and Recent Developments: seccomp and Small Linux Security Modules - Kees Cooke: https://www.youtube.com/watch?v=hTdXJbnnJ88
- Inside the Linux Security Modules (LSM) - Vandana Salve, Prasme Systems: https://www.youtube.com/watch?v=RKBBPsp-TZ0
- Tutorial: How to Write a Linux Security Module - Casey Schaufler: https://www.youtube.com/watch?v=4rFxZw3USIs

**SELinux** Security Enhanced Linux: 
- All objects & subjects have security labels,
- All relevant security interactions are mediated via fine-graned generalized permissions. 
- flexible security policies: separation of mechanism and policy 
- policy centrally administered, and no overridable by user (include root)
- helps contain breaches via least privilige
- implemented in fedora family, android.

**KSP** kernel Self protection project:(KSPP) hardening the kernel against an attack;

- https://kernsec.org/wiki/index.php/Kernel_Self_Protection_Project
- https://kernsec.org/wiki/index.php/Projects
- https://redhatgov.io/workshops/selinux_policy/

## Brief overview of the memory

### The Virtual File System (VFS)

The virtual file system (VFS), is an abstraction mechanism that allows the linux kernel, use different file systems, 
without the knowledge ot their inner workings or use details. 

The VFS abstraction, is achieved using a common model for all the files. That model is the base to use any file in linux, 
and for all the different file systems. By means of pointers to funcions and other object oriented methods, the common interface
to work with the files, provides a framework that has to work for every file system implemented in linux. This framework provides the
methods to create, read, create links, syncronize and other operations ... and the implementation of the file system 
register the functions that the file system is able to perform.

This approach, makes that the most of the file systems share behaviors. For example, the VFS, works based on the use
of inodes, superblocks, and directory entries. A file system that is not based in Unix, most possible lacks those concepts, 
but has to cope wit it. For example the FAT or NFTS file systems. 

The advanteges of VFS are remarkable. Only one system call can read any file, on any media. A unique program/application
can copy from any file system ot any other. All the file systems are based on the same concepts, interfaces and calls. 

For example when a given program calls the system call 'read()', the C library provides the definitions of the system calls, 
so from the user-space, the system call, moves into the kernel. Then the kernel figures out the objects that backs the given 
file descriptor, and calls the fitting function asssociated with the backing object. For the file systems this is part of the
code that implements the file system. Then the data is read from the physical medium, and the data is returned to user-space, 
where the 'read()' call returns, and the program continues its execution.

You can see the struct that has all the function pointers for any file at: https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/include/linux/fs.h#n1981

```
struct file_operations {
	struct module *owner;
	loff_t (*llseek) (struct file *, loff_t, int);
	ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
	ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
	ssize_t (*read_iter) (struct kiocb *, struct iov_iter *);
	ssize_t (*write_iter) (struct kiocb *, struct iov_iter *);
...
```

The __ user tag, indicates that this information, comes from user space.

reference: https://www.kernel.org/doc/html/v5.16/filesystems/index.html

And example of how to write a VFS: https://github.com/torvalds/linux/blob/2c271fe77d52a0555161926c232cd5bc07178b39/fs/ramfs/inode.c#L12


### The Page Cache
... to be continued


## Building a minimal linux system with busybox

reference: reference: https://youtu.be/asnXWOUKhTA?list=PLw27zZE-QQB9z59AI0EnAE998NSSJ4k9p

```
#!/bin/bash

# reference: https://youtu.be/asnXWOUKhTA?list=PLw27zZE-QQB9z59AI0EnAE998NSSJ4k9p
# we will need a kernel and a root partition, and in that root partition we will install busybox

KERNEL_VERSION=5.15.6
BUSYBOX_VERSION=1.34.1

mkdir -p src
cd src

	# Kernel: donwload, unpack, default configuration and compile
	
	KERNEL_MAJOR=$(echo $KERNEL_VERSION | sed 's/\[0-9]*)[^0-9].*/\1/')
	wget https://mirrors.edge.kernel.org/pub/linux/kernel/v$KERNEL_MAJOR/linux-$KERNEL_VERSION.tar.gz
	tar -xf linux-$KERNEL_VERSION.tar.xz
	cd linux-$KERNEL_VERSION
	
		make defconfig
		make -j$(nproc) || exit
	cd ..
	
	# Busybox: download, unpack
	wget https://busybox.net/downloads/busybox-$BUSYBOX_VERSION.tar.bz2
	tar -xf busybox-$BUSYBOX_VERSION.tar.bz2
	cd busybox-$BUSYBOX_VERSION
		
		make defconfig
		# we need a static build of busybox. So the libraries are build into the executable binary
		sed 's/^.*CONFIG_STATIC[^_].*$/CONFIG_STATIC=y/g' -i .config	
		make -j$(nproc)|| exit
	
		# you need to install musl at least in manjaro based systems
		# sudo packman -s musl kernel-headers-musl
		# make CC=musl-gcc -j$(nproc) busybox || exit
	
	cd ..
	
cd ..

# now pull the compiled kernel from the source directory 
cp src/linux-$KERNEL_VERSION/arch/x86_64/boot/bzImage ./

# we need a root drive: initrd
mkdir initrd
cd initrd 

	# create standard directories
	mkdir -p bin dev proc sys
	cd bin
	
		cp ../../src/busybox-$BUSYBOX_VERSION/busybox ./
		
		for prog in $(./busybox --list); do
		# iterate through all the programs and create sym links
			ln -s /bin/busybox ./$prog
		done

	cd ..
	
	# tell the kernel what to do at start up, for that we create a init script
	echo '#!/bin/sh' > init
	echo 'mount -t sysfs sysfs /sys' >> init
	echo 'mount -t proc proc /proc' >> init
	echo 'mount -t devtmpfs udev /dev' >> init
	echo 'sysctl -w kernel.printk="2 4 1 7"' >> init
	echo 'clear' >> init
	echo '/bin/sh' >> init
	echo 'poweroff -f' >> init # turn the hw off when the terminal is exited.
	
	chmod -R 777 . # maybe we are overdoing here
	
	find . | cpio -o -H newc > ../initrd.img
		
cd ..

# launch the system
quemu-system-x86_64 -kernel bzImage -initrd initrd.img

# you can use also: -nographic -append 'console=tyyS0' 
# so you handle a serial interface
# in need of killing qemu: killall qemu*
```

## Linux kernel contextes

- reference: https://stackoverflow.com/questions/47063693/atomic-context-and-process-context-interrupt-context

**Process Context** - Regular processes and syscall invocations execute in this context and it can be interrupted by IRQs

**Atomic Context** - IRQs are generally executed in this context and they don't belong to any specific process, but rather are invoked by some device(ignore exceptions for simplicity). Once the interrupt context sleeps or gives up the CPU, it cannot be awakened. So it is also called atomic context.

A basic principle of the kernel is that in an interrupt or atomic context, the kernel cannot access user space, and the kernel cannot sleep.

## Linux networking

- https://wiki.linuxfoundation.org/networking/sk_buff
- https://wiki.linuxfoundation.org/networking/kernel_flow
- https://wiki.linuxfoundation.org/networking/start
- socket buffer sctructure: skb  - http://vger.kernel.org/~davem/skb.html
- Linux Networking - eBPF, XDP, DPDK, VPP - What does all that mean? (by Andree Toonk) : https://youtu.be/hO2tlxURXJ0
- Linux packet journey,napi, hardware queue,skb : https://youtu.be/6Fl1rsxk4JQ
- Device trees for dummies! https://www.youtube.com/watch?v=m_NyYEBxfn8
- https://www.wireguard.com/
- Linux Networking - eBPF, XDP, DPDK, VPP - What does all that mean? (by Andree Toonk) : https://youtu.be/hO2tlxURXJ0
- Kernel-bypass techniques for high-speed network packet processing: https://youtu.be/MpjlWt7fvrw
- How Linux processes your network packet - Elazar Leibovich: https://youtu.be/3Ij0aZRsw9w
- Introduction to DPDK: https://youtu.be/1DWxo2gF-RQ
- Linux network device driver internals | Linux kernel | Linux network device driver : https://youtu.be/aq0TLYXGQCA?list=PLOEpetqiDZSrfM_HYPe9l6RC782Ttul2H
- DPDK deep-dive: https://youtu.be/VJ8CVN3oXMw


## RCU
 
 - https://paulmck.livejournal.com/69622.html
 - https://docs.kernel.org/RCU/whatisRCU.html
 - The RCU api, 2019 edition: https://lwn.net/Articles/777036/


## Other references for laters

- Mentorship Session: Trust and the Linux Kernel Development Model https://youtu.be/YhDVC7-QgkI
- https://thenewstack.io/demystifying-linux-kernel-initialization/
- An introduction to Linux kernel initcalls: https://www.collabora.com/news-and-blog/blog/2020/07/14/introduction-to-linux-kernel-initcalls/
- Understanding the Linux Kernel Initcall Mechanism: https://kernelnewbies.org/Documents/InitcallMechanism
- A Whistlestop Tour of Embedded Linux:  https://www.youtube.com/watch?v=wwtWS0OcQJI&t=1034s
- Make Linux safer… or die trying: https://www.theregister.com/2023/02/14/make_linux_safer_p1/
- https://www.phoronix.com/news/Linux-6.3-Networking-BIG-TCP
- BIG TCP: https://lwn.net/Articles/883713/
- Linux Kernel Oops!: https://nakedsecurity.sophos.com/2023/03/13/linux-gets-double-quick-double-update-to-fix-kernel-oops/
- Tun/tap interfaces: https://backreference.org/2010/03/26/tuntap-interface-tutorial/index.html
- kprobes: https://ish-ar.io/kprobes-in-a-nutshell/
- Build a minimal Linux with only Busybox in 1 hour: https://youtu.be/asnXWOUKhTA?list=PLw27zZE-QQB9z59AI0EnAE998NSSJ4k9p
- Bootlin: Linux debugging, profiling, tracing and performance analysis training ...  https://bootlin.com/doc/training/debugging/debugging-slides.pdf

### BPF & eBPF

- Kernelless Kernel Programming (eBPF) - Computerphile : https://youtu.be/J_EehoXLbIU
- What is ebpf: https://youtu.be/jM3vL2LLm5o
- Mentorship session: kernel tracing with eBPF: https://youtu.be/JqnWp6X6otw
- Fast by Friday: Why eBPF is Essential - Brendan Gregg: https://youtu.be/s1mobd8t_u0
- eBPF: Unlocking the Kernel [OFFICIAL DOCUMENTARY] : https://youtu.be/Wb_vD3XZYOA
- eBPF: Fueling New Flame Graphs & more • Brendan Gregg • YOW! 2022 : https://youtu.be/HKQR7wVapgk
- Linux Networking - eBPF, XDP, DPDK, VPP - What does all that mean? (by Andree Toonk) : https://youtu.be/hO2tlxURXJ0
- https://github.com/sched-ext/scx sched_ext is a Linux kernel feature which enables implementing kernel thread schedulers in BPF and dynamically loading them. This repository contains various scheduler implementations and support utilities.

### DMR 

The Direct Rendering Manager (DRM) is a subsystem of the Linux kernel responsible for interfacing with GPUs of modern video cards. DRM exposes an API that user-space programs can use to send commands and data to the GPU and perform operations such as configuring the mode setting of the display. DRM was first developed as the kernel-space component of the X Server Direct Rendering Infrastructure,[1] but since then it has been used by other graphic stack alternatives such as Wayland and standalone applications and libraries such as SDL2 and Kodi.

User-space programs can use the DRM API to command the GPU to do hardware-accelerated 3D rendering and video decoding, as well as GPGPU computing. 

References:
 - tutorial: https://landley.net/kdocs/htmldocs/drm.html
 - https://en.wikipedia.org/wiki/Direct_Rendering_Manager
 - https://en.wikipedia.org/wiki/Linux_framebuffer
 - https://www.kernel.org/doc/Documentation/fb/framebuffer.txt
 - https://en.wikipedia.org/wiki/General-purpose_computing_on_graphics_processing_units
 - https://bootlin.com/pub/conferences/2017/kr/ripard-drm/ripard-drm.pdf
 - https://github.com/ascent12/drm_doc
 - https://www.uninformativ.de/blog/postings/2020-05-30/0/POSTING-en.html
 - https://gist.github.com/uobikiemukot/c2be4d7515e977fd9e85
 - http://liujunming.top/2019/10/22/libdrm-samples/
 - https://youtu.be/LbDOCJcDRoo
 - https://www.youtube.com/watch?v=toSMe3g9emE

 
## And other references for elaborate later ...

### XArray: 
 - https://docs.kernel.org/core-api/xarray.html
 - The design and implementation of the XArray : https://www.youtube.com/watch?v=v0C9_Fp-co4
 - XArray: One Data Structure To Rule Them All : https://www.youtube.com/watch?v=-Bw-HWcrnss
 - Matthew Wilcox: How Linux handles IO errors -- PGCon 2018 : https://www.youtube.com/watch?v=74c19hwY2oE

### What happens when Linux runs out of memory? : https://youtu.be/Cm3-6cOwICU

### Linux containers the hard way:
- https://hackaday.com/2023/08/07/linux-containers-the-hard-way/
- https://github.com/lucavallin/barco
- https://redhatgov.io/workshops/containers_the_hard_way/


### Device trees:
 - https://docs.kernel.org/devicetree/index.html
 - https://devicetree-specification.readthedocs.io/en/stable/index.html
 - https://mjoldfield.com/atelier/2017/03/rpi-devicetree.html
 - https://www.youtube.com/watch?v=_Z65pqLSMi8&t=41s
 - https://www.youtube.com/watch?v=YxDEdpHTEP8
 - https://hackaday.com/2022/04/04/a-power-button-for-raspberry-pi-courtesy-of-device-tree-overlays/
 - https://bootlin.com/blog/enabling-new-hardware-on-raspberry-pi-with-device-tree-overlays/
 - https://www.jeffgeerling.com/blog/2023/how-customize-dtb-device-tree-binary-on-raspberry-pi
 - https://github.com/raspberrypi/documentation/blob/develop/documentation/asciidoc/computers/configuration/device-tree.adoc
 - https://docs.kernel.org/devicetree/index.html#kernel-devicetree-usage
 - device tree 101: https://youtu.be/a9CZ1Uk3OYQ
 - Device Tree overlays and U-Boot extension board management, Köry Maincent : https://youtu.be/mxWiK2v-KZc
   


<br>

- https://redhatgov.io/workshops/selinux_policy/
- Kernel Magnifier: A Linux Kernel Execution Flow Research Tool for Upcomming Kernel Hackers (and Veterans): https://github.com/hgn/kernel-magnifier


### Linux Kernel Runtime Guard:
 - https://lkrg.org/

### i2c in linux:
 - https://www.eevblog.com/forum/microcontrollers/i2c-sensor-integration-in-linux/
 - https://www.kernel.org/doc/Documentation/i2c/
 - Basics of I2C on Linux - Luca Ceresoli, Bootlin -- The Linux Foundation: https://youtu.be/g9-wgdesvwA
 - The video discusses the driver for the PCA9570: https://github.com/torvalds/linux/blob/master/drivers/gpio/gpio-pca9570.c
 - Let's code a Linux Driver - Johannes 4GNU_Linux: https://www.youtube.com/playlist?list=PLCGpd0Do5-I3b5TtyqeF1UdyD4C-S-dMa


### iio - industrial I/O:
 - https://abhashpl.hashnode.dev/my-linux-kernel-bug-fixing-mentorship-experience (iio drives)
 - https://www.kernel.org/doc/html/latest/driver-api/iio/index.html
 - https://linux.ime.usp.br/~marcelosc/2019/09/Simple-IIO-driver
 - https://linux.ime.usp.br/~marcelosc/2019/09/Introduction-to-IIO-driver-development
 - 10 Years of the Industrial I/O Kernel Subsystem - Jonathan Cameron: https://youtu.be/644oH1FXdtE?si=1A9JVMcIvjoRdIi1
 - https://www.kernel.org/doc/html/v4.12/driver-api/uio-howto.html
 - https://bootlin.com/blog/the-backbone-of-a-linux-industrial-i-o-driver/
 - https://www.kernel.org/doc/html/v4.12/driver-api/iio/index.html
 - rpi compilation tutorial: https://linux.ime.usp.br/~marcelosc/2019/09/RaspberryPi-kernel-compilation
 - video iio example: https://youtu.be/l8mQtpZhgYI
 - https://linux.ime.usp.br/~marcelosc/2019/09/Introduction-to-IIO-driver-development
 - https://linux.ime.usp.br/~marcelosc/2019/09/Simple-IIO-driver
 - LibIIO - A Library for Interfacing with Linux IIO Devices - Dan Nechita: https://youtu.be/p_VntEwUe24
 - example PR: https://github.com/analogdevicesinc/linux/pull/436/commits/3d2c7522c01b19c19c77adfac0ab1546b56426bc
 - how to connect to a rpi thru the USB port: https://linux.ime.usp.br/~marcelosc/2019/01/SSH-em-Raspberrypi-conectada-por-USB
 - LibIIo: https://www.youtube.com/watch?v=p_VntEwUe24
 - sample: https://elixir.bootlin.com/linux/latest/source/drivers/iio/dummy/iio_simple_dummy.c
 - I2C: https://www.kernel.org/doc/html/v4.12/driver-api/i2c.html#
 - SPI: https://www.kernel.org/doc/html/v4.12/driver-api/spi.html
 - i2c in linux: https://www.linkedin.com/pulse/understanding-i2c-communication-linux-beginners-guide-soheil-nazari
 - i2c in linux: https://elinux.org/Interfacing_with_I2C_Devices
 - i2c in kernel: https://www.kernel.org/doc/Documentation/i2c/dev-interface
 - SPI in kernel: https://docs.kernel.org/spi/index.html


### Control-flow integrity for the kernel
Control-flow integrity (CFI) is a technique used to reduce the ability to redirect the execution of a program's code in attacker-specified ways. The Clang compiler has some features that can assist in maintaining control-flow integrity:
 - https://lwn.net/Articles/810077/
 - https://source.android.com/docs/security/test/kcfi

### Debugging the linux kernel

 - Setup Linux Kernel Debugging with QEMU and GDB: https://medium.com/@alessandrozanni.dev/setup-linux-kernel-debugging-with-qemu-and-gdb-e5446c16cd85


### LTO Link-time optimization for the kernel:
 - https://lwn.net/Articles/512548/

### Rust for linux

 - https://medium.com/@alessandrozanni.dev/rust-in-kernel-development-1aea34e5c4b0

### Linux kernel tinification: 
 - https://tiny.wiki.kernel.org/
 - https://lwn.net/Articles/608945/

### Linux kernel Panic, Oops, core dumps and debugging:
 - https://www.dedoimedo.com/computers/lkcd.html
 - https://www.dedoimedo.com/computers/crash-analyze.html
 - crahsdumps: https://wiki.ubuntu.com/Kernel/CrashdumpRecipe
 - https://wiki.ubuntu.com/Kernel/KernelDebuggingTricks
 - https://elinux.org/Debugging_The_Linux_Kernel_Using_Gdb
 - https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/kernel_administration_guide/kernel_crash_dump_guide
 - https://ubuntu.com/server/docs/kernel-crash-dump
 - Debugging Analysis of Kernel panics and Kernel oopses using System Map:: https://sanjeev1sharma.wordpress.com/tag/debug-kernel-panics/
 - Understanding a Kernel Oops!: https://www.opensourceforu.com/2011/01/understanding-a-kernel-oops/
 - Linux kernel gets "blue screens" with QR code: https://www.heise.de/en/news/Linux-kernel-gets-blue-screens-with-QR-code-9851774.html


### Schedstat
 - reference: https://www.phoronix.com/news/AMD-Linux-perf-schedstat-Tool
 - https://docs.kernel.org/scheduler/sched-stats.html

### USB
 - https://www.beyondlogic.org/usbnutshell/usb1.shtml
 - https://www.kernel.org/doc/html/v4.12/driver-api/usb/writing_usb_driver.html
 - https://www.kernel.org/doc/html/v4.15/driver-api/usb/index.html
 - https://github.com/gregkh/usbutils
 - https://github.com/libusb/libusb?tab=readme-ov-file


### Using Syzkaller
  - Using syskaller part1: fuzzing the linux kernel: https://www.collabora.com/news-and-blog/blog/2020/03/26/syzkaller-fuzzing-the-kernel/
  - detecting programming bugs in the linux kernel: https://www.collabora.com/news-and-blog/blog/2020/04/17/using-syzkaller-to-detect-programming-bugs-in-linux/
  - fuzzing your changes: https://www.collabora.com/news-and-blog/blog/2020/05/12/using-syzkaller-fuzzing-your-changes/
  - driving fuzzing: https://www.collabora.com/news-and-blog/blog/2020/06/26/using-syzkaller-part-4-driver-fuzzing/
  - finding linux kernel bugz with syskaller: https://youtu.be/50XmhnJO5p8
  - Set up syz enviroment to reproduce bugs
     - reference: https://github.com/google/syzkaller/blob/master/docs/syzbot.md#bisection
     - reference: https://groups.google.com/g/syzkaller-bugs/c/HW4z7PpD9B0/m/XQTdRRHrAwAJ
   
### Event trazing resources: 
  - https://www.kernel.org/doc/html/latest/trace/events.html
  - https://www.collabora.com/news-and-blog/blog/2019/05/14/an-ebpf-overview-part-5-tracing-user-processes/

### Static_calls
 - https://thenewstack.io/linux-kernel-5-10-introduces-static-calls-to-prevent-speculative-execution-attacks/
 - https://lore.kernel.org/lkml/20191007083830.64667428.5@infradead.org/

The release of the Linux 5.10 kernel brings a new feature to protect against speculative execution attacks. That feature is called static calls and is a replacement for global function pointers in the Linux kernel

### tun-tap interfaces
 - https://www.gabriel.urdhr.fr/2021/05/08/tuntap/
 - https://backreference.org/2010/03/26/tuntap-interface-tutorial/index.html
 - https://john-millikin.com/creating-tun-tap-interfaces-in-linux


### more references
  - https://hackmd.io/@0xff07/linux

### Creating a chroot enviroment
 - https://dev.to/robogeek95/creating-a-chrooted-environment-1gkd

### io_uring

 - https://lwn.net/Articles/776703/
 - https://lwn.net/Articles/810414/
 - https://developers.redhat.com/articles/2023/04/12/why-you-should-use-iouring-network-io
 - https://unixism.net/loti/
 - https://blog.cloudflare.com/missing-manuals-io_uring-worker-pool/
 - https://github.com/espoal/awesome-iouring
 - https://youtu.be/-5T4Cjw46ys
 - https://youtu.be/AaaH6skUEI8
 - https://github.com/axboe/liburing
 - https://kernel.dk/io_uring.pdf
 - https://elixir.bootlin.com/linux/v6.10-rc7/source/include/linux/io_uring_types.h#L594
 - https://www.scylladb.com/2020/05/05/how-io_uring-and-ebpf-will-revolutionize-programming-in-linux/

### RTLA

 - https://bristot.me/linux-scheduling-latency-debug-and-analysis/
 - https://lwn.net/Articles/979912/
 - https://elisa.tech/
 - https://docs.kernel.org/admin-guide/workload-tracing.html

### Linux kernel debugging
 - https://www.youtube.com/watch?v=FdNIiQxwJuk
 - https://marliere.net/posts/2/
 - https://en.wikibooks.org/wiki/The_Linux_Kernel/Debugging#

### Linux kernel backporting

 References:
  - questions about backporting: https://groups.google.com/g/syzkaller/c/aSvzuUHiDIQ
  - https://www.kernel.org/doc/html/next/process/backporting.html#submitting-backports-to-stable
  - https://www.kernel.org/doc/html/next/process/backporting.html
  - https://www.kernel.org/doc/html/latest/process/stable-kernel-rules.html
  - backporting linux kernel patches: https://www.youtube.com/watch?v=sBR7R1V2FeA


### virtme-ng

 - https://github.com/arighi/virtme-ng

virtme-ng is a tool that allows to easily and quickly recompile and test a Linux kernel, starting from the source code.

It allows to recompile the kernel in few minutes (rather than hours), then the kernel is automatically started in a virtualized environment that is an exact copy-on-write copy of your live system, which means that any changes made to the virtualized environment do not affect the host system.

### compiling the linux kernel with clang/llvm

References: 
 - https://zawzaww.github.io/posts/compile-linux-clang-llvm/
 - https://www.kernel.org/doc/html/latest/kbuild/llvm.html
 - Mentorship Session: Using Clang and LLVM to Build the Linux Kernel: https://youtu.be/y458QwEfSsU

### Btrfs

References:
 - https://wiki.tnonline.net/w/Category:Btrfs
 - https://btrfs.readthedocs.io/en/latest/Introduction.html
 - https://surajsinghbisht054.medium.com/understand-btrfs-file-system-copy-on-write-sub-volumes-snapshots-quota-group-part-1-c6305f87df9b
 - https://surajsinghbisht054.medium.com/understand-btrfs-file-system-copy-on-write-sub-volumes-snapshots-quota-group-part-2-2b60209c5296
 - https://unix.stackexchange.com/questions/209165/conceptualizing-btrfs-understanding-snapshots-and-space-used
 - https://wiki.archlinux.org/title/Btrfs
 - https://btrfs.readthedocs.io/en/latest/


### Display Linux CPU topology with lstopo
 - https://www.thomas-krenn.com/en/wiki/Display_Linux_CPU_topology_with_lstopo
 - `apt install hwloc`

### Linux initialization

 - https://thenewstack.io/demystifying-linux-kernel-initialization/

### using gdb to debugg the kernel

 - https://www.starlab.io/blog/using-gdb-to-debug-the-linux-kernel


### Linux Kernel Memory Model (LKMM)

 - Linux-Kernel Memory Model: https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p0124r7.html
 - https://github.com/aparri/memory-model/blob/master/Documentation/explanation.txt
 - Installing and Using the Linux-Kernel Memory Model (LKMM) - Paul McKenney : https://www.youtube.com/watch?v=YPpojI84WZk
 - More Science Fiction than Fairy Tale: A Discussion of the Linux Kernel Memory Mo... Jonas Oberhauser : https://www.youtube.com/watch?v=iFDKhIxKhoQ
 - P99 CONF 2023 | How to Avoid Learning the Linux-Kernel Memory Model by Paul McKenney : https://www.youtube.com/watch?v=T7VwKaU129w

### Linux file systems
 - Writing Linux File System for Fun : https://www.youtube.com/watch?v=sLR17lUjTpc
 - Creating and Mounting a Filesystem on Linux: Step-by-Step Guide : https://www.youtube.com/watch?v=06INoQnj-s4


 ### Control Flow Integrity
 - https://outflux.net/slides/2020/lca/cfi.pdf
 - https://lpc.events/event/16/contributions/1315/attachments/1067/2169/cfi.pdf
 - https://source.android.com/docs/security/test/kcfi

  ### Linux filesystems
   - Linux Storage Stack Explained - Werner Fischer, Thomas-Krenn.AG: https://youtu.be/hCKruOlLPIQ


### Booting process

 - https://bootlin.com/blog/demystifying-kernel-boot-sequence/#:~:text=Userspace%E2%80%9D%20%2D%20Bootlin's%20blog-,Demystifying%20the%20Kernel%20Boot%20Sequence%3A%20From%20'Starting%20Kernel%E2%80%A6',boot%20process%20does%20this%20happen%3F
 - https://people.kernel.org/linusw/how-the-arm32-kernel-starts
 - https://opensource.com/article/17/2/linux-boot-and-startup
 - https://kleinembedded.com/understanding-the-embedded-linux-boot-process/
 - https://github.com/nu11secur1ty/All-Stages-of-Linux-Booting-Process-Architecture/blob/master/README.md
 - https://medium.com/@ahmedmansouri/my-notes-for-understanding-the-linux-boot-process-a-comprehensive-guide-1bb484375179
 - https://medium.com/@gangulysutapa96/6-stages-of-linux-boot-process-5ee84265d8a0


### Risc-V
 -  Embedded Linux from Scratch in 45 minutes, on RISC-V: https://youtu.be/cIkTh3Xp3dA

```
#!/bin/bash

set -euo pipefail

HOST_ARCH=$(uname -m)
ROOT=${1:?missing root filesystem}
ARCH=${2:-$HOST_ARCH}

BASE_DEPS=git
INCLUDE=--include=$BASE_DEPS

if [[ $ARCH == "$HOST_ARCH" ]]; then
    sudo debootstrap "$INCLUDE" sid "$ROOT"
else
    sudo debootstrap --arch "$ARCH" --foreign "$INCLUDE" sid "$ROOT"
    sudo chroot "$ROOT" bash -c "/debootstrap/debootstrap --second-stage"
fi

KSELFTESTS="build-essential flex bison libasound2-dev libcap-ng-dev libcap-dev libnuma-dev libmnl-dev pkg-config rsync libpopt-dev libssl-dev libelf-dev clang liburing-dev libfuse3-dev libfuse-dev"
LTP="python3 python3-asyncssh python3-msgpack"
sudo chroot "$ROOT" bash -c "apt install -y $KSELFTESTS $LTP"

# sudo vng --verbose --user root --arch riscv64 --root $roots/riscv/sid --run $linux/riscv64/ --force-9p --rw -n user

# https://cloud-images.ubuntu.com/
# https://download.opensuse.org/ports/
# https://cloud.debian.org/images/cloud/
```

> IMHO buildroot is awesome but may be overkill; if you have debootstrap (the debian tool, it's packaged in opensuse and probably in red hat too) you can use something like this... then use vng to run a kernel with it!
>
> that of course imply in having the correct qemu-system package, etc


### dynamic debugging

- https://documentation.suse.com/sles/15-SP6/html/SLES-all/cha-tuning-dynamic-debug.html
- https://android.googlesource.com/kernel/common/+/bcmdhd-3.10/Documentation/dynamic-debug-howto.txt
- https://www.kernel.org/doc/html/v4.19/admin-guide/dynamic-debug-howto.html
- https://wiki.st.com/stm32mpu/wiki/How_to_use_the_kernel_dynamic_debug
- https://www.ti.com/video/5399373110001
- https://www.ti.com/video/series/debugging-embedded-linux-systems-training-series.html
- Linux Kernel Debugging: Going Beyond Printk Messages - Sergio Prado, Embedded Labworks: https://youtu.be/NDXYpR_m1CU
- Debugging the Linux Kernel : https://www.youtube.com/watch?v=7QiR3TOYajY
- Introduction to the Linux Kernel Development: Adding support for debugfs in a Linux Kernel Module: https://youtu.be/TV3zGlz5t1E

### static keys

 - https://www.kernel.org/doc/Documentation/static-keys.txt
 - https://www.kernel.org/doc/html/latest/staging/static-keys.html
 - https://users.rust-lang.org/t/announcing-static-keys-reimplementaion-of-linux-kernels-static-keys-mechanism-for-rust-userland/115060
 - https://github.com/Rust-for-Linux/linux/commit/6e59bcc9c8adec9a5bbedfa95a89946c56c510d9
 - https://github.com/Rust-for-Linux/linux/blame/rust-next/rust/kernel/jump_label.rs
 - https://github.com/Rust-for-Linux/linux/issues/453
 - https://rust.docs.kernel.org/kernel/macro.static_branch_unlikely.html
 - https://rust.docs.kernel.org/next/src/kernel/tracepoint.rs.html
 - https://elixir.bootlin.com/linux/v6.14.7/source/include/linux/dynamic_debug.h#L16

### how git works
 - https://youtu.be/RxHJdapz2p0 - how git works under the hood
 - https://fabiensanglard.net/git_code_review/architecture.php
 - https://fabiensanglard.net/git_code_review/diff.php
 - https://medium.com/geekculture/hows-git-work-the-algorithm-behind-be274f9983da
 - https://youtu.be/suLZU68iCjQ?si=QBqoLRg0CrvWESas
 - https://www.youtube.com/live/DjOk0jnqsLk?si=1i2wR_XTE9MTlG2_


### About bugs in linux

However some subsystems have their own practices. For example DRM and graphic related issue are almost exclusively reported on freedesktop gitlab. If you report bug on Bugzilla, they will ask you to report it there instead. For example for the amdgpu issues:

https://bugzilla.kernel.org/show_bug.cgi?id=200531#c14

### Linux media 

- https://www.kernel.org/doc/html/v4.10/media/index.html
- https://www.chiark.greenend.org.uk/doc/linux-doc-3.2/html/media_api/index.html
- https://www.chiark.greenend.org.uk/doc/linux-doc-3.2/html/media_api/streaming-par.html
- https://www.chiark.greenend.org.uk/doc/linux-doc-3.2/html/media_api/pixfmt.html
- https://www.marcusfolkesson.se/blog/v4l2-and-media-controller/
- https://www.marcusfolkesson.se/blog/capture-a-picture-with-v4l2/
 
