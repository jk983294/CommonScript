from numba import jit, int32


@jit(int32(int32, int32))
def f(x, y):
    return x + y


print(f(1, 2))
