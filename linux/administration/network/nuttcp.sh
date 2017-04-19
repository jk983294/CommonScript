#!/bin/bash

# network performance measurement tool
# -lbuffer_len      sender/receiver buffer size
# -nnum_bufs        source data to transmit
# -wwindow_size     sets the sender or receiver TCP socket buffer size
# -u                Use UDP instead of the default of TCP
# -R                transmitter rate limit throttles the speed at which the transmitter sends data to the network
# -Ri               restrict the instantaneous rate at any given point in time

# server
nuttcp -S

# client
nuttcp 192.168.1.100                            # good for a relatively close host
nuttcp -w6m <host>                              # good for a cross-country link
nuttcp -u -i -Ri50m <host>                      # good for checking on packet loss
nuttcp -w1m 127.0.0.1                           # check internal capability
nuttcp -w1m ::1                                 # check internal capability
nuttcp -u -Ri300m/20 -i 1 -T5 127.0.0.1         # send 300 Mbps of UDP in bursts of 20 packets for 5 seconds
nuttcp -n1G -l1500 192.168.1.100
