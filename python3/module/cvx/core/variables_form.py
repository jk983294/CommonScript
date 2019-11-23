import cvxpy as cp

# min (x - y)^2  s.t. x + y = 1, x - y >= 1

x = cp.Variable()
y = cp.Variable()
constraints = [x + y == 1, x - y >= 1]
objective = cp.Minimize((x - y)**2)

prob = cp.Problem(objective, constraints)
prob.solve()

print(
    'available status:', cp.OPTIMAL, cp.INFEASIBLE, cp.UNBOUNDED, cp.OPTIMAL_INACCURATE, cp.INFEASIBLE_INACCURATE,
    cp.UNBOUNDED_INACCURATE
)
print("status:", prob.status)    # optimal tells us the problem was solved successfully
print("optimal value", prob.value)    # optimal value
print("optimal var", x.value, y.value)    # where to achieve the optimal objective
