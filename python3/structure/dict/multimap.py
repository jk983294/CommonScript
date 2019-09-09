from collections import defaultdict

"""
depend on your requirement, you can choose list or set as mapped value
"""


d = {
    'a': [1, 2, 3],
    'b': [4, 5]
}
e = {
    'a': {1, 2, 3},
    'b': {4, 5}
}

# use default dict with list as mapped value
d1 = defaultdict(list)
d1['a'].append(1)
d1['a'].append(2)
d1['b'].append(4)

d2 = defaultdict(set)
d2['a'].add(1)
d2['a'].add(2)
d2['b'].add(4)
