#!/usr/bin/python
# coding=utf-8
import os
from optparse import OptionParser
import tushare as ts
import CommonUtil as util
import CommonConfig
from datetime import date

parser = OptionParser()
parser.add_option("-p", "--prefix", dest="DataDirPrefix", help="data directory prefix")
parser.add_option("-c", "--class_info", action="store_true", dest="class_info", default=False,
                  help="download class_info")
parser.add_option("-b", "--bank_interest", action="store_true", dest="bank_interest", default=False,
                  help="download bank_interest")
parser.add_option("-r", "--stock_report", action="store_true", dest="stock_report", default=False,
                  help="download stock_report")
parser.add_option("-m", "--report_missing", action="store_true", dest="report_missing", default=False,
                  help="report missing reports")
parser.add_option("-a", "--macro", action="store_true", dest="macro", default=False,
                  help="download macro info")
(options, args) = parser.parse_args()

config = CommonConfig.Config(options.DataDirPrefix)
util.prepare_dir(config.backup_dir)

if options.macro:
    util.prepare_dir(config.macro_dir)
    # archive old file
    util.archive_files_under(config.macro_dir, config.get_macro_backup_tar_file())
    util.delete_files_under(config.macro_dir)

    # download new data
    util.save_dataframe(ts.get_deposit_rate(), config.deposit_rate_file, error_msg='failed to download deposit rate')
    util.save_dataframe(ts.get_loan_rate(), config.loan_rate_file, error_msg='failed to download loan_rate_file')
    util.save_dataframe(ts.get_rrr(), config.rrr_file, error_msg='failed to download reserve rate')
    util.save_dataframe(ts.get_money_supply(), config.money_supply_file, error_msg='failed to download money_supply')
    util.save_dataframe(ts.get_money_supply_bal(), config.money_supply_bal_file,
                        error_msg='failed to download money_supply_balance')
    util.save_dataframe(ts.get_gdp_year(), config.gdp_year_file, error_msg='failed to download yearly gdp')
    util.save_dataframe(ts.get_gdp_quarter(), config.gdp_quarter_file, error_msg='failed to download quarterly gdp')
    util.save_dataframe(ts.get_gdp_for(), config.gdp_for_file, error_msg='failed to download gdp for three main need')
    util.save_dataframe(ts.get_gdp_pull(), config.gdp_pull_file,
                        error_msg='failed to download gdp pull by three industries')
    util.save_dataframe(ts.get_gdp_contrib(), config.gdp_contrib_file,
                        error_msg='failed to download gdp contribution of three industries')
    util.save_dataframe(ts.get_cpi(), config.cpi_file, error_msg='failed to download cpi')
    util.save_dataframe(ts.get_ppi(), config.ppi_file, error_msg='failed to download ppi')

if options.class_info:
    util.prepare_dir(config.class_info_dir)
    # archive old file
    util.archive_files_under(config.class_info_dir, config.get_class_info_backup_tar_file())
    util.delete_files_under(config.class_info_dir)

    # download new data
    util.save_dataframe(ts.get_stock_basics(), config.stock_basics_file, error_msg='failed to download stock_basics')
    util.save_dataframe(ts.get_industry_classified(), config.industry_file, error_msg='failed to download industry')
    util.save_dataframe(ts.get_concept_classified(), config.concept_file, error_msg='failed to download concept')
    util.save_dataframe(ts.get_area_classified(), config.area_file, error_msg='failed to download area')
    # 中小板股票数据, 所有002开头的股票
    util.save_dataframe(ts.get_sme_classified(), config.sme_file, error_msg='failed to download sme')
    # 创业板股票数据, 所有300开头的股票
    util.save_dataframe(ts.get_gem_classified(), config.gem_file, error_msg='failed to download gem')
    util.save_dataframe(ts.get_st_classified(), config.st_file, error_msg='failed to download st')
    util.save_dataframe(ts.get_hs300s(), config.hs300s_file, error_msg='failed to download hs300s')
    util.save_dataframe(ts.get_sz50s(), config.sz50s_file, error_msg='failed to download sz50s')
    util.save_dataframe(ts.get_zz500s(), config.zz500s_file, error_msg='failed to download zz500s')
    util.save_dataframe(ts.get_terminated(), config.terminated_file, error_msg='failed to download terminated')

# first archive all old files, then download missing year data
# then last year afterwards downloading (include last year in case last is incomplete)
if options.bank_interest:
    util.prepare_dir(config.bank_interest_dir)
    util.archive_files_under(config.bank_interest_dir, config.get_bank_interest_backup_tar_file())

    year = date.today().year

    last_year_shibor_data = util.last_year_of_files(config.bank_interest_dir + 'shibor_data*')
    last_year_shibor_ma_data = util.last_year_of_files(config.bank_interest_dir + 'shibor_ma_data*')
    last_year_shibor_quote_data = util.last_year_of_files(config.bank_interest_dir + 'shibor_quote_data*')
    start_year = 2006
    while start_year <= year:
        file_name = (config.bank_interest_dir + 'shibor_data_%d.csv') % start_year
        if not os.path.exists(file_name) or (last_year_shibor_data and start_year == last_year_shibor_data):
            util.save_dataframe(ts.shibor_data(start_year), file_name,
                                error_msg='failed to download shibor_data for year %d' % start_year)
        file_name = (config.bank_interest_dir + 'shibor_ma_data_%d.csv') % start_year
        if not os.path.exists(file_name) or (last_year_shibor_ma_data and start_year == last_year_shibor_ma_data):
            util.save_dataframe(ts.shibor_ma_data(start_year), file_name,
                                error_msg='failed to download shibor_ma_data for year %d' % start_year)
        file_name = (config.bank_interest_dir + 'shibor_quote_data_%d.csv') % start_year
        if not os.path.exists(file_name) or (last_year_shibor_quote_data and start_year == last_year_shibor_quote_data):
            util.save_dataframe(ts.shibor_quote_data(start_year), file_name,
                                error_msg='failed to download shibor_quote_data for year %d' % start_year)
        start_year += 1

    last_year_lpr = util.last_year_of_files(config.bank_interest_dir + 'lpr_data*')
    last_year_lpr_ma = util.last_year_of_files(config.bank_interest_dir + 'lpr_ma_data*')
    start_year = 2013
    while start_year <= year:
        file_name = (config.bank_interest_dir + 'lpr_data_%d.csv') % start_year
        if not os.path.exists(file_name) or (last_year_lpr and start_year == last_year_lpr):
            util.save_dataframe(ts.lpr_data(start_year), file_name,
                                error_msg='failed to download lpr_data for year %d' % start_year)
        file_name = (config.bank_interest_dir + 'lpr_ma_data_%d.csv') % start_year
        if not os.path.exists(file_name) or (last_year_lpr_ma and start_year == last_year_lpr_ma):
            util.save_dataframe(ts.lpr_ma_data(start_year), file_name,
                                error_msg='failed to download lpr_ma_data for year %d' % start_year)
        start_year += 1

# first archive all files, then download missing year data
# then last year afterwards downloading (include last year in case last is incomplete)
if options.stock_report:
    util.prepare_dir(config.stock_report_dir)
    util.archive_files_under(config.stock_report_dir, config.get_stock_report_backup_tar_file())

    now = date.today()
    year = now.year
    month = now.month

    last_report_data = util.last_quarter_of_files(config.stock_report_dir + 'report_data*')
    last_profit_data = util.last_quarter_of_files(config.stock_report_dir + 'profit_data*')
    last_operation_data = util.last_quarter_of_files(config.stock_report_dir + 'operation_data*')
    last_growth_data = util.last_quarter_of_files(config.stock_report_dir + 'growth_data*')
    last_debtpaying_data = util.last_quarter_of_files(config.stock_report_dir + 'debtpaying_data*')
    last_cashflow_data = util.last_quarter_of_files(config.stock_report_dir + 'cashflow_data*')
    start_quarter = util.quarter_count(2005, 1)
    last_quarter = util.quarter_count_from_month_count(util.month_count(year, month) - 3)
    while start_quarter <= last_quarter:
        y, q = util.count2quarter(start_quarter)

        file_name = (config.stock_report_dir + 'report_data_%d_%d.csv') % (y, q)
        if not os.path.exists(file_name) or (last_report_data and start_quarter == last_report_data):
            util.save_dataframe(ts.get_report_data(y, q), file_name,
                                error_msg='failed to download report_data for year %d quarter %d' % (y, q))

        file_name = (config.stock_report_dir + 'profit_data_%d_%d.csv') % (y, q)
        if not os.path.exists(file_name) or (last_profit_data and start_quarter == last_profit_data):
            util.save_dataframe(ts.get_profit_data(y, q), file_name,
                                error_msg='failed to download profit_data for year %d quarter %d' % (y, q))

        file_name = (config.stock_report_dir + 'operation_data_%d_%d.csv') % (y, q)
        if not os.path.exists(file_name) or (last_operation_data and start_quarter == last_operation_data):
            util.save_dataframe(ts.get_operation_data(y, q), file_name,
                                error_msg='failed to download operation_data for year %d quarter %d' % (y, q))

        file_name = (config.stock_report_dir + 'growth_data_%d_%d.csv') % (y, q)
        if not os.path.exists(file_name) or (last_growth_data and start_quarter == last_growth_data):
            util.save_dataframe(ts.get_growth_data(y, q), file_name,
                                error_msg='failed to download growth_data for year %d quarter %d' % (y, q))

        file_name = (config.stock_report_dir + 'debtpaying_data_%d_%d.csv') % (y, q)
        if not os.path.exists(file_name) or (last_debtpaying_data and start_quarter == last_debtpaying_data):
            util.save_dataframe(ts.get_debtpaying_data(y, q), file_name,
                                error_msg='failed to download debtpaying_data for year %d quarter %d' % (y, q))

        file_name = (config.stock_report_dir + 'cashflow_data_%d_%d.csv') % (y, q)
        if not os.path.exists(file_name) or (last_cashflow_data and start_quarter == last_cashflow_data):
            util.save_dataframe(ts.get_cashflow_data(y, q), file_name,
                                error_msg='failed to download cashflow_data for year %d quarter %d' % (y, q))

        start_quarter += 1

if options.report_missing:
    print "check missing..."
    now = date.today()
    year = now.year
    month = now.month
    start_year = 2006
    while start_year <= year:
        util.report_missing_file((config.bank_interest_dir + 'shibor_data_%d.csv') % start_year)
        util.report_missing_file((config.bank_interest_dir + 'shibor_ma_data_%d.csv') % start_year)
        util.report_missing_file((config.bank_interest_dir + 'shibor_quote_data_%d.csv') % start_year)
        start_year += 1

    start_year = 2013
    while start_year <= year:
        util.report_missing_file((config.bank_interest_dir + 'lpr_data_%d.csv') % start_year)
        util.report_missing_file((config.bank_interest_dir + 'lpr_ma_data_%d.csv') % start_year)
        start_year += 1

    start_quarter = util.quarter_count(2005, 1)
    last_quarter = util.quarter_count_from_month_count(util.month_count(year, month) - 3)
    while start_quarter <= last_quarter:
        y, q = util.count2quarter(start_quarter)
        util.report_missing_file((config.stock_report_dir + 'report_data_%d_%d.csv') % (y, q))
        util.report_missing_file((config.stock_report_dir + 'profit_data_%d_%d.csv') % (y, q))
        util.report_missing_file((config.stock_report_dir + 'operation_data_%d_%d.csv') % (y, q))
        util.report_missing_file((config.stock_report_dir + 'growth_data_%d_%d.csv') % (y, q))
        util.report_missing_file((config.stock_report_dir + 'debtpaying_data_%d_%d.csv') % (y, q))
        util.report_missing_file((config.stock_report_dir + 'cashflow_data_%d_%d.csv') % (y, q))
        start_quarter += 1
