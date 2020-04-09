from numpy import *

# merge
vstack([[1, 2], [3, 4], [5, 6]])                                    # [[1, 2], [3, 4], [5, 6]]
hstack([[1, 2], [3, 4], [5, 6]])                                    # [1, 2, 3, 4, 5, 6]
concatenate(([[1, 2], [3, 4]], [[5, 6], [7, 8]]))                   # [[1, 2], [3, 4], [5, 6], [7, 8]]
concatenate(([[1, 2], [3, 4]], [[5, 6], [7, 8]]), axis=1)           # [[1, 2, 5, 6], [3, 4, 7, 8]]
# column_stack stacks 1D arrays as columns into a 2D array. It is equivalent to vstack only for 1D arrays
column_stack([[1, 2], [3, 4], [5, 6]])                              # [[1, 3, 5], [2, 4, 6]]
row_stack([[1, 2], [3, 4], [5, 6]])                                 # [[1, 2], [3, 4], [5, 6]]

a = array([[0, 1], [2, 3]])
print('flatten', a.flatten())                                       # 返回的是数组的复制 [0 1 2 3]
a_view = a.flat                                                     # 返回了所有元组组成的一个迭代器
print('flat', a_view[:])

# r_[] and c_[] are useful for creating arrays by stacking numbers along one axis.
# r_ / c_ 来产生行向量或者列向量
print(r_[1:5])                                                      # [1, 2, 3, 4]
print(r_[1:10:4])                                                   # same as arange(1, 10, 4), [1, 5, 9]
print(r_[1:10:4j])                                                  # same as linspace(1, 10, 4), [ 1., 4., 7., 10.]
print(r_[1:5, 7, 1:10:4])                                           # [1, 2, 3, 4, 7, 1, 5, 9]
print(r_['r', 1:3].shape)                                           # 1 * 2, [[1, 2]]
print(r_['c', 1:3].shape)                                           # 2 * 1, [[1], [2]]
print(r_[[[1, 2], [4, 5]], [[1, 2], [4, 5]]].shape)                 # 4 * 2, [1, 2], [4, 5], [1, 2], [4, 5]]
print(r_['-1', [[1, 2], [4, 5]], [[1, 2], [4, 5]]].shape)           # 2 * 4, [[1, 2, 1, 2], [4, 5, 4, 5]]
print(c_[1:5].shape)                                                # 4 * 1, [1, 2, 3, 4]^T
print(c_[1:5, 2:6].shape)                                           # 4 * 2, [[1, 2], [2, 3], [3, 4], [4, 5]]
