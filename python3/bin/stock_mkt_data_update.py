#!/usr/bin/python3
# coding=utf-8
import time
import tushare as ts
import pandas as pd
import os
from optparse import OptionParser
import CommonUtil as util
import CommonConfig

#
# useful commands:
# ./stock_mkt_data_update.py -d > /tmp/download.log 2>&1
# ./stock_mkt_data_update.py -d -s 20060101 > /tmp/download.log 2>&1
# ./stock_mkt_data_update.py -d -s 20060101 -f none > /tmp/download.log 2>&1
#
# for test
# ./stock_mkt_data_update.py -d -s 20150101 -o /tmp/test/
# ./stock_mkt_data_update.py -d -s 20150101 -f none -o /tmp/test/
# ./stock_mkt_data_update.py -d -o /tmp/test/ > /tmp/download.log 2>&1

parser = OptionParser()
parser.add_option("-p", "--prefix", dest="DataDirPrefix",
                  help="data directory prefix")
parser.add_option("-d", "--stock_daily", action="store_true", dest="stock_daily", default=False,
                  help="download stock_daily")
parser.add_option("-w", "--stock_weekly", action="store_true", dest="stock_weekly", default=False,
                  help="download stock_weekly")
parser.add_option("-s", "--start_cob", type="int", dest="start_cob", default=0,
                  help="start_cob like 20150101")
parser.add_option("-e", "--end_cob", type="int", dest="end_cob", default=0,
                  help="end_cob like 20170728")
parser.add_option("-f", "--stock_fq", dest="fq", default="qfq",
                  help="fu quan info (qfq/hfq/none)")
parser.add_option("-o", "--override_dir", dest="override_dir", default=None,
                  help="override target dir to store, this is mainly for test")
(options, args) = parser.parse_args()

config = CommonConfig.Config(options.DataDirPrefix)

if options.stock_daily:
    fq = options.fq
    target_dir = config.stock_daily_dir
    if options.fq == "none":
        fq = None
        target_dir = config.stock_daily_nfq_dir

    if options.override_dir:
        target_dir = options.override_dir

    util.prepare_dir(target_dir)
    stocks = util.get_dataframe_from_file(config.area_file, dt={'code': 'str'})

    if not stocks.empty:
        if options.start_cob:
            start_date = util.cob2date(options.start_cob)
            end_date = util.timestamp2date_str(time.time())
            if options.end_cob:
                end_date = util.cob2date(options.end_cob)

            for code in config.stock_index:
                util.save_dataframe(ts.get_k_data(code, index=True, autype=fq, start=start_date, end=end_date),
                                    target_dir + ('index_%s.csv' % code),
                                    error_msg='failed to download daily stock index %s' % code)

            for index, row in stocks.iterrows():
                code = row['code']
                util.save_dataframe(ts.get_k_data(code, autype=fq, start=start_date, end=end_date),
                                    target_dir + ('%s.csv' % code),
                                    error_msg='failed to download daily stock %s' % code)
        else:
            for code in config.stock_index:
                util.save_dataframe(ts.get_k_data(code, index=True, autype=fq),
                                    target_dir + ('index_%s.csv' % code),
                                    error_msg='failed to download daily stock index %s' % code)

            for index, row in stocks.iterrows():
                code = row['code']
                util.save_dataframe(ts.get_k_data(code, autype=fq),
                                    target_dir + ('%s.csv' % code),
                                    error_msg='failed to download daily stock %s' % code)
    else:
        print("no file % for downloading" % config.area_file)

if options.stock_weekly:
    util.prepare_dir(config.stock_weekly_dir)
    stocks = util.get_dataframe_from_file(config.area_file, dt={'code': 'str'})

    if not stocks.empty:
        for code in config.stock_index:
            util.save_dataframe(ts.get_k_data(code, index=True, ktype='W', autype='hfq'),
                                config.stock_weekly_dir +
                                ('index_%s.csv' % code),
                                error_msg='failed to download weekly stock index %s' % code)

        for index, row in stocks.iterrows():
            code = row['code']
            util.save_dataframe(ts.get_k_data(code, ktype='W', autype='hfq'),
                                config.stock_weekly_dir + ('%s.csv' % code),
                                error_msg='failed to download weekly stock %s' % code)
    else:
        print("no file % for downloading" % config.area_file)
