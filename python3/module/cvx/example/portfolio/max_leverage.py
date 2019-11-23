import numpy as np
import cvxpy as cp
import matplotlib.pyplot as plt
import scipy.stats as spstats

# w is the portfolio allocation vector, 1^T*w=1
# portfolio return is R=r^T*w, E[R]=μ^T*w and var(R)=w^T*Σ*w
# more leverage increases returns and allows greater risk

np.random.seed(1)
n = 10    # asset count
mu = np.abs(np.random.randn(n, 1))    # asset mean
Sigma = np.random.randn(n, n)
Sigma = Sigma.T.dot(Sigma)    # asset covariance

w = cp.Variable(n)
Lmax = cp.Parameter()
gamma = cp.Parameter(nonneg=True)    # risk aversion parameter, it gives the optimal risk-return trade-off
ret = mu.T * w
risk = cp.quad_form(w, Sigma)
prob = cp.Problem(cp.Maximize(ret - gamma * risk), [cp.sum(w) == 1, cp.norm(w, 1) <= Lmax])

# compute trade-off curve for each leverage limit.
L_vals = [1, 2, 4]
SAMPLES = 100
risk_data = np.zeros((len(L_vals), SAMPLES))
ret_data = np.zeros((len(L_vals), SAMPLES))
gamma_vals = np.logspace(-2, 3, num=SAMPLES)
w_vals = []
for k, L_val in enumerate(L_vals):
    for i in range(SAMPLES):
        Lmax.value = L_val
        gamma.value = gamma_vals[i]
        prob.solve(solver=cp.SCS)
        risk_data[k, i] = cp.sqrt(risk).value
        ret_data[k, i] = ret.value

# plot trade-off curves for each leverage limit.
for idx, L_val in enumerate(L_vals):
    plt.plot(risk_data[idx, :], ret_data[idx, :], label=r"$L^{\max}$ = %d" % L_val)
for w_val in w_vals:
    w.value = w_val
    plt.plot(cp.sqrt(risk).value, ret.value, 'bs')
plt.xlabel('Standard deviation')
plt.ylabel('Return')
plt.legend(loc='lower right')
plt.show()
