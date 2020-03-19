# The Precision Time Protocol (PTP)
# PTP follow a master-slave hierarchy. The slaves are synchronized to their masters
apt install linuxptp
ethtool -T enp0s3               # check NIC timestamp ability (SOF_TIMESTAMPING_SOFTWARE|SOF_TIMESTAMPING_RAW_HARDWARE)
ptp4l -m -i enp0s3              # enable by hardware timestamp
ptp4l -m -S -i enp0s3           # enable by software timestamp

systemctl start ptp4l           # run as service
systemctl enable ptp4l
systemctl disable ptp4l

# Synchronizing the Clocks with phc2sys
phc2sys -s enp0s3 -w
phc2sys -s eth0 -O -35          # with offset
systemctl start phc2sys
systemctl enable phc2sys
systemctl disable phc2sys