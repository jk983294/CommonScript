import numpy as np
from scipy.stats import skew, kurtosis

print(np.random.rand(2, 1))  # uniform, [[ 0.83604898], [ 0.79689486]]
print(np.random.randn(2, 1))  # gaussian, [[ 0.29441506], [-0.49656679]]
# discrete uniform, [[ 2, -5], [ 2,  4]]
print(np.random.random_integers(-5, 5, (2, 2)))
print(np.random.random_sample((2, 2)))  # sample from uniform [0.0, 1.0)

a = np.random.normal(0, 10, 100000)
a[1] = 1000
print('skewness of normal distribution (should be 0): {}'.format(skew(a)))
print('kurtosis of normal distribution (should be 0): {}'.format(kurtosis(a)))
