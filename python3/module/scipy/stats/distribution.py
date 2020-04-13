import numpy as np
import scipy as sp
import matplotlib.pyplot as plt
import scipy.stats.stats as st
from scipy.stats import norm

# norm.cdf      返回对应的累计分布函数值
# norm.pdf      返回对应的概率密度函数值
# norm.rvs      产生指定参数的随机变量
# norm.fit      返回给定数据下，各参数的最大似然估计（MLE）值

x_norm = sp.stats.norm.rvs(size=500)

x_mean, x_std = norm.fit(x_norm)
print('mean', x_mean)
print('std', x_std)

h = plt.hist(x_norm, normed=True, bins=20)  # scale down to norm dist
print('counts', h[0])
print('bin centers', h[1])
x = np.linspace(-3, 3, 50)
p = plt.plot(x, norm.pdf(x), 'r-')
plt.show()


