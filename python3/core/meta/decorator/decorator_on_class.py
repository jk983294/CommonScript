"""
class level decorator often provide neat solution compared to mixin/metaclass
"""


def log_getattribute(cls):
    # Get the original implementation
    orig_getattribute = cls.__getattribute__

    # Make a new definition
    def new_getattribute(self, name):
        print('getting:', name)
        return orig_getattribute(self, name)

    # Attach to the class and return
    cls.__getattribute__ = new_getattribute
    return cls


@log_getattribute
class A:
    def __init__(self, x):
        self.x = x

    def spam(self):
        pass


a = A(42)
a.x                 # getting: x
a.spam()            # getting: spam


class LoggedGetattribute:
    def __getattribute__(self, name):
        print('getting:', name)
        return super().__getattribute__(name)


class B(LoggedGetattribute):
    def __init__(self, x):
        self.x = x

    def spam(self):
        pass


b = B(42)
b.x                 # getting: x
b.spam()            # getting: spam
