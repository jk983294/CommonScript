import cvxpy as cp
import numpy

# attribute
X = cp.Variable((5, 4))
A = numpy.ones((3, 5))
expression = A * X
print("dimensions of X:", X.shape)    # (5, 4)
print("size of X:", X.size)    # 20
print("number of dimensions:", X.ndim)    # 2
print("dimensions of sum(X):", cp.sum(X).shape)    # ()
print("dimensions of A*X:", expression.shape)    # (3, 4)
