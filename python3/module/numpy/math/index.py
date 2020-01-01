import numpy as np

b = np.arange(3)
indices = b.nonzero()                               # find the indices of the nonzero elements, [1, 2]
print(b[indices])                                   # get those elements, [1, 2]
