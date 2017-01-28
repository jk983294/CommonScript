from numpy import *
from numpy.random import *

a = floor(10*random((3, 4)))            # [[ 2.,  8.,  4.,  2.], [ 6.,  5.,  6.,  3.], [ 1.,  8.,  6.,  6.]]
a.shape                                 # (3, 4)
a.ravel()                               # flatten the array
a.shape = (6, 2)                        # [[ 2.,  8.], [ 4.,  2.], [ 6.,  5.], [ 6.,  3.], [ 1.,  8.], [ 6.,  6.]]

# reshape return a new matrix, while resize change itself
a.resize((2, 6))                        # [[ 7.,  5.,  9.,  3.,  7.,  2.], [ 7.,  8.,  6.,  8.,  3.,  2.]]
# if a dimension is given as -1 in a reshaping operation, the other dimensions are automatically calculated
a.reshape(3, -1)                        # [[ 7.,  5.,  9.,  3.], [ 7.,  2.,  7.,  8.], [ 6.,  8.,  3.,  2.]]
# -1 means "whatever is needed"
a.shape = 2, -1, 3                      # [[[ 7.,  3.,  5.], [ 9.,  5.,  3.]], [[ 9.,  7.,  6.], [ 3.,  5.,  5.]]]
