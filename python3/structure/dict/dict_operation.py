"""
map's keys()/items() function returns a set, it can apply with set union/intersect/minus operations
but values() is not a set
"""

a = {
    'x': 1,
    'y': 2,
    'z': 3
}

b = {
    'w': 10,
    'x': 11,
    'y': 2
}

# Find keys in common
print(a.keys() & b.keys())                      # { 'x', 'y' }
# Find keys in a that are not in b
print(a.keys() - b.keys())                      # { 'z' }
# Find (key, value) pairs in common
print(a.items() & b.items())                    # { ('y', 2) }

# Make a new dictionary with certain keys removed
c = {key: a[key] for key in a.keys() - {'z', 'w'}}
print(c)                                        # {'y': 2, 'x': 1}
