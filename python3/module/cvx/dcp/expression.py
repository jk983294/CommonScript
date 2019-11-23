import cvxpy as cp
import numpy

# variables and parameters
x, y = cp.Variable(), cp.Variable()
a, b = cp.Parameter(), cp.Parameter()

# expressions
3.69 + b / 3
x - 4 * a
cp.sqrt(x) - cp.minimum(y, x - a)
cp.maximum(2.66 - cp.sqrt(y), cp.square(x + 2 * y))
