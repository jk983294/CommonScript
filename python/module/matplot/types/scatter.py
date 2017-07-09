import matplotlib.pyplot as plt
import numpy as np

x = np.random.randn(1000)
y = np.random.randn(1000)
size = 50 * np.random.randn(1000)
colors = np.random.rand(1000)
plt.scatter(x, y, s=size, c=colors)
plt.show()
