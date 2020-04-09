import numpy as np

# list
names = ["george", "kevin", "bob"]
print([name.capitalize() for name in names])  # ['George', 'Kevin', 'Bob']
data = [1, 2, 3, 5, 6, 7, 44, 55, 66]
print([x * 2 for x in data if x > 6])  # [14, 88, 110, 132]
print([y + 44 for y in [x * 2 for x in data if x > 6] if y < 100])  # [58, 132]
x = [[1, 2], [3, 4]]
print([j for i in x for j in i])  # flat, [1, 2, 3, 4]
print(np.array(x).flatten().tolist())  # flat, [1, 2, 3, 4]

# tuple
tuples = [(n, str(n)) for n in range(3)]
print(tuples)  # [(0, '0'), (1, '1'), (2, '2')]
print([item[0] for item in tuples])  # extract first element [0, 1, 2]

# map
items = {str(n): n for n in range(3)}
print(items)  # {'0': 0, '1': 1, '2': 2}
print([k for k, v in items.items()])  # ['0', '1', '2']
