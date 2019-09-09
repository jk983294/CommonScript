from numpy import *
from numpy.linalg import *

a = array([[1.0, 2.0], [3.0, 4.0]])
j = array([[0.0, -1.0], [1.0, 0.0]])
y = array([[5.], [7.]])
a.transpose()                               # [[ 1.,  3.],  [ 2.,  4.]]
inv(a)                                      # [[-2. ,  1. ], [ 1.5, -0.5]]
u = eye(2)                                  # unit 2x2 matrix; [[ 1.,  0.], [ 0.,  1.]]
dot(j, j)                                   # matrix product, [[-1.,  0.], [ 0., -1.]]
trace(u)                                    # trace, 2.0
solve(a, y)                                 # [[-3.], [ 4.]]
eig(j)                                      # eigenvalues

# matrix class
M = mat(arange(12).reshape([3, 4]).copy())
M[:, 1]                                     # [[1], [5], [9]])
A = matrix('1.0 2.0; 3.0 4.0')              # [[ 1.  2.] [ 3.  4.]]
type(A)                                     # file where class is defined, 'numpy.matrixlib.defmatrix.matrix'
A.T                                         # transpose, [[ 1.  3.] [ 2.  4.]]
X = matrix('5.0 7.0')
Y = X.T                                     # [[5.] [7.]]
print(A*Y)                                   # matrix multiplication, [[19.] [43.]]
print(A.I)                                   # inverse, [[-2.   1. ] [ 1.5 -0.5]]
solve(A, Y)                                 # solving linear equation, matrix([[-3.], [ 4.]])
