import numpy as np
import cvxpy as cp
import matplotlib.pyplot as plt
import scipy.stats as spstats

# maximize μ^T*w−γ(f^T*Σ*f+w^T*D*w) subject to 1^T*w=1,f=F^T*w

n = 300    # asset number
m = 50    # factor number
np.random.seed(1)
mu = np.abs(np.random.randn(n, 1))    # asset expected return
Sigma_tilde = np.random.randn(m, m)
Sigma_tilde = Sigma_tilde.T.dot(Sigma_tilde)    # factor covariance matrix
D = np.diag(np.random.uniform(0, 0.9, size=n))    # diagonal matrix, D_ii>0 is the idiosyncratic risk
F = np.random.randn(n, m)    # factor loading matrix, Fij is the loading of asset i to factor j

# Factor model portfolio optimization.
w = cp.Variable(n)
f = F.T * w
gamma = cp.Parameter(nonneg=True)
Lmax = cp.Parameter()    # leverage limit
ret = mu.T * w
risk = cp.quad_form(f, Sigma_tilde) + cp.quad_form(w, D)
prob_factor = cp.Problem(cp.Maximize(ret - gamma * risk), [cp.sum(w) == 1, cp.norm(w, 1) <= Lmax])

# Solve the factor model problem.
Lmax.value = 2
gamma.value = 0.1
prob_factor.solve(verbose=True)

# Standard portfolio optimization with data from factor model.
risk = cp.quad_form(w, F.dot(Sigma_tilde).dot(F.T) + D)
prob = cp.Problem(cp.Maximize(ret - gamma * risk), [cp.sum(w) == 1, cp.norm(w, 1) <= Lmax])

# Uncomment to solve the problem
prob.solve(verbose=True)

print('Factor model solve time = {}'.format(prob_factor.solver_stats.solve_time))
print('Single model solve time = {}'.format(prob.solver_stats.solve_time))
