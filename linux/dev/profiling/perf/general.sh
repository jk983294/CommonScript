#!/usr/bin/env bash

perf buildid-list -i perf.data      # get build id

# install
git clone https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
git clone https://github.com/torvalds/linux.git
cd linux/tools/perf
make
cp perf /usr/bin

# perm
sudo sh -c 'echo 1 >/proc/sys/kernel/perf_event_paranoid'
sudo sh -c 'echo kernel.perf_event_paranoid=-1 > /etc/sysctl.d/local.conf'
$ grep perf_event_paranoid /etc/sysctl.conf
kernel.perf_event_paranoid = -1
