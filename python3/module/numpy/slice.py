import numpy as np

# vector
a = np.arange(10)
print(a[2])                                 # 2
print(a[[1, 2, 3]])                         # [1 2 3]
idx = np.array([[1, 2], [2, 3]])
print(a[idx])                               # [[1 2], [2 3]]
print(a[2:5])                               # [2 3 4]
a[:6:2] = -1000                             # [-1000     1 -1000     3 -1000     5     6     7     8     9]
print(a)

# matrix
b = np.arange(6).reshape(2, 3)
print(b)                                    # [[0 1 2], [3 4 5]]
print(b[1, 2])                              # 5
print(b[:, 1])                              # second column [1 4]
print(b[1, :])                              # second row [3 4 5]
print(b[-1])                                # the last row [3 4 5]
row_index = np.array([[0, 1], [1, 0]])
column_index = np.array([[0, 1], [1, 2]])
print(b[row_index, column_index])           # [[0 4], [4 2]]

# ... represent as many colons as needed to produce a complete indexing tuple
c = np.arange(6).reshape(1, 1, 2, 3)
print(c[0, ...])                            # = c[0,:,:,:], [[[0 1 2], [3 4 5]]]
print(c[0, ..., 1])                         # = c[0,:,:,1], [[1 4]]
