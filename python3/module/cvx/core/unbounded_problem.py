import cvxpy as cp

x = cp.Variable()
prob = cp.Problem(cp.Minimize(x))
prob.solve()

print("status:", prob.status)    # status: unbounded
print("optimal value", prob.value)    # optimal value -inf
