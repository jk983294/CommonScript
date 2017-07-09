import matplotlib.pyplot as plt
import numpy as np

# implicit horizontal values list [0, N)
plt.plot([1, 3, 2, 4, 7, 9, 6], label='Slow')

# plot with x, y array
x = np.arange(0.0, 6.0, 0.01)
plt.plot(x, [xi ** 2 for xi in x], label='Fast')


# legend will show label, default is loc='best'
plt.legend(loc='upper left')
plt.title('Simple plot')
plt.xlabel('This is the X axis')
plt.ylabel('This is the Y axis')
# show axes limits
plt.axis()
# set new axes limits
plt.axis([0, 7, -1, 40])
plt.grid(True)
plt.savefig('basic.png')
plt.show()
