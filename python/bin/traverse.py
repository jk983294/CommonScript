#!/usr/bin/python
# coding=utf-8
import glob2
import os
from optparse import OptionParser

# usage: python traverse.py -d /tmp/test


def read_file(path):
    if os.path.isdir(path):
        return
    elif os.path.isfile(path):
        print "//##**----------------", path
        with open(path, 'r') as f:
            for line in f.readlines():
                print line


parser = OptionParser()
parser.add_option("-d", "--directory", dest="directory",
                  help="directory to play")
(options, args) = parser.parse_args()

target_dir = '.'
if options.directory:
    target_dir = options.directory

os.chdir(target_dir)

for fileName in glob2.glob("**/*"):
    read_file(fileName)
