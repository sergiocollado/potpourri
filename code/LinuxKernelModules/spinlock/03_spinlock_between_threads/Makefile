obj-m += spinlock_03.o

PWD := $(CURDIR)

all:
	 make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
