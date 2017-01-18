#!/usr/bin/env bash

# Yum (Yellow dog Updater, Modified)
# repository management for RPM

yum install nmap
yum -y remove nmap                  # -y no prompt
yum info nmap
yum list                            # show all available
yum list installed                  # show all installed
yum search nmap
yum grouplist


# yum shell
info nmap
install nmap            # setup transaction
ts                      # show transaction
run                     # run transaction
quit

# yum script as below, script named yum.cmds
install zsh
remove nmap
run

# run with script
yum shell yum.cmds
yum -y shell yum.cmds               # no prompt

# repository management
# copy rpm file into your local repo folder
# make that folder a repository of yum
# install that rpm package
mkdir /repo
mv /home/jk/Downloads/FoxitReader-1.1.0.rpm /repo
ls /repo
yum install createrepo
createrepo /repo                    # create a repository, repodata will be generated
ls /repo/                           # you should see repodata
cd /etc/yum.repos.d/
ls
cp CentOS-Media.repo local.repo
vim local.repo
# baseurl=file:///repo
yum repolist                        # show all yum repository
yum search Fox                      # should see FoxitReader-1.1.0
yum install FoxitReader-1.1.0