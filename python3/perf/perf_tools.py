import time
from functools import wraps
from contextlib import contextmanager


def timethis(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        start = time.perf_counter()
        r = func(*args, **kwargs)
        end = time.perf_counter()
        print('{}.{} : {}'.format(func.__module__, func.__name__, end - start))
        return r
    return wrapper


@contextmanager
def timeblock(label):
    start = time.perf_counter()
    try:
        yield
    finally:
        end = time.perf_counter()
        print('{} : {}'.format(label, end - start))


if __name__ == '__main__':
    @timethis
    def countdown(n):
        while n > 0:
            n -= 1

    countdown(100000)

    with timeblock('counting'):
        n = 10000000
        while n > 0:
            n -= 1
