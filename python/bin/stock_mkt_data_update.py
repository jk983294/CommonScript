#!/usr/bin/python
# coding=utf-8
import tushare as ts
import pandas as pd
import os
from optparse import OptionParser
import CommonUtil as util
import CommonConfig

parser = OptionParser()
parser.add_option("-p", "--prefix", dest="DataDirPrefix", help="data directory prefix")
parser.add_option("-d", "--stock_daily", action="store_true", dest="stock_daily", default=False,
                  help="download stock_daily")
parser.add_option("-w", "--stock_weekly", action="store_true", dest="stock_weekly", default=False,
                  help="download stock_weekly")
(options, args) = parser.parse_args()

config = CommonConfig.Config(options.DataDirPrefix)

if options.stock_daily:
    util.prepare_dir(config.stock_daily_dir)
    stocks = util.get_dataframe_from_file(config.area_file, dt={'code': 'str'})

    if not stocks.empty:
        for code in config.stock_index:
            util.save_dataframe(ts.get_k_data(code, index=True),
                                config.stock_daily_dir + ('index_%s.csv' % code),
                                error_msg='failed to download daily stock index %s' % code)

        for index, row in stocks.iterrows():
            code = row['code']
            util.save_dataframe(ts.get_k_data(code), config.stock_daily_dir + ('%s.csv' % code),
                                error_msg='failed to download daily stock %s' % code)
    else:
        print "no file % for downloading" % config.area_file

if options.stock_weekly:
    util.prepare_dir(config.stock_weekly_dir)
    stocks = util.get_dataframe_from_file(config.area_file, dt={'code': 'str'})

    if not stocks.empty:
        for code in config.stock_index:
            util.save_dataframe(ts.get_k_data(code, index=True, ktype='W', autype='hfq'),
                                config.stock_weekly_dir + ('index_%s.csv' % code),
                                error_msg='failed to download weekly stock index %s' % code)

        for index, row in stocks.iterrows():
            code = row['code']
            util.save_dataframe(ts.get_k_data(code, ktype='W', autype='hfq'),
                                config.stock_weekly_dir + ('%s.csv' % code),
                                error_msg='failed to download weekly stock %s' % code)
    else:
        print "no file % for downloading" % config.area_file
