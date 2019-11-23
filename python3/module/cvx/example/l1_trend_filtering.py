import numpy as np
import cvxpy as cp
import scipy as scipy
import matplotlib.pyplot as plt
import cvxopt as cvxopt

# Load time series data: S&P 500 price log
y = np.loadtxt(open('snp500.txt', 'rb'), delimiter=",", skiprows=1)
n = y.size

# Form second difference matrix.
e = np.ones((1, n))
D = scipy.sparse.spdiags(np.vstack((e, -2 * e, e)), range(3), n - 2, n)

# Set regularization parameter.
vlambda = 50

# Solve l1 trend filtering problem.
x = cp.Variable(shape=n)
obj = cp.Minimize(0.5 * cp.sum_squares(y - x) + vlambda * cp.norm(D * x, 1))
prob = cp.Problem(obj)

# ECOS and SCS solvers fail to converge before the iteration limit. Use CVXOPT instead.
prob.solve(solver=cp.CVXOPT, verbose=True)
print('Solver status: {}'.format(prob.status))

# Check for error.
if prob.status != cp.OPTIMAL:
    raise Exception("Solver did not converge!")

print("optimal objective value: {}".format(obj.value))

# plot properties
plt.rc('font', family='serif')
font = {'weight': 'normal', 'size': 16}
plt.rc('font', **font)

# plot estimated trend with original signal
plt.figure(figsize=(6, 6))
plt.plot(np.arange(1, n + 1), y, 'k:', linewidth=1.0)
plt.plot(np.arange(1, n + 1), np.array(x.value), 'b-', linewidth=2.0)
plt.xlabel('date')
plt.ylabel('log price')
plt.Text(0, 0.5, 'log price')
plt.show()
