from numpy import *

print(fromfunction(lambda i, j: i**2 + j**2, (2, 2)))  # [[ 0.,  1.], [ 1.,  2.]]
print(fromfunction(lambda i, j: i - j, (2, 2)))  # [[ 0. -1.], [ 1.  0.]]
