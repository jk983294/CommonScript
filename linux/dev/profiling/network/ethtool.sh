#!/bin/bash



# RX errors mean that NIC is receiving malformed frames from the transmitting switchport.
# Frame errors mean CRC failures on receipt of a frame. The root cause of this could be a bad cable,
# or a bad interface on either the machine or the switch.

ethtool -S eno1                                 # NIC statistics, packet drop/error details
thtool -S eno1 | grep -i error                  # check NIC error
ethtool eno1                                    # Settings for NIC eno1
ethtool -g eno1                                 # ringbuffer setting
ethtool -k eno1                                 # check feature turn on/off
ethtool -i eno1                                 # driver info
ethtool -t eno1 online                          # test interface without restart, need root permission


ethtool -A tx off eno1                          # stop module transmit data
ethtool -K eno1 rx off                          # turn off CRC check
ethtool -p eno1 10                              # check eno1 in which NIC, it will blink
ethtool -s eno1 speed 100                       # downgrade send speed
