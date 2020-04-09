import numpy as np

a = np.array([2, 0, 8, 4, 1])
ind = a.argsort()
print(ind)  # [1 4 0 3 2]
print('sort result:', a[ind])  # [0 1 2 4 8]
