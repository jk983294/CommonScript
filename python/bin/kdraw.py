#!/usr/bin/python
# coding=utf-8
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import dates as mdates
from matplotlib import ticker as mticker
from matplotlib.finance import candlestick_ohlc
import datetime as dt
import pylab
import CommonUtil as util
import CommonConfig
from optparse import OptionParser

#
# useful commands:
# ./kdraw.py -c 000001
# ./kdraw.py -c 000001 -s 20150712
# ./kdraw.py -c 000001 -s 20150712 -e 20170512
# python kdraw.py -c 600000 -s 20150512
#


def sma_calculation(data, day):
    day_count = len(data)
    result = range(day_count)

    i = 0
    sum_value = 0
    while i < day_count:
        if i < day:
            sum_value += data[i]
            result[i] = sum_value / (i + 1)
        else:
            sum_value += data[i]
            sum_value -= data[i - day]
            result[i] = sum_value / day

        i += 1

    return result


def ema_calculation(values, window):
    weights = np.exp(np.linspace(-1., 0., window))
    weights /= weights.sum()
    a = np.convolve(values, weights, mode='full')[:len(values)]
    a[:window] = a[window]
    return a


def macd_calculation(x, slow=26, fast=12):
    ema_slow = ema_calculation(x, slow)
    ema_fast = ema_calculation(x, fast)
    return ema_slow, ema_fast, ema_fast - ema_slow


def rsi_calculation(prices, n=14):
    deltas = np.diff(prices)
    seed = deltas[:n + 1]
    up = seed[seed >= 0].sum() / n
    down = -seed[seed < 0].sum() / n
    rs = up / down
    rsi = np.zeros_like(prices)
    rsi[:n] = 100. - 100. / (1. + rs)

    for i in range(n, len(prices)):
        delta = deltas[i - 1]             # cause the diff is 1 shorter
        if delta > 0:
            up_value = delta
            down_value = 0.
        else:
            up_value = 0.
            down_value = -delta

        up = (up * (n - 1) + up_value) / n
        down = (down * (n - 1) + down_value) / n

        rs = up / down
        rsi[i] = 100. - 100. / (1. + rs)

    return rsi


def main():
    parser = OptionParser()
    parser.add_option("-p", "--prefix", dest="DataDirPrefix",
                      help="data directory prefix")
    parser.add_option("-c", "--code", dest="stock_code", help="stock code")
    parser.add_option("-w", "--weekly", action="store_true", dest="weekly", default=False,
                      help="find stock file in weekly data directory")
    parser.add_option("-f", "--stock_file",
                      dest="stock_file", help="stock file")
    parser.add_option("-s", "--start", dest="start_date", help="start date")
    parser.add_option("-e", "--end", dest="end_date", help="end date")
    (options, args) = parser.parse_args()

    config = CommonConfig.Config(options.DataDirPrefix)
    stock_code = ''

    if options.stock_file:
        stock_path = options.stock_file
    else:
        if options.stock_code:
            stock_code = options.stock_code
        else:
            print "no stock code provided!"
            exit(1)

        if options.weekly:
            stock_path = config.stock_weekly_dir + stock_code + '.csv'
        else:
            stock_path = config.stock_daily_dir + stock_code + '.csv'

    average1 = 30
    average2 = 90

    # days = read_stock_data(stock_path, start_date, end_date)
    raw_data = util.get_dataframe_from_file(
        stock_path, dt={'code': 'str', 'date': 'str'})

    if options.start_date:
        raw_data = raw_data[raw_data['date'] >
                            util.cob2date(options.start_date)]
    if options.end_date:
        raw_data = raw_data[raw_data['date'] < util.cob2date(options.end_date)]

    date_time = map(lambda d: mdates.date2num(
        dt.datetime.strptime(d, "%Y-%m-%d")), raw_data['date'].tolist())
    days = pd.DataFrame({'DateTime': date_time, 'Open': raw_data['open'].tolist(),
                         'Close': raw_data['close'].tolist(), 'High': raw_data['high'].tolist(),
                         'Low': raw_data['low'].tolist()})
    days = days.reindex(columns=['DateTime', 'Open', 'High', 'Low', 'Close'])

    ma1 = sma_calculation(days.Close.values, average1)
    ma2 = sma_calculation(days.Close.values, average2)
    fig = plt.figure(facecolor='#07000d', figsize=(15, 10))

    ax1 = plt.subplot2grid((6, 4), (1, 0), rowspan=4,
                           colspan=4, axisbg='#07000d')
    candlestick_ohlc(ax1, days.values, width=.6,
                     colorup='#ff1717', colordown='#53c156')
    ma_label1 = str(average1) + ' SMA'
    ma_label2 = str(average2) + ' SMA'

    ax1.plot(days.DateTime.values, ma1, '#e1edf9',
             label=ma_label1, linewidth=1.5)
    ax1.plot(days.DateTime.values, ma2, '#4ee6fd',
             label=ma_label2, linewidth=1.5)
    ax1.grid(True, color='w')
    ax1.xaxis.set_major_locator(mticker.MaxNLocator(10))
    ax1.xaxis.set_major_formatter(mdates.DateFormatter('%Y-%m-%d'))
    ax1.yaxis.label.set_color("w")
    ax1.spines['bottom'].set_color("#5998ff")
    ax1.spines['top'].set_color("#5998ff")
    ax1.spines['left'].set_color("#5998ff")
    ax1.spines['right'].set_color("#5998ff")
    ax1.tick_params(axis='y', colors='w')
    plt.gca().yaxis.set_major_locator(mticker.MaxNLocator(prune='upper'))
    ax1.tick_params(axis='x', colors='w')
    plt.ylabel('Stock price and Volume')

    # plot an RSI indicator on top
    ma_legend = plt.legend(loc=9, ncol=2, prop={
                           'size': 7}, fancybox=True, borderaxespad=0.)
    ma_legend.get_frame().set_alpha(0.4)
    text_legend = pylab.gca().get_legend().get_texts()
    pylab.setp(text_legend[0:5], color='w')

    ax0 = plt.subplot2grid((6, 4), (0, 0), sharex=ax1,
                           rowspan=1, colspan=4, axisbg='#07000d')
    rsi = rsi_calculation(days.Close.values)
    rsi_col = '#c1f9f7'
    pos_col = '#386d13'
    neg_col = '#8f2020'

    ax0.plot(days.DateTime.values, rsi, rsi_col, linewidth=1.5)
    ax0.axhline(70, color=neg_col)
    ax0.axhline(30, color=pos_col)
    ax0.fill_between(days.DateTime.values, rsi, 70, where=(
        rsi >= 70), facecolor=neg_col, edgecolor=neg_col, alpha=0.5)
    ax0.fill_between(days.DateTime.values, rsi, 30, where=(
        rsi <= 30), facecolor=pos_col, edgecolor=pos_col, alpha=0.5)
    ax0.set_yticks([30, 70])
    ax0.yaxis.label.set_color("w")
    ax0.spines['bottom'].set_color("#5998ff")
    ax0.spines['top'].set_color("#5998ff")
    ax0.spines['left'].set_color("#5998ff")
    ax0.spines['right'].set_color("#5998ff")
    ax0.tick_params(axis='y', colors='w')
    ax0.tick_params(axis='x', colors='w')
    plt.ylabel('RSI')

    # plot volume
    volume_min = 0
    ax1v = ax1.twinx()
    ax1v.fill_between(days.DateTime.values, volume_min, raw_data.volume.values, facecolor='#00ffe8',
                      alpha=.4)
    ax1v.axes.yaxis.set_ticklabels([])
    ax1v.grid(False)
    # Edit this to 3, so it's a bit larger
    ax1v.set_ylim(0, 3 * raw_data.volume.values.max())
    ax1v.spines['bottom'].set_color("#5998ff")
    ax1v.spines['top'].set_color("#5998ff")
    ax1v.spines['left'].set_color("#5998ff")
    ax1v.spines['right'].set_color("#5998ff")
    ax1v.tick_params(axis='x', colors='w')
    ax1v.tick_params(axis='y', colors='w')

    # plot an MACD indicator on bottom
    ax2 = plt.subplot2grid((6, 4), (5, 0), sharex=ax1,
                           rowspan=1, colspan=4, axisbg='#07000d')
    fillcolor = '#00ffe8'
    n_slow = 26
    n_fast = 12
    n_ema = 9
    ema_slow, ema_fast, macd = macd_calculation(
        days.Close.values, n_slow, n_fast)
    ema9 = ema_calculation(macd, n_ema)
    ax2.plot(days.DateTime.values, macd, color='#4ee6fd', lw=2)
    ax2.plot(days.DateTime.values, ema9, color='#e1edf9', lw=1)
    ax2.fill_between(days.DateTime.values, macd - ema9, 0, alpha=0.5, facecolor=fillcolor,
                     edgecolor=fillcolor)
    plt.gca().yaxis.set_major_locator(mticker.MaxNLocator(prune='upper'))

    ax2.spines['bottom'].set_color("#5998ff")
    ax2.spines['top'].set_color("#5998ff")
    ax2.spines['left'].set_color("#5998ff")
    ax2.spines['right'].set_color("#5998ff")
    ax2.tick_params(axis='x', colors='w')
    ax2.tick_params(axis='y', colors='w')
    plt.ylabel('MACD', color='w')
    ax2.yaxis.set_major_locator(mticker.MaxNLocator(nbins=5, prune='upper'))
    for label in ax2.xaxis.get_ticklabels():
        label.set_rotation(45)

    # other tweak
    plt.suptitle(stock_code, color='w')
    plt.setp(ax0.get_xticklabels(), visible=False)
    plt.setp(ax1.get_xticklabels(), visible=False)
    plt.subplots_adjust(left=.09, bottom=.14, right=.94,
                        top=.95, wspace=.20, hspace=0)
    plt.show()


if __name__ == "__main__":
    main()
