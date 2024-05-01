obj-m += module_with_command_line_arguments.o

PWD := $(CURDIR)

all:
	 make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
