#!/usr/bin/python3
# coding=utf-8
import os
from optparse import OptionParser
import getpass
import CommonUtil as util

# for data visualization
# usgae: python csv2json.py -f /home/kun/Data/ctp/backtest/IF0000_1min.csv


parser = OptionParser()
parser.add_option("-f", "--file", dest="file", help="source csv file")
parser.add_option("-t", "--toFile", dest="toFile", help="target json file")
(options, args) = parser.parse_args()

if not options.file or not os.path.exists(options.file):
    raise Exception("csv file not found!")

columns = {}

with open(options.file, 'r') as f:
    data = f.readlines()

    headers = data[0].encode('utf-8').strip().split(",")
    columnCount = len(headers)
    for itr, val in enumerate(headers):
        val = val.strip("\"")
        columns[val] = []
        headers[itr] = val

    i = 1
    endCount = len(data)
    while i < endCount:
        lets = data[i].encode('utf-8').strip().split(",")

        if len(lets) == 0 or (len(lets) == 1 and lets[0] == ''):
            i += 1
            continue
        elif len(lets) != columnCount:
            raise Exception("format error in line ", i)
        else:
            for itr in range(columnCount):
                columns[headers[itr]].append(lets[itr])

        i += 1

instrument = os.path.splitext(os.path.basename(options.file))[0]
targetFile = ('/home/%s/github/midas/visualization/%s.%s.json'
              % (getpass.getuser(), instrument, util.get_timestamp_str()))
if options.toFile:
    targetFile = options.toFile

result = {'instrumentName': instrument}
columnResult = {}

headerMap = {}
for item in headers:
    if item == 'TotalVolume':
        headerMap['volume'] = 'TotalVolume'
    else:
        headerMap[item.lower()] = item

if 'date' in headerMap and 'time' in headerMap:
    columnResult['times'] = []
    for i, val in enumerate(columns[headerMap['date']]):
        columnResult['times'].append('%s %s' % (val, columns[headerMap['time']][i]))
elif 'date' in headerMap:
    columnResult['times'] = columns[headerMap['date']]
elif 'time' in headerMap:
    columnResult['times'] = columns[headerMap['time']]
else:
    raise Exception("format error no time column found!")

for key, value in headerMap.items():
    if key != 'date' and key != 'time':
        columnResult[key] = util.to_numeric_array(columns[value])

result['columns'] = columnResult

util.serialization_object(targetFile, result)
print("generate json file", targetFile)
