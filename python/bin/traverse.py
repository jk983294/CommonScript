#!/usr/bin/python
# coding=utf-8
import glob2
import os
from optparse import OptionParser
import CommonUtil as util

# usage: python traverse.py -d /tmp/test
# usage: python traverse.py -f /tmp/a.txt


path_prefix = "//##**----------------"


def read_file(path):
    if os.path.isdir(path):
        return
    elif os.path.isfile(path):
        print path_prefix, path
        with open(path, 'r') as f:
            for line in f.readlines():
                print line,


def rebuild(path):
    with open(path, 'r') as rf:
        data = rf.readlines()
        i = 0
        end_count = len(data)
        while i < end_count:
            if data[i].startswith(path_prefix):
                file_path = data[i].strip()[len(path_prefix) + 1:]
                dir_path = file_path[:file_path.rfind('/')]
                print file_path, dir_path
                util.prepare_dir(dir_path)

                i += 1
                with open(file_path, "w") as wf:
                    while i < end_count:
                        if data[i].startswith(path_prefix):
                            break
                        wf.write(data[i])
                        i += 1


parser = OptionParser()
parser.add_option("-d", "--directory", dest="directory", help="directory to play")
parser.add_option("-f", "--file", dest="file", help="file to rebuild")
(options, args) = parser.parse_args()

target_dir = '.'
if options.directory:
    target_dir = options.directory

os.chdir(target_dir)

if options.file:
    rebuild(options.file)
else:
    for fileName in glob2.glob("**/*"):
        read_file(fileName)
