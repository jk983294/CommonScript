import cvxpy as cp

x = cp.Variable(5)
print("0 dimensional", x[0].shape)    # ()
print("1 dimensional", x[0:2].shape)    # (2,)
