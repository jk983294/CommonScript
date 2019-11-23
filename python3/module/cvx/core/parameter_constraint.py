import cvxpy as cp
import numpy

# Parameters
x = cp.Variable()
y = cp.Variable()
m = cp.Parameter(nonneg=True)    # positive scalar parameter
rho = cp.Parameter(nonneg=True, value=2)    # initialize a parameter with a value
c = cp.Parameter(5)    # column vector parameter with unknown sign (by default)
G = cp.Parameter((2, 3), nonpos=True)    # matrix parameter with negative entries
G.value = -numpy.ones((2, 3))    # assigns a constant value to G

# attributes
z1 = cp.Variable(nonneg=True)    # nonnegative
z2 = cp.Variable(nonpos=True)    # nonpositive
z3 = cp.Variable((2, 2), symmetric=True)    # symmetric
z4 = cp.Variable((2, 2), PSD=True)    # symmetric positive semidefinite
z5 = cp.Variable((2, 2), NSD=True)    # symmetric negative semidefinite
z6 = cp.Variable(2, boolean=True)    # 0 or 1
z7 = cp.Variable(2, integer=True)    # integer

# Constraints
# !!! You cannot construct inequalities with < and >. Strict inequalities don't make sense in a real world setting
constraints1 = [x + y == 1, x - y >= 1, x - y <= 2]
constraints = [0 <= c, c <= 1]
