#!/usr/bin/python
# coding=utf-8
import glob
import os
import sys

# usage: python traverse.py -d /tmp/test

path_prefix = "//##**----------------"


def ignore_file(fileName):
    return fileName.endswith(".png") or fileName.endswith(".jpeg") or fileName.endswith(".pdf") \
                or fileName.endswith(".so") or fileName.endswith(".pyc") or fileName.endswith(".gch") \
                or fileName.endswith(".iml")


def loop_dir(fileName):
    return fileName.endswith(".") or fileName.endswith("..")


def read_file(path):
    for fileName in glob.glob(path + '/*'):
        if os.path.isdir(fileName) and not loop_dir(fileName) and fileName != path:
            read_file(fileName)
        elif os.path.isfile(fileName) and not ignore_file(fileName):
            print path_prefix, fileName
            with open(fileName, 'r') as f:
                for line in f.readlines():
                    print line,


target_dir = '.'
if len(sys.argv) == 3:
    target_dir = sys.argv[2]

os.chdir(target_dir)

read_file(".")
