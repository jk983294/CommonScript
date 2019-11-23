import cvxpy as cp
import numpy

# sign
x = cp.Variable()
a = cp.Parameter(nonpos=True)
c = numpy.array([1, -1])

print("sign of x:", x.sign)    # UNKNOWN
print("sign of a:", a.sign)    # NONPOSITIVE
print("sign of square(x):", cp.square(x).sign)    # NONNEGATIVE
print("sign of c*a:", (c * a).sign)    # UNKNOWN
