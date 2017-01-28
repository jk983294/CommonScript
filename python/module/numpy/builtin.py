from numpy import *
from numpy.random import *
from numpy.linalg import inv

# Arithmetic operators on arrays apply element-wise. A new array is created and filled with the result.
a = array([20, 30, 40, 50])                         # [20, 30, 40, 50]
b = arange(4)                                       # [0, 1, 2, 3]
c1 = a-b                                            # [20, 29, 38, 47]
b**2                                                # [0, 1, 4, 9]


# matrix operation
A = array([[1, 1], [0, 1]])
B = array([[2, 0], [3, 4]])
A*B                                                 # element-wise product, [[2, 0], [0, 4]]
dot(A, B)                                           # matrix product, [[5, 4], [3, 4]]
inv(A)                                              # inverse matrix, [[ 1., -1.], [ 0.,  1.]]
B.transpose()                                       # [[2, 3], [0, 4]]
B.diagonal()                                        # [2, 4]
B.trace()                                           # 6, sigma (B.diagonal())

# in-place operator, modify an existing array rather than create a new one
a = ones((1, 2), dtype=int)                         # [[1, 1]]
b = random((1, 2))                                  # [[ 0.4238594 ,  0.57967898]]
a *= 3                                              # [[3, 3]]
b += a                                              # [[ 3.4238594 ,  3.57967898]]

# by default, these operations apply to the array as though it were a list of numbers, regardless of its shape
# by specifying the axis parameter you can apply an operation along the specified axis
a = array([[1, 2], [3, 4]])
b = arange(3)                                       # [ 0, 1, 2 ]
c = array([2., -1., 4.])
d = array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
w = array([0.1, 0.2, 0.5])
T = array([1.3, 4.5, 2.8, 3.9])
P = array([2.7, 8.7, 4.7, 8.2])
rho = array([8.5, 5.2, 6.9, 6.5])
booleans = array([True, False, True])
a.sum()                                             # 10
a.min()                                             # 1
a.max()                                             # 4
a.mean()                                            # 2.5
a.std()                                             # 1.1180339887498949, normalized by N (not N-1)
a.var()                                             # 1.25, normalised with N (not N-1)
a.prod()                                            # 24
a.sum(axis=0)                                       # [4, 6]
a.min(axis=0)                                       # [1, 2]
a.max(axis=0)                                       # [3, 4]
a.mean(axis=0)                                      # [ 2.,  3.]
a.std(axis=0)                                       # [ 1.,  1.]
a.var(axis=0)                                       # [ 1.,  1.]
a.prod(axis=0)                                      # [3, 8]

# universal functions, these functions operate element-wise on an array, producing an array as output
exp(b)                                              # [ 1.        ,  2.71828183,  7.3890561 ]
sqrt(b)                                             # [ 0.        ,  1.        ,  1.41421356]
add(b, c)                                           # [ 2.,  0.,  6.]
inner(b, c)                                         # 7.0, sigma ( b[i] * c[i] )
outer(b, c)                                         # [[ 0., -0.,  0.], [ 2., -1.,  4.], [ 4., -2.,  8.]]
cumprod(c)                                          # cumulative product, [ 2., -2., -8.]
cumsum(c)                                           # cumulative sum, [ 2.,  1.,  5.]
diff(c)                                             # 1st-order differences, [-3.,  5.]
diff(c, n=2)                                        # 2st-order differences, diff(diff(c)), [ 8.]
cross(b, c)                                         # vector cross-product, [ 6.,  4., -2.]
apply_along_axis(lambda x: (x[0]+x[-1])/2, 0, d)    # apply to each column (axis=0) of d, [4, 5, 6]
apply_along_axis(lambda x: (x[0]+x[-1])/2, 1, d)    # apply to each row (axis=1) of d, [2, 5, 8]

maximum(b, c)                                       # element-by-element comparison, [ 2.,  1.,  4.]
minimum(b, c)                                       # element-by-element comparison, [ 0., -1.,  2.]
median(array([1, 2, 3, 4, 9]))                      # 3.0
median(array([1, 2, 3, 4, 9, 0]))                   # 2.5
average(c)                                          # 1.6666666666666667
average(c, weights=w)                               # weighted average, 2.5
bincount(b)                                         # [1, 1, 1], 0 occur 1 times, 1 occur 1 times, 2 occur 1 times
bincount(b, weights=w)                              # weighted occurrence, [ 0.1,  0.2,  0.5]
ceil(w)                                             # nearest integers >= w, [ 1.,  1.,  1.]
floor(w)                                            # nearest integers <= w, [ 0.,  0.,  0.]
w.round()                                           # [ 0.,  0.,  0.]
round_(w)
around(w)
w.round(decimals=1)                                 # [ 0.1,  0.2,  0.5]
c.clip(min=1.0, max=3.0)                            # [ 2.,  1.,  3.]
clip(c, 1.0, 3.0)                                   # [ 2.,  1.,  3.]

corrcoef([T, P])                                    # correlation matrix [[ 1. ,  0.98062258], [ 0.98062258,  1. ]]
cov(T)                                              # 1.9758333333333333, variance, normalized by N-1
cov(T, bias=1)                                      # 1.481875, variance, normalized by N
cov(T, P)                                           # covariance, [[ 1.97583333,  3.95416667], [ 3.95416667,  8.22916667]]

booleans.all()                                      # False
all(booleans)                                       # False
all(b > 0)                                          # False
alltrue(booleans)                                   # False
sometrue(booleans)                                  # True
alltrue(b > 0)                                      # False
booleans.any()                                      # True
any(booleans)                                       # True
(b >= 1).any()                                      # True

# index based operation
indices = b.nonzero()                               # find the indices of the nonzero elements, [1, 2]
b[indices]                                          # get those nonzero elements, [1, 2]
