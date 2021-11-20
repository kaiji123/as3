KERNELDIR=/lib/modules/`uname -r`/build
#ARCH=i386
#KERNELDIR=/usr/src/kernels/`uname -r`-i686

EXTRA_CFLAGS += -I$(PWD)
MODULES = charDeviceDriver.ko 
obj-m += charDeviceDriver.o 


all: $(MODULES)

charDeviceDriver.ko: charDeviceDriver.c
	make -C $(KERNELDIR) M=$(shell pwd) modules

clean:
	make -C $(KERNELDIR) M=$(shell pwd) clean
	rm -f *.o *.o.rc


