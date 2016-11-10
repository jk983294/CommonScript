L = [ i * i for i in range(5) ]

# iterator with index
for index, data in enumerate(L, 1):
    print(index, ':',  data)

# iterator reverse order
for item in reversed(L):
    print(item)