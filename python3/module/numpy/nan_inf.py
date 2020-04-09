import numpy as np

print(np.isinf(1.0))  # False
print(np.isinf(np.inf))  # True
print(np.isinf(-np.inf))  # True

# 只有 0/0 会得到 nan，非0值除以0会得到无穷
print(np.array([0]) / 0.0)  # [nan]
print(np.array([1]) / 0.0)  # [inf]

# nan 与任何数进行比较都是 False
a = np.arange(5.0)
b = a / 0.0
print(b == np.nan)  # [False False False False False]
print(np.isnan(b))  # [True False False False False]
