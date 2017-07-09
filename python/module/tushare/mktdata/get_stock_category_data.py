# coding=utf-8
import tushare as ts
import pandas as pd

# industry category: code, name, industry name
ts.get_industry_classified()

# concept category: code, name, concept name
ts.get_concept_classified()

# area category: code, name, area name
# ts.get_area_classified()

# 中小板股票数据, 所有002开头的股票
ts.get_sme_classified()

# 创业板股票数据, 所有300开头的股票
ts.get_gem_classified()

# 风险警示板股票数据, 所有st股票
ts.get_st_classified()

# 沪深300当前成份股及所占权重
ts.get_hs300s()

# 上证50成份股
ts.get_sz50s()

# 中证500成份股
ts.get_zz500s()

# 已经被终止上市的股票列表, 目前只有在上海证券交易所交易被终止的股票
ts.get_terminated()