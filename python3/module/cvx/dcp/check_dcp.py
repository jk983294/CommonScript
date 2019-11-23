import cvxpy as cp

# If a problem follows the DCP rules, it is guaranteed to be convex and solvable by CVXPY
x = cp.Variable()
y = cp.Variable()

# DCP problems.
prob1 = cp.Problem(cp.Minimize(cp.square(x - y)), [x + y >= 0])
prob2 = cp.Problem(cp.Maximize(cp.sqrt(x - y)), [2 * x - 3 == y, cp.square(x) <= 2])
print("prob1 is DCP:", prob1.is_dcp())    # True
print("prob2 is DCP:", prob2.is_dcp())    # True

# A non-DCP objective.
obj = cp.Maximize(cp.square(x))
prob3 = cp.Problem(obj)
print("prob3 is DCP:", prob3.is_dcp())    # False
print("Maximize(square(x)) is DCP:", obj.is_dcp())    # False

# A non-DCP constraint.
prob4 = cp.Problem(cp.Minimize(cp.square(x)), [cp.sqrt(x) <= 2])
print("prob4 is DCP:", prob4.is_dcp())    # False
print("sqrt(x) <= 2 is DCP:", (cp.sqrt(x) <= 2).is_dcp())    # False
