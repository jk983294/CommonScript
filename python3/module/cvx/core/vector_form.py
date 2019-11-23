import cvxpy as cp
import numpy

# least square, make residual minimum
# min (A*x - b)^2  s.t. 0 <= x <= 1

m = 10
n = 2
numpy.random.seed(1)
A = numpy.random.randn(m, n)
b = numpy.random.randn(m)

x = cp.Variable(n)
objective = cp.Minimize(cp.sum_squares(A * x - b))
# cannot construct inequalities with < and >, strict inequalities don’t make sense in a real world setting
constraints = [0 <= x, x <= 1]
prob = cp.Problem(objective, constraints)
prob.solve()

print("status:", prob.status)    # optimal tells us the problem was solved successfully
print("optimal value", prob.value)    # optimal value
print("optimal var", x.value)    # where to achieve the optimal objective
