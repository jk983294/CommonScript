#!/usr/bin/env bash

# Permission: Read / Write / Execute
# Permission: sticky bit, it allow user to access directory, delete his own files but cannot delete others' files
# Entity: User / Group / Others(everyone else)
# symbolic notation: RWX / RW- / R--
# octal notation:     7  /  6  /  4
# directory need execute perm to enter the folder
# delete a file perm:
# 1. the file is owned by the user, so the user could delete it
# 2. the user could delete other user's file if he have x perm of folder


ls -l file1                                             # check perm
ls -ld /data/                                           # check perm for directory
ls -ld /tmp                                             # by default, you can only delete files you own under /tmp
stat file1                                              # check perm

chmod 777 file1                                         # change perm to rwxrwxrwx
chmod u=rwx,g=rwx,o=rwx file2                           # change perm to rwxrwxrwx
chmod +rx file3                                         # give U/G/O group all read and execute permission, this is still under umask control
chmod o+t /data/                                        # give /data/ folder stick bit, so now can not delete files owned by others under /data/ folder

chgrp users /data/                                      # change /data directory group to users

umask                                                   # show current file mode creation mask
umask 0                                                 # set file mode creation mask to 0, then default perm is rw-rw-rw-
umask 077                                               # set file mode creation mask to 0, then default perm is rw-------
umask 002                                               # default umask
