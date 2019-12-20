from numpy import *

a = array([1.2, 3.5, 5.1])                      # float64
b = array([[3, 4, 5], [6, 7, 8]])               # int32
c = array([[1, 2], [3, 4]], dtype=complex)      # complex128 [[ 1.+0.j,  2.+0.j], [ 3.+0.j,  4.+0.j]]

# special
print(zeros((1, 2)))                                                    # [[ 0.  0.]]
print(zeros_like(b))                                                    # [[0 0 0], [0 0 0]]
print(ones((1, 2), dtype=int16))                                        # [[1 1]]
print(ones_like(b))                                                     # [[1 1 1], [1 1 1]]
print(empty((1, 2)))                                                    # initial content is random
print(empty_like(b))                                                    # random garbage value
print(eye(2, dtype=float))                                              # [[ 1.  0.], [ 0.  1.]]
print(identity(2, float))                                               # [[ 1.,  0.], [ 0.,  1.]]
