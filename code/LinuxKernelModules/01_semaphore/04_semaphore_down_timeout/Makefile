obj-m += semaphore_04.o

PWD := $(CURDIR)

all:
	 make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
