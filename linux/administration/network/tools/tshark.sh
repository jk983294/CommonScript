# install
sudo add-apt-repository ppa:dreibh/ppa
sudo apt-get update
sudo apt-get install wireshark tshark
sudo apt-get install libpcap-dev

# capture
tshark -w mycaptures.pcap                           # capture all
tshark -c 500 -w mycaptures.pcap                    # capture next 500 packets
tshark -a duration:60 -w mycaptures.pcap            # capture 60s
tshark -i wlan0 -w mycaptures.pcap                  # capture interface wlan0

# capture fetch condition
# !!! only for use with a network capture, not for reading from a pcap file
# host                          4 decimal digit dot separated IP address
# net                           a range of 4 decimal digit dot separate IP address
# src                           net from a range of IP addresses
# dst                           to a range of IP addresses
# mask                          to apply to IP address
# arp                           Address Resolution Protocol
# ether proto                   ethernet type field
# ether dst                     ethernet MAC address of destination
# broadcast                     broadcast message across the network
# multicast                     ethernet multicast packet
# tcp port range                hyphen (-) separated range of TCP port numbers
# dst port                      TCP destination port number
# tcp port                      TCP port number
# ip                            all IPv4 traffic
# pppoes                        all PPPoE traffic
# vlan                          all VLAN traffic
# port                          TCP port number
# not                           NOT the following
# and                           logical AND of the two adjacent parameters
# or                            logical OR of the two adjacent parameters
tshark -f "net 192.168.8.0/24"                      # capture packets from/to all network addresses on network 192.168.8.0

# Yank filter
# this can be used both capture or read from file
# frame.time
# frame.time                    relative Relative packet time stamp
# frame.len                     Length of the packet
# frame.protocols               Protocol to which the packet belongs
# frame.number                  Packet number in the data stream
# eth.addr                      6 hex digit colon separated ethernet MAC address
# eth.dst                       6 hex digit colon separated destination MAC address
# ip.addr                       4 decimal digit dot separated IP address
# ip.src                        Sender’s IP address
# ip.dst                        Receiver’s IP address
# ip.len                        length of the IP packet
# tcp.srcport                   TCP source port
# tcp.port                      TCP port number
# tcp.dstport                   TCP destination port
# udp.port                      UDP port number
# col.Info                      Received packet’s content
# http.response.code            HTTP response code number
# &&                            logical AND
# ||                            logical OR
# >                             greater than
# ≥                             greater or equal
# <                             less than
# ≤                             less than or equal
# ==                            equal to
# !                             logical NOT
tshark -Y "ip.addr == 192.168.8.244" -r mycaps.pcap     #  displays packets which from/to IP 192.168.8.244
tshark -Y "ip.src == 192.168.14.5 && ip.len < 1500"

# analysis
tshark -V                                               # verbose
tshark -O icmp                                          # only verbose for icmp
tshark -T fields -e frame.number -e ip.addr             # print ip address

# read a Pcap with Tshark
tshark -V
tshark -r capture-output.pcap
tshark -r cuero_20180720_2.pcap -x | less               # -x show raw content
tshark -r mycaptures.pcap -Y "frame.number == 6" -x     # show number 6 raw message