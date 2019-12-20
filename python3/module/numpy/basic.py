import numpy as np

# main object is the homogeneous multidimensional array
# element (usually number) is indexed by a tuple of positive integers
# the number of axes is rank

# matrix
m = np.arange(6).reshape(2, 3)                                          # [[0 1 2], [3 4 5]]
print(m.shape)                                                          # (3, 5)
print(m.ndim)                                                           # 2
print(m.dtype.name)                                                     # int32
print(m.itemsize)                                                       # 4, sizeof(int32_t)
print(m.size)                                                           # 15
print(type(m))                                                          # numpy.ndarray

# vector
v = np.arange(0, 3, 1)                                                  # [0 1 2]
print(v.shape)                                                          # (3,)
print(v.ndim)                                                           # 1
print(v.dtype.name)                                                     # int32
print(v.itemsize)                                                       # 4, sizeof(int32_t)
print(v.size)                                                           # 15
print(type(v))
