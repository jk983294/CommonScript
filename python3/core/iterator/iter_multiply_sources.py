import itertools

"""
zip can accept several iteratables and return one iterator
"""


xpts = [1, 2, 3]
ypts = [4, 5, 6]
for x, y in zip(xpts, ypts):
    print("(", x, y, ")")                  # ( 1 4 ) ( 2 5 ) ( 3 6 )


xpts = [1, 2, 3]
ypts = [4, 5, 6, 7]
for x, y in zip(xpts, ypts):
    print("(", x, y, ")")                   # ( 1 4 ) ( 2 5 ) ( 3 6 )


for x, y in itertools.zip_longest(xpts, ypts):
    print("(", x, y, ")")                   # ( 1 4 ) ( 2 5 ) ( 3 6 ) ( None 7 )


for x, y in itertools.zip_longest(xpts, ypts, fillvalue=-1):
    print("(", x, y, ")")                   # ( 1 4 ) ( 2 5 ) ( 3 6 ) ( -1 7 )


"""
chain all source together
"""

for x in itertools.chain([1, 2, 3], ['a', 'b']):
    print(x)                                # 1, 2, 3, 'a', 'b'

for x in itertools.chain.from_iterable([[1, 2, 3], ['a', 'b']]):
    print(x)                                # 1, 2, 3, 'a', 'b'

