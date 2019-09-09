#!/usr/bin/python3
# coding=utf-8
import glob2
import os
from optparse import OptionParser

# usgae: python beauty.py -d ~/cpp
# usgae: python beauty.py -d ~/github/midas/


def beautify_with_pattern(p):
    for fileName in glob2.glob(p):
        print("clang-format -i %s" % fileName)
        os.system("clang-format -i %s" % fileName)


parser = OptionParser()
parser.add_option("-d", "--directory", dest="directory",
                  help="directory need beautify")
(options, args) = parser.parse_args()

target_dir = '.'
if options.directory:
    target_dir = options.directory

print("target dir:", target_dir)

os.chdir(target_dir)
beautify_with_pattern("./**/*.h")
beautify_with_pattern("./**/*.cpp")
beautify_with_pattern("./**/*.inl")
