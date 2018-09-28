#!/usr/bin/env bash


# for Debian / Ubuntu
# .deb file <=> .rpm
# apt <=> apt
# dpkg-reconfigure
# DPKG database located at /var/lib/dpkg

dpkg -l                                         # list all debs installed on device
dpkg -L vim-tiny                                # list all packages associated with vim-tiny
dpkg -s vim-tiny                                # status of vim-tiny
dpkg -S /etc/vim/vimrc.tiny                     # link the file back to its package
dpkg -i nameof.deb                              # install deb to system
dpkg -r nameofpackage                           # remove deb from system
dpkg-reconfigure packagename                    # re-run configuration wizard if available

apt-get update                                  # update cache to the latest version of .deb
ls /var/cache/apt/archives/
apt-get install vim

# high level package manager
apt-get install aptitude
aptitude install npm

# install services
apt-cache search postfix                        # search cache about postfix
apt-cache pkgname postfix                       # find cache about package name start with postfix
apt-get install postfix

# reconfigure services, re-run the wizard
dpkg-reconfigure postfix

# configure source of apt repository
vim /etc/apt/sources.list
