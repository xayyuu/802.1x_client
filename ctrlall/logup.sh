#!/bin/bash
# set -x
echo "THIS IS A CONTROL USED SHELL SCRIPT"
echo -n "PLEASE INPUT YOUR CHOICSE: up, down:    "
read CMD_CHOICE


if [ "$CMD_CHOICE" = "up" ]
then 
./house_ctrl -on
./house_ctrl -on
./house_ctrl -on

sleep 3
echo "NEXT STAGE: DHCP DISCARD IP ADDRESS"
sudo dhclient eth0
echo "LOGON SUCCESS, NOW ENJOYING THE SURFING ON THE INTERNET"

elif [ "$CMD_CHOICE" = "down" ] 
then
./house_ctrl -over
sudo dhclient -r  eth0
echo "LOGFF, CANNOT SURFING NOW"

else
echo "YOUR INPUT IS WRONG FORMAT, PLEASE CHECK IT"
fi
