# packet capture
exanic-capture -H -i enp179s0d1 -w /tmp/exanic_1_kun.pcap

exanic-config
exanic-config exanic0:0 speed 1000          # setting port speed
exanic-config exanic0:0 promisc on          # enable promiscuous mode
exanic-config exanic0:0 bypass-only on      # enable bypass-only mode, tshark will not function correctly while this is enabled

# time synchronize
exanic-clock-sync exanic0:host
exanic-clock-sync exanic0:host exanic1:exanic0
exanic-clock-check exanic0

## exasock
exasock nc -u -l 1234
EXASOCK_DEBUG=1 exasock nc -u -l 1234       # extra debugging information
exasock --debug nc -u -l 1234               # use debug version of libexasock
exasock --trace nc -u -l 1234               # record system calls
exasock --no-warn nc -u -l 1234             # turn off warning messages
exasock --no-auto nc -u -l 1234             # disable acceleration
exasock-stat                                # display accelerated connections

## Transmit preloading
# loading the card with a packet before it is required to be sent, and using a single register write to trigger the packet to be sent. The general idea is to remove the overhead of transferring the packet from the critical path.
