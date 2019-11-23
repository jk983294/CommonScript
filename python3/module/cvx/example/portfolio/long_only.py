import numpy as np
import cvxpy as cp
import matplotlib.pyplot as plt
import scipy.stats as spstats

# w is the portfolio allocation vector, 1^T*w=1, w ≥ 0 is a long only portfolio
# portfolio return is R=r^T*w, E[R]=μ^T*w and var(R)=w^T*Σ*w

np.random.seed(1)
n = 10    # asset count
mu = np.abs(np.random.randn(n, 1))    # asset mean
Sigma = np.random.randn(n, n)
Sigma = Sigma.T.dot(Sigma)    # asset covariance

w = cp.Variable(n)
gamma = cp.Parameter(nonneg=True)    # risk aversion parameter, it gives the optimal risk-return trade-off
ret = mu.T * w
risk = cp.quad_form(w, Sigma)
prob = cp.Problem(cp.Maximize(ret - gamma * risk), [cp.sum(w) == 1, w >= 0])    # Long only portfolio optimization

# compute trade-off curve.
SAMPLES = 100
risk_data = np.zeros(SAMPLES)
ret_data = np.zeros(SAMPLES)
gamma_vals = np.logspace(-2, 3, num=SAMPLES)
for i in range(SAMPLES):
    gamma.value = gamma_vals[i]
    prob.solve()
    risk_data[i] = cp.sqrt(risk).value
    ret_data[i] = ret.value

# plot long only trade-off curve
fig = plt.figure()
ax = fig.add_subplot(111)
plt.plot(risk_data, ret_data, 'g-')
markers_on = [29, 40]
for marker in markers_on:
    plt.plot(risk_data[marker], ret_data[marker], 'bs')
    ax.annotate(r"$\gamma = %.2f$" % gamma_vals[marker], xy=(risk_data[marker] + .08, ret_data[marker] - .03))
for i in range(n):
    plt.plot(cp.sqrt(Sigma[i, i]).value, mu[i], 'ro')
plt.xlabel('Standard deviation')
plt.ylabel('Return')
plt.show()

# plot return distributions for two points on the trade-off curve
# high gamma means we want small return with low risk
plt.figure()
for midx, idx in enumerate(markers_on):
    gamma.value = gamma_vals[idx]
    prob.solve()
    x = np.linspace(-2, 5, 1000)
    plt.plot(x, spstats.norm.pdf(x, ret.value, risk.value), label=r"$\gamma = %.2f$" % gamma.value)

plt.xlabel('Return')
plt.ylabel('Density')
plt.legend(loc='upper right')
plt.show()
