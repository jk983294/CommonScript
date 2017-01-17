# decorator is a function which receives the function received in the first parameter, and returns a new function which would replace the old one

def tracer_decorator(func):
    def tracer(*args, **kwargs):
        if TRACE:
            print "%s is called with args=%s, kwargs=%s" % (func.__name__, repr(args), repr(kwargs))
        ret_val = func(*args, **kwargs)
        if TRACE:
            print "%s is returning %s" % (func.__name__, repr(ret_val))
        return ret_val
    return tracer

# usage like annotation
@tracer_decorator
def my_func(a, b):
    return a+b


# entitlement check decorator
def need_userid(userid):
    def decorator(func):
        def check_userid(*args, **kwargs):
            if os.geteuid() == userid:
                return func(*args, **kwargs)
            else:
                raise OSError, "Invalid userid: %d" % os.geteuid()
        return check_userid
    return decorator

# decorator object
class need_userid(object):
    def __init__(self, userid):
        self.userid = userid

    def __call__(self, func):
        def check_userid(*args, **kwargs):
            if os.geteuid() == self.userid:
                return func(*args, **kwargs)
            else:
                raise OSError, "Invalid userid: %d" % os.geteuid()
        return check_userid


# decorator object usage, nesting decorators
@need_userid(5678)
@tracer_decorator
def my_func(a,b):
    return a+b

my_func(6,7)            # equals to my_func = need_userid(107686)(tracer_decorator(my_func)) | my_func(6,7)


# An essential tool for wrapping an existing functions, copies the wrapped function's name, docstrings
def tracer_decorator(func):
    @functools.wraps(func)
    def tracer(*args, **kwargs):
        print "%s is called" % func.__name__
        ret_val = func(*args, **kwargs)
        print "%s is returning" % func.__name__
        return ret_val
    return tracer

# decorator package, eliminates the need of nesting functions
@decorator
def trace(f, *args, **kw):
    print "calling %s with args %s, %s" % (f.func_name, args, kw)
    return f(*args, **kw)
