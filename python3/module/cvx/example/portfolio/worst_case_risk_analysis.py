import numpy as np
import cvxpy as cp
import matplotlib.pyplot as plt
import scipy.stats as spstats

# return covariance Σ is not known
# maximize w^T*Σ*w

np.random.seed(2)
n = 5
mu = np.abs(np.random.randn(n, 1)) / 15
Sigma = np.random.uniform(-.15, .8, size=(n, n))
Sigma_nom = Sigma.T.dot(Sigma)
print("Sigma_nom =")
print(np.round(Sigma_nom, decimals=2))

# Form and solve portfolio optimization problem.
# Here we minimize risk while requiring a 0.1 return.
w = cp.Variable(n)
ret = mu.T * w
risk = cp.quad_form(w, Sigma_nom)
prob = cp.Problem(cp.Minimize(risk), [cp.sum(w) == 1, ret >= 0.1, cp.norm(w, 1) <= 2])
prob.solve()
print("w =")
print(np.round(w.value, decimals=2))

# Form and solve worst-case risk analysis problem.
Sigma = cp.Variable((n, n), PSD=True)
Delta = cp.Variable((n, n), symmetric=True)
risk = cp.quad_form(w.value, Sigma)
prob = cp.Problem(cp.Maximize(risk), [Sigma == Sigma_nom + Delta, cp.diag(Delta) == 0, cp.abs(Delta) <= 0.2])
prob.solve()
print("standard deviation =", cp.sqrt(cp.quad_form(w.value, Sigma_nom)).value)
print("worst-case standard deviation =", cp.sqrt(risk).value)
print("worst-case Delta =")
print(np.round(Delta.value, decimals=2))
