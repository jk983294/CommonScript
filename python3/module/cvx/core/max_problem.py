import cvxpy as cp

# max x + y  s.t. x + y = 1, x - y >= 1

x = cp.Variable()
y = cp.Variable()
constraints = [x + y == 1, x - y >= 1]
objective = cp.Maximize(x + y)

prob = cp.Problem(objective, constraints)
prob.solve()

print("status:", prob.status)    # optimal tells us the problem was solved successfully
print("optimal value", prob.value)    # optimal value
print("optimal var", x.value, y.value)    # where to achieve the optimal objective

# change constraints, max x + y  s.t. x + y <= 3, x - y >= 1
constraints = [x + y <= 3] + prob.constraints[1:]
prob2 = cp.Problem(prob.objective, constraints)
print("optimal value", prob2.solve())
