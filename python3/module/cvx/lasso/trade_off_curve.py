import cvxpy as cp
import numpy
import matplotlib.pyplot as plt

n = 15
m = 10
numpy.random.seed(1)
A = numpy.random.randn(n, m)
b = numpy.random.randn(n)
gamma = cp.Parameter(nonneg=True)    # gamma must be non-negative due to DCP rules

x = cp.Variable(m)
error = cp.sum_squares(A * x - b)
obj = cp.Minimize(error + gamma * cp.norm(x, 1))
prob = cp.Problem(obj)

# Construct a trade-off curve of ||Ax-b||^2 vs. ||x||_1
sq_penalty = []
l1_penalty = []
x_values = []
gamma_values = numpy.logspace(-4, 6)
for val in gamma_values:
    gamma.value = val
    prob.solve()
    # use expr.value to get the numerical value of an expression in the problem.
    sq_penalty.append(error.value)
    l1_penalty.append(cp.norm(x, 1).value)
    x_values.append(x.value)

plt.rc('text')    # plt.rc('text', usetex=True)
plt.rc('font', family='serif')
plt.figure(figsize=(6, 10))

# plot trade-off curve
plt.subplot(211)
plt.plot(l1_penalty, sq_penalty)
plt.xlabel(r'|x|_1', fontsize=16)
plt.ylabel(r'|Ax-b|^2', fontsize=16)
plt.title('Trade-Off Curve for LASSO', fontsize=16)

# plot entries of x vs. gamma
plt.subplot(212)
for i in range(m):
    plt.plot(gamma_values, [xi[i] for xi in x_values])
plt.xlabel(r'gamma', fontsize=16)
plt.ylabel(r'x_{i}', fontsize=16)
plt.xscale('log')
plt.title(r'Entries of x vs. gamma', fontsize=16)

plt.tight_layout()
plt.show()
