import cvxpy as cp

x = cp.Variable()
y = cp.Variable()

constraints = [x + y == 1, x - y >= 1]
obj = cp.Minimize((x - y)**2)

prob = cp.Problem(obj, constraints)
prob.solve()

# The optimal dual variable (Lagrange multiplier) for a constraint is stored in constraint.dual_value.
print("optimal (x + y == 1) dual variable", constraints[0].dual_value)
print("optimal (x - y >= 1) dual variable", constraints[1].dual_value)
print("x - y value:", (x - y).value)
