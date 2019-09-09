a = {1, 2, 3, 4, 5}             # {1, 2, 3, 4, 5}
a.add(1)                        # {1, 2, 3, 4, 5}
b = {3, 4, 5, 6, 7}             # {3, 4, 5, 6, 7}
print(1 in a)                   # True
print(a.intersection(b))        # set([3, 4, 5])
print(a - b)                    # set([1, 2])
list(a - b)                     # [1, 2]
print((a - b).issubset(a))      # True
