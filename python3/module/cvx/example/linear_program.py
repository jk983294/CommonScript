import cvxpy as cp
import numpy as np

# minimize c^T*x  subject to Ax≤b

m = 15
n = 10
np.random.seed(1)
s0 = np.random.randn(m)
lamb0 = np.maximum(-s0, 0)
s0 = np.maximum(s0, 0)
x0 = np.random.randn(n)
A = np.random.randn(m, n)
b = A @ x0 + s0    # s0 is noise
c = -A.T @ lamb0

x = cp.Variable(n)
prob = cp.Problem(cp.Minimize(c.T @ x), [A @ x <= b])
prob.solve()

print("\nThe optimal value is", prob.value)
print("A solution x is")
print(x.value)
print("original x is")    # used to generate the problem
print(x0)
print("A dual solution is")
print(prob.constraints[0].dual_value)
