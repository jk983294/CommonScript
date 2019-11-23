import cvxpy as cp

x = cp.Variable()
y = cp.Variable(pos=True)
objective_fn = -cp.sqrt(x) / y
problem = cp.Problem(cp.Minimize(objective_fn), [cp.exp(x) <= y])
problem.solve(qcp=True)    # indicate this is DGP problem
assert problem.is_dqcp()
print("Optimal value: ", problem.value)
print("x: ", x.value)
print("y: ", y.value)
