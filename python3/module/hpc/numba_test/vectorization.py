from numba import guvectorize, vectorize, int32, int64, float32, float64
import numpy as np


# ufuncs automatically get other features such as reduction, accumulation or broadcasting
@vectorize([int32(int32, int32), int64(int64, int64),
            float32(float32, float32), float64(float64, float64)])
def f(x, y):
    return x + y


a = np.arange(6)
print(f(a, a))
a = np.linspace(0, 1, 6)
print(f(a, a))
a = np.arange(12).reshape(3, 4)
print(f.reduce(a, axis=0))
print(f.reduce(a, axis=1))
print(f.accumulate(a))
print(f.accumulate(a, axis=1))


@guvectorize([(int64[:], int64, int64[:])], '(n),()->(n)')
def g(x, y, res):
    for i in range(x.shape[0]):
        res[i] = x[i] + y


a = np.arange(5)
print(g(a, 2))
a = np.arange(6).reshape(2, 3)
print(g(a, 10))
