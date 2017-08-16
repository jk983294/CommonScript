#!/bin/bash

sudo apt install vsftpd
vsftpd /etc/vsftpd/vsftpd.conf &

ftp 192.168.31.112                          # login in with user name and password
# ftp command
cd Downloads                                # remote directory now /home/jk/Downloads
lcd Downloads                               # Local directory now /home/kun/Downloads

ls                                          # show remote directory
!ls                                         # show local directory

get test.txt ./Downloads/test.txt           # get remote file to local file
mget *.txt                                  # get all remote file end with txt download to current directory

put ./Downloads/test.txt /tmp/test1.txt     # upload local file to remote file
mput ./Downloads/*.txt                      # upload all local file end with txt to remote file

delete ./Downloads/*.txt                    # remove all remote file end with txt

bye                                         # disconnect
