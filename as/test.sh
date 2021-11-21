rmmod charDeviceDriver
rm /dev/opsysmem
make
insmod charDeviceDriver.ko
mknod /dev/opsysmem c 237 0
echo "hello" > /dev/opsysmem
echo "france" > /dev/opsysmem
dmesg
