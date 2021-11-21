mknod /dev/opsysmem c 246 0
sleep 3
echo "hello" > /dev/opsysmem
sleep 3
echo "hi" > /dev/opsysmem
sleep 3
echo "cia" > /dev/opsysmem
sleep 2
head -n 1 /dev/opsysmem
sleep 2
head -n 1 /dev/opsysmem
sleep 1
dmesg > log.txt
