#KERNELDIR=/home/haoli/workspace/linux_src/linux-stable
#KERNELDIR=/usr/src/linux-headers-3.13.0-49
KERNELDIR=/usr/src/linux-headers-$(shell uname -r)
obj-m:=hello.o


PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
