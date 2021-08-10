import numpy as np

a = np.array([[1.1, 2.1], [np.nan, np.nan], [3.6, 4.7]])

col_mean = np.nanmean(a, axis=0)
col_sd = np.nanstd(a, axis=0)
print(col_mean, col_sd)

normed = (a - col_mean) / col_sd
np.nan_to_num(normed, copy=False, nan=0.0)
print(normed)

print(np.count_nonzero(~np.isnan(normed)))  # non nan count
print(np.count_nonzero(np.isnan(normed)))  # nan count

b = np.array([1.1, 2.1])
c = np.nanmean(b)
print(c)
