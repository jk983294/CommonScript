import functools
import os
from symbol import decorator

# decorator is a function which receives the function received in the first parameter,
# and returns a new function which would replace the old one

TRACE = True


def tracer_decorator(func):
    def tracer(*args, **kwargs):
        if TRACE:
            print("%s is called with args=%s, kwargs=%s" % (func.__name__, repr(args), repr(kwargs)))
        ret_val = func(*args, **kwargs)
        if TRACE:
            print("%s is returning %s" % (func.__name__, repr(ret_val)))
        return ret_val

    return tracer


# usage like annotation
@tracer_decorator
def my_func(a, b):
    return a + b


# entitlement check decorator
def need_user_id(user_id):
    def decorator(func):
        def check_user_id(*args, **kwargs):
            if os.geteuid() == user_id:
                return func(*args, **kwargs)
            else:
                raise OSError("Invalid user id: %d" % os.geteuid())

        return check_user_id

    return decorator


# An essential tool for wrapping an existing functions, copies the wrapped function's name, docstrings
def tracer_decorator(func):
    @functools.wraps(func)
    def tracer(*args, **kwargs):
        print("%s is called" % func.__name__)
        ret_val = func(*args, **kwargs)
        print("%s is returning" % func.__name__)
        return ret_val

    return tracer


# decorator package, eliminates the need of nesting functions
@tracer_decorator
def trace(f, *args, **kw):
    print("calling %s with args %s, %s" % (f.func_name, args, kw))
    return f(*args, **kw)
