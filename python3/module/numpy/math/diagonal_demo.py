import numpy as np

a = np.array([11, 21, 31, 12, 22, 32, 13, 23, 33])
a.shape = 3, 3
print(a.diagonal())  # [11 22 33]
print(a.diagonal(offset=1))  # [21 32]
print(a.diagonal(offset=2))  # [31]
print(a.diagonal(offset=3))  # []

# 更新对角线的值
i = [0, 1, 2]
print('old values', a[i, i])
a[i, i] = 2
print('new values\n', a)

# 更新offset对角线的值
i = np.array([0, 1])
a[i, i + 1] = 1
a[i + 1, i] = -1
print('new values\n', a)
