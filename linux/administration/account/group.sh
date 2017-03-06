#!/bin/bash

# /etc/group (group name, password, gid, user list)
# /etc/gshadow (group name, encrypted password, admin list, members)

gpasswd -M kun,jk sudo                      # change memebr of sudo group
gpasswd sales                               # setup password for group sales
newgrp sales                                # temporarily join group sales, need sales group password, this is not permenant

groupadd sales                              # add group sales
groupmod -G sudo,adm,sales kun              # add kun to group sudo and adm
groupdel sales                              # delete group sales
