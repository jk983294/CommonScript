# iterator with index with first index be 1
for index, data in enumerate(range(3), 1):
    print(index, ':',  data)

# default index is 0 based
for index, data in enumerate(range(3)):
    print(index, ':',  data)

data = [(1, 2), (3, 4), (5, 6), (7, 8)]

# Correct way to iterator array of tuple
for n, (x, y) in enumerate(data):
    print(n, x, y)
