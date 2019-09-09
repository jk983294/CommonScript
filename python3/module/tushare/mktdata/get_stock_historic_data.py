# coding=utf-8
import tushare as ts
import pandas as pd

# code      stock code
# ktype     data type, default day, D for day, W for week, M for month, 5 for 5min, 15min, 30min, 60min
# autype    default qfq previous, hfq backwards, None no
# index     default False, if True means it is index code
# start     format : YYYY-MM-DD, if empty, then today
# end       format : YYYY-MM-DD

# get 3 year day data, qfq
df = ts.get_k_data('600000')
print(df.head())
print(df.tail())

# get 6 years weekly data
ts.get_k_data('600000', ktype='W', autype='hfq')

# get 5 min data
ts.get_k_data('600000', ktype='5')

# get 300 index
ts.get_k_data('399300', index=True, start='2016-10-01', end='2016-10-31')

# 融资融券
ts.sh_margins(start='2015-01-01', end='2015-04-19')
ts.sz_margins(start='2015-01-01', end='2015-04-19')


