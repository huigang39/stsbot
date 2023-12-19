#!/bin/sh

echo 'KERNEL=="ttyUSB*", ATTRS{idVendor}=="1a86", ATTRS{idProduct}=="7523", MODE:="0666", GROUP:="dialout",  SYMLINK+="ttyUSB_ARDUINO"' > /etc/udev/rules.d/ch34x.rules
echo 'KERNEL=="ttyUSB*", ATTRS{idVendor}=="10c4", ATTRS{idProduct}=="ea60", MODE:="0666", GROUP:="dialout",  SYMLINK+="ttyUSB_LIDAR"' > /etc/udev/rules.d/rplidar.rules

service udev reload
sleep 2
service udev restart

echo "finish"
