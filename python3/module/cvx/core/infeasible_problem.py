import cvxpy as cp

x = cp.Variable()
prob = cp.Problem(cp.Minimize(x), [x >= 1, x <= 0])
prob.solve()

print("status:", prob.status)    # status: infeasible
print("optimal value", prob.value)    # optimal value inf
