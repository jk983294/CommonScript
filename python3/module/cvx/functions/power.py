import cvxpy as cp

x = cp.Variable((2, 3))
print("x..shape", x.shape)    # (2, 3)
print("x.T.shape", x.T.shape)    # (3, 2)
