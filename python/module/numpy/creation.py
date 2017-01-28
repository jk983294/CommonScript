from numpy import *
from numpy.random import *

# merge
vstack([[1, 2], [3, 4], [5, 6]])                                    # [[1, 2], [3, 4], [5, 6]]
hstack([[1, 2], [3, 4], [5, 6]])                                    # [1, 2, 3, 4, 5, 6]
concatenate(([[1, 2], [3, 4]], [[5, 6], [7, 8]]))                   # [[1, 2], [3, 4], [5, 6], [7, 8]]
concatenate(([[1, 2], [3, 4]], [[5, 6], [7, 8]]), axis=1)           # [[1, 2, 5, 6], [3, 4, 7, 8]]
# column_stack stacks 1D arrays as columns into a 2D array. It is equivalent to vstack only for 1D arrays
column_stack([[1, 2], [3, 4], [5, 6]])                              # [[1, 3, 5], [2, 4, 6]]
row_stack([[1, 2], [3, 4], [5, 6]])                                 # [[1, 2], [3, 4], [5, 6]]
# r_[] and c_[] are useful for creating arrays by stacking numbers along one axis. they allow the use of range literals (":")
r_[1:5]                                                             # same as arange(1,5), [1, 2, 3, 4]
r_[1:10:4]                                                          # same as arange(1,10,4), [1, 5, 9]
r_[1:10:4j]                                                         # same as linspace(1,10,4), [ 1., 4., 7., 10.]
r_[1:5, 7, 1:10:4]                                                  # [1, 2, 3, 4, 7, 1, 5, 9]
r_['r', 1:3]                                                        # return a matrix. [[1, 2]]
r_['c', 1:3]                                                        # return a matrix. [[1], [2]]
r_[[[1, 2], [4, 5]], [[1, 2], [4, 5]]]                              # concatenation along row, [1, 2], [4, 5], [1, 2], [4, 5]]
r_['-1', [[1, 2], [4, 5]], [[1, 2], [4, 5]]]                        # concatenation along column, [[1, 2, 1, 2], [4, 5, 4, 5]]
c_[1:5]                                                             # [1, 2, 3, 4]
c_[1:5, 2:6]                                                        # [[1, 2], [2, 3], [3, 4], [4, 5]]

# split
a = array([[3, 4, 5], [6, 7, 8]])
hsplit(a, 3)                                                        # [[3], [6]], [[4], [7]], [[5], [8]]
hsplit(a, [1, 2])                                                   # split along with column 1 and 2, [[3], [6]], [[4], [7]], [[5], [8]]
b = array([[3, 4], [5, 6], [7, 8]])
vsplit(b, 3)                                                        # [[3, 4]], [[5, 6]], [[7, 8]]
vsplit(b, [1, 2])                                                   # split along with row 1 and 2, [[3, 4]], [[5, 6]], [[7, 8]]
array_split(a, 2, axis=0)                                           # split a in 2 parts. row-wise
array_split(a, 3, axis=1)                                           # split a in 4 parts, column-wise
array_split(a, [1, 2], axis=1)                                      # make a split before the 1st and the 2nd column

# Array Creation
b = array([1.2, 3.5, 5.1])
b = array([[3, 4, 5], [6, 7, 8]])
b = array([(1.5, 2, 3), (4, 5, 6)])
c = array([[1, 2], [3, 4]], dtype=complex)                          # [[ 1.+0.j,  2.+0.j], [ 3.+0.j,  4.+0.j]]

zeros((1, 2))                                                       # zeros creates an array full of zeros
zeros_like(b)                                                       # with zeros initialised array with the same shape and datatype as b
ones((1, 2, 3), dtype=int16)                                        # ones creates an array full of ones
ones_like(b)                                                        # ones initialised array with the same shape and datatype as b
empty((1, 2))                                                       # empty creates an array whose initial content is random
empty_like(b)                                                       # uninitialized array with the same shape and datatype as b
eye(1, 2, 0, dtype=float)                                           # [[ 1.,  0.]]
eye(1, 2, 1, dtype=float)                                           # [[ 0.,  1.]]
identity(2, float)                                                  # [[ 1.,  0.], [ 0.,  1.]]

arange(6)                                                           # [0, 1, 2, 3, 4, 5]
arange(6).reshape(1, 2, 3)                                          # [[[0, 1, 2], [3, 4, 5]]]
arange(10, 30, 5)                                                   # start, end, step, [10, 15, 20, 25]
arange(0, 2, 0.3)                                                   # [ 0. ,  0.3,  0.6,  0.9,  1.2,  1.5,  1.8]

linspace(0, 2, 5)                                                   # start, end, count, [ 0. ,  0.5,  1. ,  1.5,  2. ]
x = linspace(0, 2*pi, 100)                                          # useful to evaluate function at lots of points
f = sin(x)

fromfunction(lambda i, j: i**2 + j**2, (2, 2))                      # evaluate functiom, [[ 0.,  1.], [ 1.,  2.]]

y = array([2., 4., 6., 8.])
y.tofile("myfile.dat")                                              # binary format
fromfile('myfile.dat', dtype=float)                                 # array([ 2., 4., 6., 8.])

y.tofile("myfile.txt", sep='\n', format="%e")                       # ascii format, one column, exponential notation
fromfile('myfile.txt', dtype=float, sep='\n')

rand(2, 1)                                                          # uniform distribution, [[ 0.83604898], [ 0.79689486]]
randn(2, 1)                                                         # standard normal distribution, [[ 0.29441506], [-0.49656679]]
random_integers(-5, 5, (2, 2))                                      # [[ 2, -5], [ 2,  4]]
random_sample((2, 2))                                               # range [0.0, 1.0)
