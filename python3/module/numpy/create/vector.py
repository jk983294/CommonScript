import numpy as np

print(np.array([20, 30, 40, 50]))  # [20 30 40 50]
print(np.array([20, 30, 40, 50], dtype=np.float32))  # change data type
print(np.arange(6))  # [0, 1, 2, 3, 4, 5]
print(np.arange(6).reshape(2, 3))  # [[0, 1, 2], [3, 4, 5]]
print(np.arange(1, 6, 2))  # [1 3 5]
print(np.arange(0, 2, 0.3))  # [ 0.   0.3  0.6  0.9  1.2  1.5  1.8]

# linspace exactly n elements range from [x, y], arange is n elements range from [x, y)
print(np.linspace(0, 2, 5))  # [ 0.   0.5  1.   1.5  2. ]
np.sin(np.linspace(0, 2 * np.pi, 100))

# 产生 N 个对数等距分布的数组，默认以10为底
print(np.logspace(0, 1, 5))  # [10^0, 10^0.25, 10^0.5, 10^0.75, 10^1]

# 二维平面中生成一个网格
x_ticks = np.linspace(-1, 1, 5)
y_ticks = np.linspace(-1, 1, 5)
x, y = np.meshgrid(x_ticks, y_ticks)