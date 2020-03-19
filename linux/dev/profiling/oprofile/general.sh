# dynamic program analysis, it consists of a kernel driver and a daemon for collecting data
apt install oprofile

operf ./a.out
opannotate --source         # line by line profile of your code

# Profile With the Linux Kernel
cp /boot/vmlinux-`uname -r`.gz /tmp
gunzip /tmp/vmlinux*.gz
opcontrol --vmlinux=/tmp/vmlinux*

# Profile Without the Linux Kernel
opcontrol --no-vmlinux

opcontrol --start           # Start the OProfile daemon
# start the application you want to profile
opcontrol --stop            # Stop the OProfile daemon
opcontrol --dump            # Dump the collected data to /var/lib/oprofile/samples 
opreport                    # Create a report
opcontrol --shutdown        # Shut down the oprofile daemon
