#!/usr/bin/python3
# coding=utf-8
import sys
from optparse import OptionParser
import CommonUtil as util

# usage: python field_extract_facility.py -f tp,ts,bap,bbp -t 1


parser = OptionParser()
parser.add_option("-f", "--fields", dest="fields", help="fields to extract")
parser.add_option("-t", "--time_type", dest="time_type",
                  help="time type (1. ntime rcvt)")
(options, args) = parser.parse_args()

time_type = 1
if options.time_type:
    time_type = int(options.time_type)

has_fields2extract = False
fields = {}
if options.fields:
    has_fields2extract = True
    for field in options.fields.split(','):
        fields[field] = field

for line in sys.stdin:
    line = line.strip()
    if line:
        tick = util.parse_midas_format(line)
        t = ''
        content = ''
        if time_type == 1:
            t = util.ntime2timestamp_string(tick['rcvt'])
        elif time_type == 2:
            t = ("%s.%s" % (tick['ut'], tick['um'].zfill(3)))

        if not has_fields2extract:
            print("%s ,%s" % (t, line))
        else:
            for key, value in tick.items():
                if key in fields:
                    content += (' %s %s,' % (key, value))

            print("%s ,%s;" % (t, content))
