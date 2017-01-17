from shutil import *
from glob import glob

# a number of high-level operations on files and collections of files

copytree('example', '/tmp/example')
rmtree('/tmp/example')
move('example.txt', 'example.out')                              # move a file or directory from one place to another
copyfile('shutil_copyfile.py', 'shutil_copyfile.py.copy')
copy('shutil_copy.py', 'folder')                                # copy to folder/shutil_copy.py
copy2('shutil_copy2.py', 'folder')                              # the access and modification times in the meta-data copied to the new file
copymode('shutil_copymode.py', 'file_to_change.txt')            # copy the permissions from one file to another
copystat('shutil_copystat.py', 'file_to_change.txt')            # copy other meta-data about the file (permissions, last access time, and last modified time)
