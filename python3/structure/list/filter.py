from itertools import compress

"""
filter return generator, use list to get a list
"""

mylist = [1, 4, -5, 10, -7, 2, 3, -1]
print([n for n in mylist if n > 0])         # [1, 4, 10, 2, 3]
print([n for n in mylist if n < 0])         # [-5, -7, -1]
# replace condition failed item to default value
print([n if n > 0 else 0 for n in mylist])  # [1, 4, 0, 10, 0, 2, 3, 0]

# use generator to reduce memory usage
pos = (n for n in mylist if n > 0)
for x in pos:
    print(x, " ", end='')


def is_int(val):
    try:
        x = int(val)
        return True
    except ValueError:
        return False


values = ['1', '2', '-3', '-', '4', 'N/A', '5']
ivals = list(filter(is_int, values))
print()
print(ivals)


# find addresses which its count > 5
# compress() will output the selection Boolean array indicated items
addresses = [
    '5412 N CLARK',
    '5148 N CLARK',
    '5800 E 58TH',
    '2122 N CLARK',
    '5645 N RAVENSWOOD',
    '1060 W ADDISON',
    '4801 N BROADWAY',
    '1039 W GRANVILLE',
]
counts = [0, 3, 10, 4, 1, 7, 6, 1]


more5 = [n > 5 for n in counts]
print(more5)                                    # [False, False, True, False, False, True, True, False]
print(list(compress(addresses, more5)))         # ['5800 E 58TH', '1060 W ADDISON', '4801 N BROADWAY']
