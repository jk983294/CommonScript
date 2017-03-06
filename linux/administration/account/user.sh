#!/bin/bash

id                                              # print current id
id jk                                           # print jk id info
less /etc/default/useradd                       # check default add user action (shell, group, home, inactive, expire, skel, create_mail_spool)
# passwd files /etc/passwd /etc/shadow
# 7 fields of /etc/passwd (login name, password encrypted flag, uid, gid, user name, home directory, command interpreter)
# 8 fields of /etc/passwd (login name, encrypted password, date of last password change, minimum password age, maximum password age, password warning period, password inactivity, account expiry day)
# password aging defaults: /etc/login.defs
useradd -D                                      # defaults
useradd jk                                      # add user but won't create home directory immediately
useradd -m bob                                  # create home directory
passwd jk                                       # setup password
pwconv                                          # move password from /etc/passwd to /etc/shadow
pwunconv                                        # opposite way
usermod jk -c "jiangkun"                        # modify user jk's full user name
userdel -r jk                                   # remove user jk and its home directory
