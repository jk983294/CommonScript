import matplotlib.pyplot as plt
import numpy as np

x = np.arange(0, 10, 0.1)
y = np.random.randn(len(x))
fig = plt.figure()
ax = fig.add_subplot(111)
l, = plt.plot(x, y)
t = ax.set_title('random numbers')
plt.show()
