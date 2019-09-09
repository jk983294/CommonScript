from functools import wraps


def decorator1(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        print('Decorator 1')
        return func(*args, **kwargs)
    return wrapper


def decorator2(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        print('Decorator 2')
        return func(*args, **kwargs)
    return wrapper


@decorator1
@decorator2
def add(x, y):
    return x + y


add(2, 3)
print("for multi-layer decorators, __wrapped__ works not consistent, in 3.3, it remove all layer decorators, "
      "while in 3.4, it only remove one layer")
add.__wrapped__(2, 3)
