import numpy as np

data = np.linspace(0, 1, 5)  # [0.   0.25 0.5  0.75 1.  ]
values = np.array([.1, .8, .3, .12, .5, .25])
print(data)

# searchsorted 返回的值=保持第一个数组的排序性质不变，将第二个数组中的值插入第一个数组中的位置
print(np.searchsorted(data, values))  # [1 4 2 1 2 1]
print(np.searchsorted(data, 0.1))  # 1
print(np.searchsorted(data, 0.5))  # 2

# 利用插入位置，将数组中所有在这两个值之间的值提取出来
bounds = .4, .8
low_idx, high_idx = np.searchsorted(data, bounds)
print(data[low_idx:high_idx])  # [0.5  0.75]
