import numpy as np

a = np.array([[1, 2], [3, 4]])

# statistics with whole data
print(a.sum())                                          # 10
print(a.min())                                          # 1
print(a.max())                                          # 4
print('argmin()', a.argmin())                           # 0
print('argmax()', a.argmax())                           # 3
print(a.mean())                                         # 2.5
print(a.std())                                          # 1.1180339887498949, normalized by N (not N-1)
print(a.var())                                          # 1.25, normalised with N (not N-1)
print(a.prod())                                         # 24
print(np.median(a))                                     # 2.5
print(np.average(a))                                    # 2.5
print(np.average(a, weights=np.array([[0.1, 0.2], [0.3, 0.4]])))    # 3.0
print('ptp', a.ptp())                                   # 3, 计算最大值和最小值之差

# statistics column-wise, 沿着第一维
print(a.sum(axis=0))                                    # [4, 6]
print(a.min(axis=0))                                    # [1, 2]
print(a.max(axis=0))                                    # [3, 4]
print('argmin(axis=0)', a.argmin(axis=0))               # [0 0]
print('argmax(axis=0)', a.argmax(axis=0))               # [1 1]
print(a.mean(axis=0))                                   # [ 2.,  3.]
print(a.std(axis=0))                                    # [ 1.,  1.]
print(a.var(axis=0))                                    # [ 1.,  1.]
print(a.prod(axis=0))                                   # [3, 8]
print('average(axis=0)', np.average(a, axis=0))         # [1.5 3.5]
print('ptp', a.ptp(axis=0))                             # [2 2], 计算最大值和最小值之差

# statistics row-wise, 沿着第二维
print(a.sum(axis=1))                                    # [3 7]
print(a.min(axis=1))                                    # [1 3]
print(a.max(axis=1))                                    # [2 4]
print('argmin(axis=1)', a.argmin(axis=1))               # [0 0]
print('argmax(axis=1)', a.argmax(axis=1))               # [1 1]
print(a.mean(axis=1))                                   # [ 1.5  3.5]
print(a.std(axis=1))                                    # [ 0.5  0.5]
print(a.var(axis=1))                                    # [ 0.25  0.25]
print(a.prod(axis=1))                                   # [ 2 12]
print('average(axis=1)', np.average(a, axis=1))         # [1.5 3.5]
print('ptp', a.ptp(axis=1))                             # [1 1], 计算最大值和最小值之差

# apply
print(np.apply_along_axis(lambda x: (x[0]+x[-1])/2, 0, a))    # [ 2.  3.], apply to each column
print(np.apply_along_axis(lambda x: (x[0]+x[-1])/2, 1, a))    # [ 1.5  3.5], apply to each row
