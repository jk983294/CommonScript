import numpy as np
from scipy.stats import linregress


# 产生数据
x = np.linspace(-5, 5, 100)
y = 4 * x + 1.5
noise_y = y + np.random.randn(y.shape[-1]) * 2.5

# 最小二乘拟合
slope, intercept, r_value, p_value, stderr = linregress(x, noise_y)
print(slope, intercept, r_value, p_value, stderr)