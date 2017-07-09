# coding=utf-8
import tushare as ts
import pandas as pd

# quick run to test
df = ts.shibor_quote_data(2016)
df.to_csv('/home/kun/Data/MktData/fundamental/bank_interest/shibor_quote_data_2016.csv', encoding='utf-8')


# Shibor拆放利率, since 2006
# ON:隔夜拆放利率 1W:1周拆放利率 2W:2周拆放利率 1M:1个月拆放利率 3M:3个月拆放利率 6M:6个月拆放利率 9M:9个月拆放利率 1Y:1年拆放利率
df = ts.shibor_data()       # 取当前年份的数据
# df = ts.shibor_data(2014)  # 取2014年的数据
print df.head()
print df.tail()

# 银行报价数据, since 2006
# date:日期 bank:报价银行名称 ON:隔夜拆放利率 ON_B:隔夜拆放买入价 ON_A:隔夜拆放卖出价 1W_B:1周买入 1W_A:1周卖出
# 2W_B:买入 2W_A:卖出 1M_B:买入 1M_A:卖出 3M_B:买入 3M_A:卖出 6M_B:买入 6M_A:卖出 9M_B:买入 9M_A:卖出 1Y_B:买入 1Y_A:卖出
df = ts.shibor_quote_data()         # 取当前年份的数据
df = ts.shibor_quote_data(2015)

# Shibor均值数据, since 2006
# date:日期 其它分别为各周期5、10、20均价，请参考上面的周期含义
df = ts.shibor_ma_data()        # 取当前年份的数据
# df = ts.shibor_ma_data(2014)  # 取2014年的数据

# 贷款基础利率, since 2013
# date:日期 1Y:1年贷款基础利率
df = ts.lpr_data()          # 取当前年份的数据
# df = ts.lpr_data(2014)    # 取2014年的数据

# 获取贷款基础利率均值数据, since 2013
# date:日期 1Y_5:5日均值 1Y_10:10日均值 1Y_20:20日均值
df = ts.lpr_ma_data()           # 取当前年份的数据
# df = ts.lpr_ma_data(2014)     # 取2014年的数据