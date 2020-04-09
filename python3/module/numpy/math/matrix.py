import numpy as np
import numpy.linalg as la

a = np.array([[1.0, 2.0], [3.0, 4.0]])          # 2 * 2
j = np.array([[0.0, -1.0], [1.0, 0.0]])         # 2 * 2
y = np.array([[5.], [7.]])                      # 2 * 1


print(a.transpose())                            # [[ 1.,  3.],  [ 2.,  4.]]
print(la.inv(a))                                # [[-2. ,  1. ], [ 1.5, -0.5]]
print(np.dot(j, j))                             # matrix product, [[-1.,  0.], [ 0., -1.]]
print(np.trace(a))                              # trace, 5.0
print(np.diagonal(a))                           # [ 1.  4.]
print(la.solve(a, y))                           # [[-3.], [ 4.]]
print(la.eig(a))                                # (eigen vector, eigen values)

# matrix class
print(np.mat(np.arange(6).reshape([2, 3])))     # [[0 1 2] [3 4 5]]

A = np.mat('1.0 2.0; 3.0 4.0')                  # [[ 1.  2.] [ 3.  4.]]
print(A)                                        # [[ 1.  2.] [ 3.  4.]]
print(A.T)                                      # transpose, [[ 1.  3.] [ 2.  4.]]
print('A.I', A.I)                               # 逆矩阵, [[-2. 1. ], [ 1.5 -0.5]]

X = np.mat('5.0 7.0')                           # 1 * 2
Y = X.T                                         # 2 * 1, [[5.] [7.]]
print(A*Y)                                      # matrix multiplication, [[19.] [43.]]
print(A.I)                                      # inverse, [[-2.   1. ] [ 1.5 -0.5]]
print(la.solve(A, Y))                           # solving linear equation, matrix([[-3.], [ 4.]])
