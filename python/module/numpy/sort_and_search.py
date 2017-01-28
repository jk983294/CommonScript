from numpy import *

# 1-d array sort
a = array([2, 0, 8, 4, 1])
ind = a.argsort(kind='merge')                   # options are 'quicksort', 'mergesort' and 'heapsort'
ind = a.argsort()                               # indices of sorted array using quicksort, [1, 4, 0, 3, 2]
ind = argsort(a)                                # there is a functional form
a[ind]                                          # sort result: [0, 1, 2, 4, 8]

# multi-dimension array sort
a = array([[8, 4, 1], [2, 0, 9]])
ind = a.argsort(axis=0)                         # sorts on columns. [[1, 1, 0], [0, 0, 1]]
a[ind, [[0, 1, 2], [0, 1, 2]]]                  # sort result: [[2, 0, 1], [8, 4, 9]]
ind = a.argsort(axis=1)                         # sort along rows. [[2, 1, 0], [1, 0, 2]]

# lexsort, sort by height, then width
serialnr = array([1023, 5202, 6230, 1671, 1682, 5241])
height = array([40., 42., 60., 60., 98., 40.])
width = array([50., 20., 70., 60., 15., 30.])
indices = lexsort(keys=(width, height))         # [5, 0, 1, 3, 2, 4]
for n in indices:
    print serialnr[n], height[n], width[n]

# alternatively: all data in one big matrix, sort on last row, then on 2nd last row, etc.
a = vstack([serialnr, width, height])
indices = lexsort(a)
a.take(indices, axis=-1)

# find max min
b = arange(3)                                       # [ 0, 1, 2 ]
d = array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
b.argmax()                                          # 1
idx = d.argmax(axis=0)                              # for each column: the row index of the maximum value, [2, 2, 2]
d[idx, xrange(d.shape[1])]                          # get max value of each column
idx = d.argmax(axis=1)                              # for each row: the row index of the maximum value, [2, 2, 2]
d[xrange(d.shape[0]), idx]                          # get max value of each row
b.argmin()                                          # 0
idx = d.argmin(axis=0)                              # for each column: the row index of the minimum value, [0, 0, 0]
d[idx, xrange(d.shape[1])]                          # get min value of each column
idx = d.argmin(axis=1)                              # for each row: the row index of the minimum value, [0, 0, 0]
d[xrange(d.shape[0]), idx]                          # get min value of each row

# where
a = array([3, 5, 7, 9])
b = array([10, 20, 30, 40])
c = array([2, 4, 6, 8])
d = array([[3, 5, 7, 9], [2, 4, 6, 8]])
where(a <= 6, b, c)                             # [10, 20,  6,  8]
where(a <= 6, b, -1)                            # [10, 20, -1, -1]
indices = where(a <= 6)                         # [0, 1]
b[indices]                                      # [10, 20]
b[a <= 6]                                       # [10, 20], an alternative syntax
where(d <= 6)                                   # [0, 0, 1, 1, 1], [0, 1, 0, 1, 2], (row indices, column indices)
