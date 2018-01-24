#!/usr/bin/python
# coding=utf-8
import glob
import tarfile
import os.path
import os
import pandas as pd
import jsonpickle
import datetime
import time
import logging
from collections import OrderedDict


def get_dataframe_from_file(file_path, dt=None):
    if os.path.isfile(file_path):
        return pd.read_csv(file_path, dtype=dt)
    else:
        return None


def save_dataframe(df, path, error_msg):
    if df is None or df.empty:
        print 'error:', error_msg
    else:
        df.to_csv(path, encoding='utf-8')
        print "download success", path
        # time.sleep(2)


def serialization_object(serialization_path, obj):
    f = open(serialization_path, 'w')
    f.write(jsonpickle.encode(obj).encode('utf-8'))
    f.close()


def deserialization_object(serialization_path):
    if os.path.exists(serialization_path):
        f = open(serialization_path, 'r')
        obj = jsonpickle.decode(f.read())
        f.close()
        return obj
    else:
        return None


def date_str2cob(date_str):
    date_time = datetime.datetime.strptime(date_str, '%Y-%m-%d')
    return int(date_time.strftime('%Y%m%d'))


def timestamp2date_str(timestamp):
    date_time = datetime.datetime.fromtimestamp(timestamp)
    return date_time.strftime('%Y-%m-%d')


def cob2date(cob):
    date_time = datetime.datetime.strptime(str(cob), '%Y%m%d')
    return date_time.strftime('%Y-%m-%d')


def get_timestamp_str():
    return time.strftime("%Y%m%d_%H%M%S", time.localtime())


def month_count(year, month):
    return (year - 1970) * 12 + month - 1


def count2month(count):
    year = int(count / 12) + 1970
    month = count % 12 + 1
    return year, month


def quarter_count_from_month_count(count):
    year, month = count2month(count)
    quarter = int((month - 1) / 3) + 1
    return quarter_count(year, quarter)


def quarter_count(year, quarter):
    return (year - 1970) * 4 + quarter - 1


def count2quarter(count):
    year = int(count / 4) + 1970
    quarter = count % 4 + 1
    return year, quarter


def contains(source, pattern):
    return pattern in source


def array_contains(source, patterns):
    for pattern in patterns:
        if pattern in source:
            return True
    return False


def prepare_dir(dir_name):
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)

# def get_all_stock_codes():
#     client = MongoClient("mongodb://localhost:27017")
#     db = client.prod
#     names = db.StockMisc.find_one({"_id": "AllStockNames"})
#     return names['stockNames']


def last_year_of_files(pattern):
    max_year = None
    data_files = glob.glob(pattern)
    for data_file in data_files:
        parts = (os.path.splitext(os.path.basename(data_file))[0]).split("_")
        if parts and (not max_year or max_year < int(parts[-1])):
            max_year = int(parts[-1])
    return max_year


def last_quarter_of_files(pattern):
    max_quarter = None
    data_files = glob.glob(pattern)
    for data_file in data_files:
        parts = (os.path.splitext(os.path.basename(data_file))[0]).split("_")
        if parts and (not max_quarter or max_quarter < quarter_count(int(parts[-2]), int(parts[-1]))):
            max_quarter = quarter_count(int(parts[-2]), int(parts[-1]))
    return max_quarter


def archive_files_under(directory, destination):
    data_files = glob.glob(directory + '*')
    if data_files:
        tar = tarfile.open(destination, "w")
        for data_file in data_files:
            tar.add(data_file)
        tar.close()
        print "archive success", destination
    else:
        print "no files to archive"


def delete_files_under(directory):
    data_files = glob.glob(directory + '*')
    for data_file in data_files:
        os.remove(data_file)


def delete_file(file_path):
    try:
        if os.path.exists(file_path):
            os.remove(file_path)
            logging.warn('delete file : ' + file_path)
    except (IOError, RuntimeError):
        logging.exception('delete file failed : ' + file_path)


def report_missing_file(file_path):
    if not os.path.exists(file_path):
        print "missing:", file_path


def ntime2timestamp_string(t):
    millisecond = int((int(t) % 1e9) / 1e6)
    ticks = float(t) / 1e9
    localtime = time.localtime(ticks)
    return "%s.%s" % (time.strftime("%Y%m%d-%H:%M:%S", localtime), str(millisecond).zfill(3))


def ntime2float_string(t):
    ticks = float(t) / 1e9
    localtime = time.localtime(ticks)
    return time.strftime("%Y%m%d.%H%M%S", localtime)


def parse_midas_format(line):
    result = OrderedDict()
    line = line.strip()
    if line.endswith(';'):
        for entry in line[:-1].split(","):
            if entry:
                kv = entry.split(' ')
                result[kv[0]] = kv[1]
    return result


def to_numeric_array(stringArray):
    result = []
    for item in stringArray:
        result.append(float(item))
    return result

if __name__ == '__main__':
    print timestamp2date_str(time.time())
    print cob2date(20120923)                            # 2012-09-23
    print timestamp2date_str(1430323200)
    print date_str2cob('2015-04-30')
    print month_count(2017, 1)
    y, m = count2month(564)
    print y, m
    print quarter_count_from_month_count(month_count(2017, 1))
    print quarter_count(2017, 1)
    y, q = count2quarter(188)
    print y, q
    print os.path.basename("/a/b/c.txt")
    print os.path.splitext(os.path.basename("/a/b/c.txt"))[0]
    # print get_all_stock_codes()
    print ntime2timestamp_string(1508942856453804254)       # 20171025.224736
    parse_midas_format('a 1 ,b 2 ,c ,;')
    print 'test %s %d finished' % ("a", 2)
    print 'test finished'
