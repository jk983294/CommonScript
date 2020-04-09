import numpy as np

# element-wise operation
a = np.array([20, 30, 40, 50])                          # [20, 30, 40, 50]
b = np.arange(4)                                        # [0, 1, 2, 3]
print(b**2)                                             # [0, 1, 4, 9]
print(np.exp(b))                                        # [  1.           2.71828183   7.3890561   20.08553692]
print(np.sqrt(b))                                       # [ 0.          1.          1.41421356  1.73205081]
w = np.array([0.1, 0.2, 0.5])
print(np.ceil(w))                                       # [ 1.  1.  1.]
print(np.floor(w))                                      # [ 0.  0.  0.]
print(np.round_(w))                                     # [ 0.  0.  0.]
print(w.round(decimals=1))                              # [ 0.1  0.2  0.5]
print(np.clip(w, 0.0, 0.3))                             # [ 0.1  0.2  0.3], 将数值限制在某个范围, remove extreme data

# pair wise, element wise
print(a - b)                                            # [20, 29, 38, 47]
print(np.add(a, b))                                     # [20 31 42 53]
print(np.inner(a, b))                                   # inner product, 260
print(np.maximum(a, b))                                 # [20 30 40 50] ele max
print(np.minimum(a, b))                                 # [0 1 2 3] ele min

# other
print(np.outer(a, b))                                   # outer product
print('cross', np.cross(np.array([1, 0, 0]), np.array([0, 1, 0])))  # [0 0 1], vector perpendicular to both a and b
print(np.cumprod(b))                                    # cumulative product, [0 0 0 0]
print(np.cumsum(b))                                     # cumulative sum, [0 1 3 6]
print(np.diff(b))                                       # 1st-order differences, [1 1 1]
print(np.diff(b, n=2))                                  # 2st-order differences, [0 0]

# stats
print(np.bincount([1, 3, 5, 2]))                                    # [0 1 1 1 0 1]
print(np.bincount([1, 3, 5, 2], weights=[0.1, 0.2, 0.3, 0.4]))      # [ 0.   0.1  0.4  0.2  0.   0.3]


# in-place operator, modify an existing array rather than create a new one
a *= 3
print(a)                                                # [ 60  90 120 150]
b += a
print(b)                                                # [ 60  91 122 153]
