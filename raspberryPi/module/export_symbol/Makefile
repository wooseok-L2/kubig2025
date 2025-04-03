CC = gcc
obj-m := export_symbol_a.o
obj-m += export_symbol_b.o
obj-m += export_symbol_c.o 
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean