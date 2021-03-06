#!/usr/bin/env bash

# tar for archive
# c     create a new archive
# C 	relative path
# v     verbose
# f     use archive file
# z     compress with gzip
# j     compress with bzip, more compression ratio than gzip
# t     test
# x     expand archive file, extract files out

tar -cvf etc.tar /etc                       # archive etc config folder
tar -czvf etc.tgz /etc                      # archive with compress
tar -cjvf etc.tar.bz /etc                   # archive with compress

# expand
tar -xvf etc.tar
tar -xzvf etc.tgz
tar -xjvf etc.tar.bz

# relative path
mkdir foo
tar -xzf bar.tar.gz -C foo # expand to relative path foo
to_archive_path=/a/b/c/to_archive
to_archive_dir=$(dirname "$to_archive_path")
to_archive_base=$(basename "$to_archive_path")
tar -czvf /tmp/archive.tgz -C $to_archive_dir $to_archive_base   # archive to relative path

# check size of the archive
ls -lh etc.t*
du -sh /etc

# measure the archive process with/without compress
time tar -cvf etc.tar /etc
time tar -czvf etc.tgz /etc
time tar -cjvf etc.tar.bz /etc

# print out the content of archived files
tar -tf etc.tar
tar -tzf etc.tgz
tar -tjf etc.tar.bz

# check tar file type
file etc.tar                                # POSIX tar archive (GNU)
file etc.tgz                                # gzip compressed data
file etc.tar.bz                             # bzip2 compressed data, block size = 900k

# remove all unziped files
/bin/rm -f "$(tar ztf /path/to/file.tar.gz)"
