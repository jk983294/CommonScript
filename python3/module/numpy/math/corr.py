import numpy as np

T = np.array([1.3, 4.5, 2.8, 3.9])
P = np.array([2.7, 8.7, 4.7, 8.2])

print(np.corrcoef([T, P]))          # correlation matrix [[ 1. ,  0.98062258], [ 0.98062258,  1. ]]
print(np.cov(T))                    # 1.9758333333333333, variance, normalized by N-1
print(np.cov(T, bias=True))         # 1.481875, variance, normalized by N
print(np.cov(T, P))                 # covariance, [[ 1.97583333,  3.95416667], [ 3.95416667,  8.22916667]]
