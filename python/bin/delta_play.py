#!/usr/bin/python
# coding=utf-8
import glob2
import os
import gzip
from optparse import OptionParser
import CommonUtil as util

# usage: python delta_play.py -d /home/kun/Data/ctp/raw_msg_log -s 20171027.131659 -e 20171027.133221

s, e = (0, 0)
isIoErrorOccur = False


def filter_files_by_time(files):
    if len(files) == 0:
        return []

    files.sort()
    times = []
    si, ei = (0, len(files) - 1)

    for i, f in enumerate(files):
        current_time = float(f[:-3])
        times.append(current_time)
        if s != 0 and s > current_time:
            si = i

        if e != 0 and e >= current_time:
            ei = i

    if e and e < times[0]:
        ei = -1
    return files[si:ei + 1]


def read_gz_file(path):
    with gzip.open(path, 'rt') as pf:
        try:
            for line in pf:
                if line:
                    tick = util.parse_midas_format(line)
                    if tick and tick['rcvt']:
                        t = float(util.ntime2float_string(tick['rcvt']))
                        if (s == 0 or s <= t) and (e == 0 or e >= t):
                            print line,
        except IOError as err:
            isIoErrorOccur = True

parser = OptionParser()
parser.add_option("-d", "--directory", dest="directory", help="directory to play")
parser.add_option("-s", "--start", dest="start", help="start time to play")
parser.add_option("-e", "--end", dest="end", help="end time to play")
(options, args) = parser.parse_args()

target_dir = '.'
if options.directory:
    target_dir = options.directory

if options.start:
    s = float(options.start)

if options.end:
    e = float(options.end)

os.chdir(target_dir)
fileNames = glob2.glob("*.gz")

for fileName in filter_files_by_time(fileNames):
    read_gz_file(fileName)
