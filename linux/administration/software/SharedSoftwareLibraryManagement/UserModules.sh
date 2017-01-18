#!/usr/bin/env bash

ldd /bin/ls                                             # list shared libraries for ls
ldd $(which useradd)

less /etc/ld.so.conf.d/libc.conf
ldconfig                                                # rebuild, configure dynamic linker run-time bindings
ldconfig -p                                             # print rebuild info

# make my /testlibs/librt.so.1 replace system librt.so.1
# LD_LIBRARY_PATH, this variable used to indicate the location of shared libraries other than default path
mkdir /testlibs
cp /lib/i386-linux-gnu/librt.so.1 /testlibs/
export LD_LIBRARY_PATH=/testlibs/
echo $LD_LIBRARY_PATH
unset LD_LIBRARY_PATH                                   # revert the linker


