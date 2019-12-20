import numpy as np


def my_func(x):
    if x >= 0:
        return x**2
    else:
        return -x


my_func(2.)                                             # 4.0
vec_func = np.vectorize(my_func, otypes=[float])        # declare the return type as float
print(vec_func(np.array([-2, 2])))                      # [ 2.,  4.]
