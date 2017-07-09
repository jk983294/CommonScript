# coding=utf-8
import tushare as ts
import pandas as pd

# get current stock price
df = ts.get_today_all()
print df.head()

# get current index price
df = ts.get_index()
print df.head()

# get realtime quotes
df = ts.get_realtime_quotes('000581')
ts.get_realtime_quotes(['600848', '000980', '000981'])
# 上证指数
ts.get_realtime_quotes('sh')
# 上证指数 深圳成指 沪深300指数 上证50 中小板 创业板
ts.get_realtime_quotes(['sh', 'sz', 'hs300', 'sz50', 'zxb', 'cyb'])
# mixed
ts.get_realtime_quotes(['sh', '600848'])
