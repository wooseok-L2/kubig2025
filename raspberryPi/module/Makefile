CC = gcc
obj-m := module_exam.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm -f *.ko
	rm -f *.o
	rm -f *.mod.*
	rm -f .*.cmd