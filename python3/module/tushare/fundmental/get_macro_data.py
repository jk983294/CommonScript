# coding=utf-8
import tushare as ts
import pandas as pd

# 存款利率
# date :变动日期 deposit_type :存款种类 rate:利率（%）
df = ts.get_deposit_rate()
print(df.head())
print(df.tail())

# 贷款利率
# date :执行日期 loan_type :存款种类 rate:利率（%）
ts.get_loan_rate()

# 存款准备金率
# date :变动日期 before :调整前存款准备金率(%) now:调整后存款准备金率(%) changed:调整幅度(%)
ts.get_rrr()

# 货币供应量
# month :统计时间 m2 :货币和准货币（广义货币M2）(亿元) m2_yoy:货币和准货币（广义货币M2）同比增长(%)
# m1:货币(狭义货币M1)(亿元) m1_yoy:货币(狭义货币M1)同比增长(%) m0:流通中现金(M0)(亿元) m0_yoy:流通中现金(M0)同比增长(%)
# cd:活期存款(亿元) cd_yoy:活期存款同比增长(%) qm:准货币(亿元) qm_yoy:准货币同比增长(%)
# ftd:定期存款(亿元) ftd_yoy:定期存款同比增长(%) sd:储蓄存款(亿元) sd_yoy:储蓄存款同比增长(%)
# rests:其他存款(亿元) rests_yoy:其他存款同比增长(%)
ts.get_money_supply()

# 货币供应量(年底余额)
# year :统计年度 m2 :货币和准货币(亿元) m1:货币(亿元) m0:流通中现金(亿元) cd:活期存款(亿元) qm:准货币(亿元)
# ftd:定期存款(亿元) sd:储蓄存款(亿元) rests:其他存款(亿元)
ts.get_money_supply_bal()

# 国内生产总值(年度)
# year :统计年度 gdp :国内生产总值(亿元) pc_gdp :人均国内生产总值(元) gnp :国民生产总值(亿元)
# pi :第一产业(亿元) si :第二产业(亿元) industry :工业(亿元) cons_industry :建筑业(亿元) ti :第三产业(亿元)
# trans_industry :交通运输仓储邮电通信业(亿元) lbdy :批发零售贸易及餐饮业(亿元)
ts.get_gdp_year()

# 国内生产总值(季度)
# quarter :季度 gdp :国内生产总值(亿元) gdp_yoy :国内生产总值同比增长(%)
# pi :第一产业增加值(亿元) pi_yoy:第一产业增加值同比增长(%) si :第二产业增加值(亿元) si_yoy :第二产业增加值同比增长(%)
# ti :第三产业增加值(亿元) ti_yoy :第三产业增加值同比增长(%)
ts.get_gdp_quarter()

# 三大需求对GDP贡献
# year :统计年度 end_for :最终消费支出贡献率(%) for_rate :最终消费支出拉动(百分点) asset_for :资本形成总额贡献率(%)
# asset_rate:资本形成总额拉动(百分点) goods_for :货物和服务净出口贡献率(%) goods_rate :货物和服务净出口拉动(百分点)
ts.get_gdp_for()

# 三大产业对GDP拉动
# year :统计年度 gdp_yoy :国内生产总值同比增长(%) pi :第一产业拉动率(%) si :第二产业拉动率(%)
# industry:其中工业拉动(%) ti :第三产业拉动率(%)
ts.get_gdp_pull()

# 三大产业贡献率
# year :统计年度 gdp_yoy :国内生产总值 pi :第一产业献率(%) si :第二产业献率(%) industry:其中工业献率(%) ti :第三产业献率(%)
ts.get_gdp_contrib()

# 居民消费价格指数
# month :统计月份 cpi :价格指数
ts.get_cpi()

# 工业品出厂价格指数
# month :统计月份 ppiip :工业品出厂价格指数 ppi :生产资料价格指数 qm:采掘工业价格指数 rmi:原材料工业价格指数
# pi:加工工业价格指数 cg:生活资料价格指数 food:食品类价格指数 clothing:衣着类价格指数 roeu:一般日用品价格指数 dcg:耐用消费品价格指数
ts.get_ppi()

