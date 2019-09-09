from collections import ChainMap

"""
for dup key, it appears in order, that means in below example key z will be object a's
when you modify dict, only fist dict be impacted
"""

a = {'x': 1, 'z': 3}
b = {'y': 2, 'z': 4}

c = ChainMap(a, b)
print(c['x'])               # Outputs 1 (from a)
print(c['y'])               # Outputs 2 (from b)
print(c['z'])               # Outputs 3 (from a)

print(len(c))               # 3
print(list(c.keys()))       # ['x', 'y', 'z']
print(list(c.values()))     # [1, 2, 3]


# when you modify dict, only fist dict be impacted
c['z'] = 10
c['w'] = 40
del c['x']
print(a)                    # {'z': 10, 'w': 40}

values = ChainMap()
values['x'] = 1
# Add a new mapping
values = values.new_child()
values['x'] = 2
# Add a new mapping
values = values.new_child()
values['x'] = 3
print(values)               # ChainMap({'x': 3}, {'x': 2}, {'x': 1})
print(values['x'])          # 3
# Discard last mapping
values = values.parents
print(values['x'])          # 2
# Discard last mapping
values = values.parents
print(values['x'])          # 1
print(values)               # ChainMap({'x': 1})
