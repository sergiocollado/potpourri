 - reference: https://gist.github.com/RockDeng110/d19d97534a34c971183327a11a466b91

## Why Vim
* Efficiency
* It's everywhere
* Free and open source
* Always available in Embedded system
* Very customizable and extensible

## cscope 
Cscope is a deveoper's tool for browsing source code. In April 2000, the code for cscope was open sourced under the BSD license. 

**Features**
* llows searching code for:
all references to a symbol
global definitions
functions called by a function
functions calling a function
text string
regular expression pattern
a file
files including a file
* Curses based (text screen)
* An information database is generated for faster searches and later reference
* The fuzzy parser supports C, but is flexible enough to be useful for C++ and Java, and for use as a generalized 'grep database' (use it to browse large text documents!)
* Has a command line mode for inclusion in scripts or as a backend to a GUI/frontend
* Runs on all flavors of Unix, plus most monopoly-controlled operating systems.

**Using cscope with Vim**
Please refer to http://cscope.sourceforge.net/cscope_vim_tutorial.html

**Custimize generating cscope.files**
- [this](http://cscope.sourceforge.net/large_projects.html) is the official tutorial for using cscope in a large project like linux kernel. It's a good reference material, except the find instructions for generating cscsope.files manully.
- And there is a better [method](https://stackoverflow.com/questions/33676829/vim-configuration-for-linux-kernel-development) to generate cscope.files manually.
- code sample in generate_cscope_files.sh
```sh
CSF=cscope.files
SOURCE_FILE_TYPE="*.[chxsS]"
MAKE_FILE_TYPE="*Makefile"
DTS_FILE_TYPE="*dts"
DTSI_FILE_TYPE="*dtsi"
NAME_VALUE="-name ${SOURCE_FILE_TYPE} -o -name ${MAKE_FILE_TYPE} -o -name ${DTS_FILE_TYPE} -o -name ${DTSI_FILE_TYPE}"

find    $dir                                          \
        -path "$dir/arch*"               -prune -o    \   
        -path "$dir/tmp*"                -prune -o    \   
        -path "$dir/Documentation*"      -prune -o    \   
        -path "$dir/scripts*"            -prune -o    \   
        -path "$dir/tools*"              -prune -o    \   
        -path "$dir/drivers*"            -prune -o    \   
        -path "$dir/include/config*"     -prune -o    \   
        -path "$dir/usr/include*"        -prune -o    \   
        -type f                                       \
        \( $NAME_VALUE \) -print > $CSF    

find    $dir/arch/arm                                 \
        -path "$dir/arch/arm/mach-*"     -prune -o    \   
        -path "$dir/arch/arm/plat-*"     -prune -o    \   
        -path "$dir/arch/arm/configs"    -prune -o    \   
        -path "$dir/arch/arm/kvm"        -prune -o    \   
        -path "$dir/arch/arm/xen"        -prune -o    \   
        -type f                                       \
        \( $NAME_VALUE \) -print >> $CSF    

find    $dir/arch/arm/mach-imx/                       \
        -type f                                       \
        \( $NAME_VALUE \) -print >> $CSF    

find   $dir/drivers/tty/serial*                       \
        -type f                                       \
        \( $NAME_VALUE \) -print >> $CSF    

```

**Generate cscope database**
```
cscope -kbq
```

**Use cscope in vim**
* Please run :cs help in vim for reference
*  Trick used to find structure declaration in kernel:
```
:cs f t struct device {
```
*  while vim is openning and cscope database has updated, should implement ":cs reset" to update cscope database in vim


## Ctags
Ctags was originally built into Vim, but with the release of Vim version 6, ctags became a separate project. Vim's ctags support allows us to navigate around a codebase by quickly jumpint ot definitions of functions and classes.

**Install ctags**
```sh
$sudo apt-get install exuberant-ctags
```

**Generate tags**
```sh
$ctags -R
```
or
```sh
$ctags -L cscope.files
```

**Navigate keyword in Vim**
<C-]>

**What VIM looks like after some plugins installed**
![](https://user-images.githubusercontent.com/28182184/204247679-d46541ed-3379-4c2b-b81b-3b49a9143c1f.png)

## VIM:advanced
### Customize your vim
```sh
set tabstop=4       :set tab width to 4 spaces
set shiftwidth=4   :set indent also to 4 spaces
set autoindent      :use indentation of previous line
set smartindent    :use intelligent indentation for c
set scrolloff=10    :keep at least 10 lines below and above cursor
syntax on              :turn syntax highlighting on
```
**.vimrc file**
When vim runs, it will implement commands in .vimrc file, so putting your settings in the .vimrc file is a better choice than manually input them at command-line mode. In addition, you can backup your vimrc file via git/github for continous improving your custermizing and easy portting your settings in any device where runs vim.

* For my vimrc file, please refer to https://github.com/RockDeng110/dotfiles

### Plug-ins
* How to install plug-ins
Download plug-ins and put them in ~/.vim/plugin


## VIM:basic and core usage
First of all, if you have to look down to find keys on the keyboard, the benefits of learning vim won't come fast. So please learn to touch tpye first, then learn vim.[1]

Secondly, just install newest version of vim in your system and start it from the shell by type vim. If you have never used vim before, you might not even know how to start edit in it. But don't be panic, just tpye :help jump to vim help system where you can learn the basics of vim. Actually you can learn almost every thing about vim from this its help documentation, try to make friend with it.

Till now, you've done first step to leran vim, which include installing it, running it and trying to edit a file just like using other editors. And then, you need practice it every day, because vim is a whole different editor to any others. It has a very special philosophy and you need do a lot of practice to get familliar with it. From my experience, the best tool for daily vim exercise for a very beginner is the vimtutor which is a wonderful vim tutorial just as its name. Vimtutor will installed along with vim installing, so please just start it as you start vim.
![](https://user-images.githubusercontent.com/28182184/148158126-d5f87b36-4d10-4936-aba4-585a60278424.jpg)


There are 7 lesons in the version 1.7 of Vim tutor as above. For the next month, you should practice it at least half an hour a day every day. Completed those exercise, you will be ready jump to next level.

### MODES
Vim can works at 4 different modes. Same keystroke in different mode have different meaning and could result in different action. Let's talk about those modes.

#### Normal mode
**Operator + Motion = Action**

Operatior: Operators are generally used to delete or change text.
```sh
c : change

d : delete

y : yank/copy

> : shift right

< ：shift left
```

Motion: A command that moves the cursor.
```sh
w : to the start of next word

b : to begin of current word

4j : 4 lines down

/The<CR> : to next occurrence of "The"
```

Examples:
```sh
daw : delete a word

ciw : change inner word

y2w : yank 2 words

4dd : delete 4 lines

3> : shift right 3 times
```

**The dot command: Repeat the last change. The most powerfull and versatile command in vim.**



#### Insert mode
Insert mode commands
```sh
a :  Append text after the cursor

A : Append text at the end of the line

i : Insert text before the cursor.

I : Insert test before the first non-blank in the line.

o : Begin a new line below the cursor and insert text.

O : Begin a new line above the cursor and insert test.
```

paste from a register without leaving inser mode
```sh
<C-r>{register}
```

Go back to normal mode
```sh
<Esc> : Switch to normal mode

<C-[> : Switch to normal mode
```

Many vim users just remap the Esc button to Caps Lock for better experience. I prefer remap jk && kj to <Esc>, then quick clicking jk or kj wil get back to normal mode. To implement that, please refer the settings in the .vimrc as below.
```sh
imap jk <esc>

imap kj <esc>
```
**Build-in autocompletion feature**
 Press Ctrl-N to start
```sh
<C-n> 
```

#### Visual mode
Commands
```sh
v : Enable character-wise Visual mode

V : Enable line-wise Visual mode

<C-v> Enable block-wise Visual mode

<Esc> / <C-[> : Switch to norma mode

v / V <C-v> : Switch to Normal mode

v2w : Switch to visual mode and select 2 words.
```
          
Usage
Comment continous lines in c source file.
```sh
yyp Vr- : Add a line of dash
```

#### Command line mode
**commands**
```sh
:[rangs]delete[x]  : Delete specified lines [into register x]

:[range]yank[x] : Yank specified line 

:[line]put[x] : Put the test from register x after the specified line

:[range]substitue/{pattern}/{string}/[flags] : Replace occurrences of \{pattern} with \{string} on each specified line

:tabnew : create new table

:split : split windows

:bN : switch to Nth buffer

:ls : list buffers
```
          
**Usages**
Use <Tab> key to autocomplete commands at the prompt.
Recall commands from history by using <Up> and <Down>.
Run commands in the shell. :!{cmd}  : Execute {cmd} with the shell
Substitute: 
replace "printk(KERN_DEBUG " with "PE_INTERNAL_DEBUG" in the range of whole file and manually chech every substitution.
```sh
:%s/printk(KERN_DEBUG /PE_INTERNAL_DEBUG(/gc
```
or you can implement substitution as above in multiple files by implement bash commands as below, which implement the substitution in all c files found by find command.
```sh
find . -type f -name "*.c" -exec sed -i 's/printk(KERN_DEBUG /PE_INTERNAL_DEBUG(/g' {} +
```      

### Manage multiple files
**Track open files with the buffer list**
```sh
:ls : liset buffers

:bnext : Go to next buffer in the buffer list

:bprev : Go to previous buffer in the buffer list
```
          
**Delete mutiple buffers**
```sh
:bdelete N1 N2 N3 : 

:N,M bdelete
```

**Divide your workspace into split windows and tabs**
```sh
:vsp[lit]{file} : Split the current window vertically, loading {file} into the new window.

:sp[lit]{file} : Split the current window horizontally, loading {file} into the new window.

<C-w>l/h/j/k : Focus the window to the right/left/below/above

:tabnew : Create a new tab page

gt : Swith to the next tab page

gT: Swith to the previous tab page
```

**Tips:**

Delete trailing white spaces 

:%s/\s\+$//g

[count] sections forward or to the next '{' in the first column. Use it going to start of the function where your cursor currently at

[[

[cont] sections backward or to the previous '}' in the first column. Use it going to start of next function

]]
