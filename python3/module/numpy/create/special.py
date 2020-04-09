import numpy as np

a = np.array([1.2, 3.5, 5.1])  # float64
b = np.array([[3, 4, 5], [6, 7, 8]])  # int32
# complex128 [[ 1.+0.j,  2.+0.j], [ 3.+0.j,  4.+0.j]]
c = np.array([[1, 2], [3, 4]], dtype=complex)

# special
print(np.zeros((1, 2)))  # [[ 0.  0.]]
print(np.zeros_like(b))  # [[0 0 0], [0 0 0]]
print(np.ones((1, 2), dtype=np.int16))  # [[1 1]]
print(np.ones_like(b))  # [[1 1 1], [1 1 1]]
print(np.empty((1, 2)))  # initial content is random
print(np.empty_like(b))  # random garbage value
print(np.eye(2, dtype=float))  # [[ 1.  0.], [ 0.  1.]]
print(np.identity(2, float))  # [[ 1.,  0.], [ 0.,  1.]]
