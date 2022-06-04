#!/bin/bash
echo EBB-PRU-RTC4 > /sys/devices/bone_capemgr.9/slots
stty -echo
. ~/.bash_profile
