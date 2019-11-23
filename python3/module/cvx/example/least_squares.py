import cvxpy as cp
import numpy as np

# minimize ||Ax−b||^2 -> x*

m = 20
n = 15
np.random.seed(1)
A = np.random.randn(m, n)
b = np.random.randn(m)

x = cp.Variable(n)
cost = cp.sum_squares(A * x - b)
prob = cp.Problem(cp.Minimize(cost))
prob.solve()

print("\nThe optimal value is", prob.value)
print("The optimal x is")
print(x.value)
print("The norm of the residual is ", cp.norm(A * x - b, p=2).value)
