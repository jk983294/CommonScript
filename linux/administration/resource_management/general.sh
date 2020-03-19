# Partitioning
# Disperse simultaneous read and write access onto different disks by:
#       using separate disks for the operating system, data, and log files
#       placing a mail server's spool directory on a separate disk
#       distributing the user directories of a home server between different disks

# NFS tune: increase the read write blocksize to 32768 by using the mount options wsize and rsize