import timeit

class A(object):
    def my_method(self):
        return "something"

a=A()
print a.my_method()
# how many lookup happen here:
# 1. globals()                      # {'A': <class '__main__.A'>, 'a': <__main__.A object at 0x9239a0c>, '__builtins__': <module '__builtin__' (built-in)>, '__package__': None, 'myvar': 77, '__name__': '__main__', '__doc__': None}
# 2. locals()                       # {'A': <class '__main__.A'>, 'a': <__main__.A object at 0x9239a0c>, '__builtins__': <module '__builtin__' (built-in)>, '__package__': None, 'myvar': 77, '__name__': '__main__', '__doc__': None}
# 3. obj.__dict__


# Call the method of the built-in type

# Performance analysis
timer = timeit.Timer("'x' in 'Hello world'")
timer.timeit(1000000)                               # run code "'x' in 'Hello world'" 1000000 times, measure its time cost

# measure time with setup
code="""
for c in my_string:
    if c == my_char:
        break
"""

setup="""
my_string="Hello world"
my_char="x"
"""

timer = timeit.Timer(code, setup)
print timer.timeit(1000000)


# Profiling
$ python -m cProfile my_script.py
