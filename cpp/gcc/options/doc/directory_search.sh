-Idir                           # add the directory dir to the head of the list of directories to be searched for header files.
-Ldir                           # add directory dir to the list of directories to be searched for ‘-l’.
-Bprefix                        # specifies where to find the executables, libraries, include files, and data files of the compiler itself.
--sysroot=dir                   # compiler normally searches for headers in ‘/usr/include’ and libraries in ‘/usr/lib’, it instead searches ‘dir/usr/include’ and ‘dir/usr/lib’
-Wl,-rpath=/tmp/lib -L/tmp/lib
