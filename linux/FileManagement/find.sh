#!/usr/bin/env bash

locate pcap.h

# -user <user name>
# -group <group name>
# -perm [-] <octal number>
# -atime [+|-] <days>
# -mtime [+|-] <days>
# -ctime [+|-] <days>
# -type [d|f|l]
# -inum <i-node number>

# action
find . -newer file1 -print
find . -newer file1 -delete                                             # delete all files newer than file1
find . -newer file1 -type f -delete                                     # only delete regular files, not directory
# {} is place-hold of found files, \; means the end of the command(mandatory)
find . -name '*.conf' -exec ls -lh {} \;                                # search and then show me long list information

# search by name
find . -name '*.conf'
find . -not -name "*.html"                                              # find all files not ending in ".html"
find . \( -name "*.c" -o -name "*.sh" \)                                # *.c and *.sh files
find . \( -name "*cache" -o -name "*xml" -o -name "*html" \)            # three patterns
find . -iname foo                                                       # case-insensitive, foo, Foo, FOo, FOO, etc.

# search multiple dirs
find /opt /usr /var -name foo.scala -type f                             # search multiple dirs

# search by time
find . -newer file1                                                     # find all files newer than file1 in current folder
find . -mtime 1                                                         # modification time 24 hours
find . -mtime -7                                                        # modification time last 7 days

# search with depth
find . -maxdepth 1 -name '*.conf'

# search by file type
find . -type d                                                          # find directory

# search by size
find . -size +142k                                                      # find files which size bigger than 142k
find . -size -142k                                                      # find files which size less than 142k

# group
find / -atime +90 -size +200 -print
find . -user root -perm -4000 -print
