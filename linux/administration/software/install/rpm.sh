#!/usr/bin/env bash

# .rpm files for Red Hat / Fedora / CentOS
rpm -qa                             # list all installed on device
rpm -i nameof.rpm                   # install
rpm -e nameofpackage                # remove from system
rpm -qpi nameofpackage              # query/package/information
rpm -ql cmd                         # query the rpm database
rpm -qf $(which nmap)               # query the file belong to which rpm file
rpm -qpl nameofpackage              # query/package/list all files it contains
rpm -i !$                           # install with last cmd's option


# YUM install from a repository without having to know the path to the file or dependencies
yum install packagename