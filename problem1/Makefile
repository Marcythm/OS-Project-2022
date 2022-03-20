# Android Module Makefile for ptree.c
obj-m := ptree.o

KDIR := ~/Downloads/kernel/goldfish
CROSS_COMPILE=arm-linux-androideabi-
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld

all:
	make -C $(KDIR) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) M=$(shell pwd) modules

clean:
	rm -rf *.ko *.o *.mod.c *.order *.symvers
