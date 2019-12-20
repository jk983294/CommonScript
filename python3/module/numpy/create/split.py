from numpy import *

# split
a = array([[3, 4, 5], [6, 7, 8]])
print(a.shape)                                              # 2 * 3
print(hsplit(a, 3)[0].shape)                                # 3 * 2 * 1, [[3], [6]], [[4], [7]], [[5], [8]]
print(hsplit(a, [1, 2])[0].shape)                           # 3 * 2 * 1, [[3], [6]], [[4], [7]], [[5], [8]]

b = array([[3, 4], [5, 6], [7, 8]])
print(b.shape)                                              # 3 * 2
print(vsplit(b, 3)[0].shape)                                # 3 * 1 * 2, [[3, 4]], [[5, 6]], [[7, 8]]
print(vsplit(b, [1, 2])[0].shape)                           # 3 * 1 * 2, [[3, 4]], [[5, 6]], [[7, 8]]

print(array_split(a, 2, axis=0))                            # [array([[3, 4, 5]]), array([[6, 7, 8]])]
print(array_split(a, 3, axis=1))                            # [array([[3], [6]]), array([[4], [7]]), array([[5], [8]])]
