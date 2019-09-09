a = {'x': 1, 'z': 3}
b = {'y': 2, 'z': 4}

merged = dict(b)
merged.update(a)
print(merged['x'])              # 1
print(merged['y'])              # 2
print(merged['z'])              # 3, it get updated data from a
