import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import datetime as dt

dates = [dt.datetime.today() + dt.timedelta(days=i) for i in range(10)]
values = np.random.rand(len(dates))
plt.plot_date(mpl.dates.date2num(dates), values, linestyle='-')
plt.show()
