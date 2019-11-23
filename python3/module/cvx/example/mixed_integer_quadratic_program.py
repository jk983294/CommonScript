import cvxpy as cp
import numpy as np

# minimize x^T*Q*x+q^T*x+r
# subject to x∈C x∈Zn

np.random.seed(0)
m, n = 40, 25
A = np.random.rand(m, n)
b = np.random.randn(m)

x = cp.Variable(n, integer=True)
objective = cp.Minimize(cp.sum_squares(A @ x - b))    # ||Ax−b||_2
prob = cp.Problem(objective)
prob.solve()

print("Status: ", prob.status)
print("The optimal value is", prob.value)
print("A solution x is")
print(x.value)
