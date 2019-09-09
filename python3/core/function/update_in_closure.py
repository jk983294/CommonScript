import sys


def sample():
    n = 0

    # Closure function
    def func():
        print('n=', n)

    # Accessor methods for n
    def get_n():
        return n

    def set_n(value):
        nonlocal n          # update internal value
        n = value

    # Attach as function attributes
    func.get_n = get_n
    func.set_n = set_n
    return func


f = sample()
f()
f.set_n(10)
f()
print(f.get_n())


"""
function as class
closure usually faster than class because it simplify access to variables without self
"""


class ClosureInstance:
    def __init__(self, locals=None):
        if locals is None:
            locals = sys._getframe(1).f_locals
        # Update instance dictionary with callable
        self.__dict__.update((key, value) for key, value in locals.items() if callable(value))

    # Redirect special methods
    def __len__(self):
        return self.__dict__['__len__']()


# Example use
def Stack():
    items = []

    def push(item):
        items.append(item)

    def pop():
        return items.pop()

    def __len__():
        return len(items)

    return ClosureInstance()


s = Stack()
s.push(10)
s.push(20)
s.push('Hello')
print(len(s))               # 3
print(s.pop())              # Hello
print(s.pop())              # 20
print(s.pop())              # 10
