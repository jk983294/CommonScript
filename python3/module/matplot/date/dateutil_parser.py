import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import datetime as dt
import dateutil.parser

datestrings = ['2008-07-18 14:36:53.494013',
               '2008-07-20 14:37:01.508990', '2008-07-28 14:49:26.183256']
dates = [dateutil.parser.parse(s) for s in datestrings]
values = np.random.rand(len(dates))
plt.plot_date(mpl.dates.date2num(dates), values, linestyle='-')
plt.show()
