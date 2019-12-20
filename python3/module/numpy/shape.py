import numpy as np

a = np.arange(12).reshape(3, 4)
print(a)                                # [[ 0  1  2  3] [ 4  5  6  7] [ 8  9 10 11]]
print(a.shape)                          # (3, 4)
a.ravel()                               # flatten to 1d
a.shape = (6, 2)
print(a)                                # [[ 0  1] [ 2  3] [ 4  5] [ 6  7] [ 8  9] [10 11]]

# reshape return a new matrix, while resize change itself
a.resize((2, 6))
print(a)                                # [[ 0  1  2  3  4  5] [ 6  7  8  9 10 11]]
# -1 dimension will be automatically calculated
a.reshape(3, -1)
print(a.reshape(3, -1))                 # [[ 0  1  2  3] [ 4  5  6  7] [ 8  9 10 11]]
# -1 means "whatever is needed"
a.shape = 2, -1, 3
print(a)                                # [[[ 0  1  2] [ 3  4  5]] [[ 6  7  8] [ 9 10 11]]]
