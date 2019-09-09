import math

a = float('inf')
b = float('-inf')
c = float('nan')
d = float('nan')

print(math.isinf(a))                # True
print(math.isnan(c))                # True
print(math.sqrt(c))                 # nan
print(c == d)                       # False
print(c is d)                       # False


