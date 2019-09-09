import types
import os
from functools import wraps


class Profiled:
    def __init__(self, func):
        wraps(func)(self)
        self.ncalls = 0

    def __call__(self, *args, **kwargs):
        self.ncalls += 1
        return self.__wrapped__(*args, **kwargs)

    def __get__(self, instance, cls):
        if instance is None:
            return self
        else:
            return types.MethodType(self, instance)


@Profiled
def add(x, y):
    return x + y


class Spam:
    @Profiled
    def bar(self, x):
        print(self, x)


add(2, 3)
add(4, 5)
print(add.ncalls)               # 2

s = Spam()
s.bar(1)
print(Spam.bar.ncalls)          # 1


class NeedUserId(object):
    def __init__(self, user_id):
        self.user_id = user_id

    def __call__(self, func):
        def check_user_id(*args, **kwargs):
            if os.geteuid() == self.user_id:
                return func(*args, **kwargs)
            else:
                raise OSError("Invalid user id: %d" % os.geteuid())

        return check_user_id


# decorator object usage, nesting decorators
@NeedUserId(5678)
def my_func(a, b):
    return a + b


my_func(6, 7)  # equals to my_func = NeedUserId(5678)(my_func) | my_func(6,7)
