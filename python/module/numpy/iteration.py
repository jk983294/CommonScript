from numpy import *

a = arange(10)**3                   # [  0,   1,   8,  27,  64, 125, 216, 343, 512, 729]
b = fromfunction(lambda x, y: 10 * x + y, (5, 4), dtype=int)

# iterating 1-d array
for i in a:
    print i**(1/3.),

# xrange is faster than range, xrange is a sequence object that evaluates lazily
for i in xrange(0, 20):
    print i,

for i in range(0, 20):
    print i,

# iterating over multidimensional arrays
for row in b:
    print row

# iterating over multidimensional arrays and perform an operation on each element
for element in b.flat:
    print element,

# index & slice
a[2]                                # 8
a[[1, 2, 3]]                        # [ 1,  8, 27]
idx = array([[1, 2], [2, 3]])       # a bidimensional array of indices
a[idx]                              # the same shape as idx, [[ 1,  8], [ 8, 27]]
a[2:5]                              # [ 8, 27, 64]
a[:6:2] = -1000                     # [-1000,     1, -1000,    27, -1000,   125,   216,   343,   512,   729], equivalent to a[0:6:2] = -1000; from start to position 6, exclusive, set every 2nd element to -1000
b[2, 3]
b[0:5, 1]                           # second column of b
b[:, 1]                             # second column of b
b[1:3, :]                           # second and third row of b
b[-1]                               # the last row. Equivalent to b[-1,:]
i = array([[0, 1],  [1, 2]])        # indices for the first dim of a
j = array([[2, 1], [3, 3]])         # indices for the second dim of a
b[i, j]

# ... represent as many colons as needed to produce a complete indexing tuple
# if x is a rank 5 array (i.e., it has 5 axes), then
# x[1,2,...] = x[1,2,:,:,:]
# x[...,3] = x[:,:,:,:,3]
# x[4,...,5,:] = x[4,:,:,5,:]


# reverse
a[::-1]                             # [  729,   512,   343,   216,   125, -1000,    27, -1000,     1, -1000]
