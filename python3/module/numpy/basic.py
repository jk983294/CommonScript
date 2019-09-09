import numpy as np

# main object is the homogeneous multidimensional array
# element (usually number) is indexed by a tuple of positive integers
# the number of axes is rank

a = np.arange(15).reshape(3, 5)                                         # [[ 0,  1,  2,  3,  4], [ 5,  6,  7,  8,  9], [10, 11, 12, 13, 14]]
print(a.shape)                                                          # (3, 5)
print(a.ndim)                                                           # 2
print(a.dtype.name)                                                     # int32
print(a.itemsize)                                                       # 4, the size in bytes of each element of the array, sizeof(int32)
print(a.size)                                                           # 15
print(type(a))                                                          # numpy.ndarray

# print array
print(a)
print(np.arange(10000).reshape(100, 100))                               # automatically skips the central part of the array if too large
