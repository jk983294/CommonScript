import numpy as np
from numpy import polyfit, poly1d


# 产生数据
x = np.linspace(-5, 5, 100)
y = 4 * x + 1.5
noise_y = y + np.random.randn(y.shape[-1]) * 2.5

# 多项式拟合函数，线性拟合即一阶多项式
coeff = polyfit(x, noise_y, 1)
print(coeff)
f = poly1d(coeff)
fitted_y = f(x)
print(f)
print(noise_y[0:5], fitted_y[0:5])
