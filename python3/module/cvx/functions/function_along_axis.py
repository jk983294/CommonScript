import cvxpy as cp

X = cp.Variable((5, 4))
col_sums1 = cp.sum(X, axis=0, keepdims=True)    # Has size (1, 4)
col_sums2 = cp.sum(X, axis=0)    # Has size (4,)
row_sums = cp.sum(X, axis=1)    # Has size (5,)
