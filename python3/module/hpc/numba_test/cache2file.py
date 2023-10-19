from numba import jit


@jit(cache=True)
def f(x, y):
    return x + y


print(f(1, 2))
