import time
from functools import wraps
from inspect import signature


def timethis(func):
    """
    Decorator that reports the execution time.
    @wraps(func) annotation keeps origin func's metadata like name, docstring, etc.
    """
    @wraps(func)
    def wrapper(*args, **kwargs):
        start = time.time()
        result = func(*args, **kwargs)
        end = time.time()
        print(func.__name__, end - start)
        return result
    return wrapper


@timethis
def countdown(n):
    while n > 0:
        n -= 1


countdown(100000)
countdown(10000000)
countdown.__wrapped__(10000)            # access origin function

print(countdown.__name__)
print(signature(countdown))             # (n)
