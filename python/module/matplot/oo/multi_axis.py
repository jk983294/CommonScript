import matplotlib.pyplot as plt
import numpy as np

x = np.arange(0., np.e, 0.01)
y1 = np.exp(-x)
y2 = np.log(x)
fig = plt.figure()
ax1 = fig.add_subplot(111)
ax1.plot(x, y1)
ax1.set_ylabel('Y values for exp(-x)')
# twinx creates a new set of axes, so new line need to set color explicitly,
# otherwise it will be the same color with first axes
ax2 = ax1.twinx()
ax2.plot(x, y2, 'r')
ax2.set_xlim([0, np.e])
ax2.set_ylabel('Y values for ln(x)')
ax2.set_xlabel('Same X for both exp(-x) and ln(x)')
plt.show()
