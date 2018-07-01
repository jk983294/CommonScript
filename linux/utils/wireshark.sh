#!/bin/bash

sudo apt-add-repository ppa:wireshark-dev/stable
sudo apt-get update
sudo apt-get install wireshark
sudo dpkg-reconfigure wireshark-common
# “Should non-superusers be able to capture packages?” choose yes

# add user group like wireshark:x:130:kun
sudo vim /etc/group
