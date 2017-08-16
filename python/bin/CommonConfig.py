#!/usr/bin/python
# coding=utf-8
import os
import CommonUtil as util
import time


class Config:
    def __init__(self, dir_prefix):
        if dir_prefix:
            self.data_dir_prefix = dir_prefix
        else:
            self.data_dir_prefix = '/home/kun/Data'

        if not os.path.exists(self.data_dir_prefix):
            print "no valid prefix", self.data_dir_prefix
            exit(1)

        # 上证指数, 深证成指, 沪深300, 上证50, 中小板指, 创业板指
        self.stock_index = ['000001', '399001',
                            '399300', '000016', '399005', '399006']
        self.backup_dir = '%s/backup/MktData/fundamental/' % self.data_dir_prefix
        self.macro_dir = '%s/MktData/fundamental/macro/' % self.data_dir_prefix
        self.class_info_dir = '%s/MktData/fundamental/class_info/' % self.data_dir_prefix
        self.bank_interest_dir = '%s/MktData/fundamental/bank_interest/' % self.data_dir_prefix
        self.stock_report_dir = '%s/MktData/fundamental/stock_report/' % self.data_dir_prefix
        self.stock_daily_dir = '%s/MktData/stock_daily/' % self.data_dir_prefix
        self.stock_daily_nfq_dir = '%s/MktData/stock_daily_nfq/' % self.data_dir_prefix
        self.stock_weekly_dir = '%s/MktData/stock_weekly/' % self.data_dir_prefix

        self.stock_basics_file = '%s/MktData/fundamental/class_info/stock_basics.csv' % self.data_dir_prefix
        self.industry_file = '%s/MktData/fundamental/class_info/industry.csv' % self.data_dir_prefix
        self.concept_file = '%s/MktData/fundamental/class_info/concept.csv' % self.data_dir_prefix
        self.area_file = '%s/MktData/fundamental/class_info/area.csv' % self.data_dir_prefix
        self.sme_file = '%s/MktData/fundamental/class_info/sme.csv' % self.data_dir_prefix
        self.gem_file = '%s/MktData/fundamental/class_info/gem.csv' % self.data_dir_prefix
        self.st_file = '%s/MktData/fundamental/class_info/st.csv' % self.data_dir_prefix
        self.hs300s_file = '%s/MktData/fundamental/class_info/hs300s.csv' % self.data_dir_prefix
        self.sz50s_file = '%s/MktData/fundamental/class_info/sz50s.csv' % self.data_dir_prefix
        self.zz500s_file = '%s/MktData/fundamental/class_info/zz500s.csv' % self.data_dir_prefix
        self.terminated_file = '%s/MktData/fundamental/class_info/terminated.csv' % self.data_dir_prefix
        self.suspended_file = '%s/MktData/fundamental/class_info/suspended.csv' % self.data_dir_prefix

        self.deposit_rate_file = '%s/MktData/fundamental/macro/deposit_rate.csv' % self.data_dir_prefix
        self.loan_rate_file = '%s/MktData/fundamental/macro/loan_rate.csv' % self.data_dir_prefix
        self.rrr_file = '%s/MktData/fundamental/macro/rrr.csv' % self.data_dir_prefix
        self.money_supply_file = '%s/MktData/fundamental/macro/money_supply.csv' % self.data_dir_prefix
        self.money_supply_bal_file = '%s/MktData/fundamental/macro/money_supply_bal.csv' % self.data_dir_prefix
        self.gdp_year_file = '%s/MktData/fundamental/macro/gdp_year.csv' % self.data_dir_prefix
        self.gdp_quarter_file = '%s/MktData/fundamental/macro/gdp_quarter.csv' % self.data_dir_prefix
        self.gdp_for_file = '%s/MktData/fundamental/macro/gdp_for.csv' % self.data_dir_prefix
        self.gdp_pull_file = '%s/MktData/fundamental/macro/gdp_pull.csv' % self.data_dir_prefix
        self.gdp_contrib_file = '%s/MktData/fundamental/macro/gdp_contrib.csv' % self.data_dir_prefix
        self.cpi_file = '%s/MktData/fundamental/macro/cpi.csv' % self.data_dir_prefix
        self.ppi_file = '%s/MktData/fundamental/macro/ppi.csv' % self.data_dir_prefix

    def get_macro_backup_tar_file(self):
        return '%s/backup/MktData/fundamental/macro_%s.tar' % (self.data_dir_prefix, util.get_timestamp_str())

    def get_class_info_backup_tar_file(self):
        return '%s/backup/MktData/fundamental/class_info_%s.tar' % (self.data_dir_prefix, util.get_timestamp_str())

    def get_bank_interest_backup_tar_file(self):
        return '%s/backup/MktData/fundamental/bank_interest_%s.tar' % (self.data_dir_prefix, util.get_timestamp_str())

    def get_stock_report_backup_tar_file(self):
        return '%s/backup/MktData/fundamental/stock_report_%s.tar' % (self.data_dir_prefix, util.get_timestamp_str())
