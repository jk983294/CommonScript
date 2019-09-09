import time
from functools import wraps


def timethis(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        start = time.time()
        r = func(*args, **kwargs)
        end = time.time()
        print(end-start)
        return r
    return wrapper


class Spam:
    """
    sequence do matters for class method or static method
    below will throw exception, swap order then works fine
    """
    @timethis
    @staticmethod
    def static_method(n):
        print(n)
        while n > 0:
            n -= 1


# Spam.static_method(1000000)           # TypeError: 'staticmethod' object is not callable
