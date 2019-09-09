"""
closure is not like default value
default value capture variable value when defined
closure capture variable and evaluate it when execute it
"""


x = 10
a = lambda y: x + y
x = 20
b = lambda y: x + y

print(a(10))                        # 30
print(b(10))                        # 30

# default value
x = 10
a = lambda y, x=x: x + y
x = 20
b = lambda y, x=x: x + y

print(a(10))                        # 20
print(b(10))                        # 30

funcs = [lambda x, n=n: x+n for n in range(5)]
for f in funcs:
    print(f(0), end=' ')            # 0 1 2 3 4
