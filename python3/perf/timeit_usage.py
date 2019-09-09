import timeit


# Performance analysis
timer = timeit.Timer("'x' in 'Hello world'")
print(timer.timeit(1000000))                     # run code "'x' in 'Hello world'" 1000000 times, measure its time cost

# measure time with setup
code = """
for c in my_string:
    if c == my_char:
        break
"""

setup = """
my_string="Hello world"
my_char="x"
"""

timer = timeit.Timer(code, setup)
print(timer.timeit(1000000))

# shortcut, it will run 100,0000 times
print(timeit.timeit('math.sqrt(2)', 'import math'))
print(timeit.timeit('sqrt(2)', 'from math import sqrt'))

print(timeit.timeit('math.sqrt(2)', 'import math', number=1000000))
print(timeit.timeit('sqrt(2)', 'from math import sqrt', number=1000000))
