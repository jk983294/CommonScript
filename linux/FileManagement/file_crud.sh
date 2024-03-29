#!/usr/bin/env bash

# clean file, especially for big file
cat /dev/null > somefile

# temp file
mktemp test.XXXXXX                  # under current directory
mktemp -t test.XXXXXX               # under /tmp/
mktemp -t test.XXXXXX               # create tmp directory

# create file
touch file1                         # create file1

mkdir /a
mkdir -p /a/b/c                     # make parent directories as needed
mkdir -p /a/b/{c,d}                 # make two directories

# copy
cp file1 file5                      # copy file1 to file5, the permission is the user who issue the command
cp -a file1 file6                   # retain the permission of source file, archive mode
cp file1 ..                         # copy file1 to parent directory
cp -i file1 ..                      # copy with interaction if the same file already exist
cp -p file1 ..                      # copy and perserve permission
cp -i file* ..                      # copy all files start with file to parent directory
cp -R files/ backup/                # copy files folder to backup folder recursively
echo /dir1 /dir2 /dir3 | xargs -n 1 cp -v path_src              # copy tocopy to several destinations
git show sha --name-only | grep pattern | xargs -I{} cp {} path_dest

# move and rename
mv file5 filenewname                # rename
mv filenewname ../                  # move file to parent directory

# list
# file type: d directory, l link, p pipe
ls                                  # list all files under this directory
ls -l                               # long list
ls -lt                              # order by modified time from most recent
ls -ltr                             # reverse order by modified time
ls -1tr                             # show latest file first, each file one line
ls -F                               # list with file type, / directory, @ link, * executable, | pipe
ls --color=auto                     # list with color, dark blue directory, light blue link, green executable
ls -R backup/                       # list recursively backup folder

# remove
rm file1
rm -i file1                         # remove with interaction mode
rm -i file*                         # remove all files start with file with interaction mode
rmdir test/                         # remove test folder, test MUST be empty
rm -ri test/                        # remove test folder with asking
rm -rf test/                        # recursive and force, remove all file under test folder and test folder itself

# dd        duplicate disk, image, create file with certain bytes, backup file, complete disks
# backup /dev/sda MBR 512 byte in case partition table etc. data lost
dd if=/dev/sda of=/data/file count=1 bs=512
# clear MBR
dd if=/dev/zero of=/dev/sda count=1 bs=512
# recover MBR from backup
dd if=/data/file of=/dev/sda count=1 bs=512
