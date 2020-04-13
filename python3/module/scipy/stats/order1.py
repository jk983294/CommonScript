import numpy as np
import scipy as sp
import scipy.stats.stats as st

heights = np.array([1.46, 1.79, 2.01, 1.75, 1.56, 1.69, 1.88, 1.76, 1.88, 1.78])

print('mean', heights.mean())
print('min', heights.min())
print('max', heights.max())
print('standard deviation', heights.std())

print('mode', st.mode(heights))             # 众数及其出现次数
print('skewness', st.skew(heights))         # 偏度
print('kurtosis', st.kurtosis(heights))     # 峰度
