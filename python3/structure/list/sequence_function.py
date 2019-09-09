# slicing, tuple, list, and string objects can be sliced
# [start:end:stride]
# [n] means the n indexed element
# [:n] means the first n elements
# [n:] means the last elements from index n (inclusive)
# [n:m] means a range from index n (inclusive) to m (exclusive) element
# [:] means a copy of the object
# m and n can be negative: counted back from the end (-1 means the last element)

a = ["A", "B", "C", "D", "E", "F"]
print(a[-1])                                            # 'F'
print(a[1:4])                                           # ['B', 'C', 'D']
print(a[1:-1])                                          # ['B', 'C', 'D', 'E']
print(a[:-3])                                           # ['A', 'B', 'C']
print(a[::2])                                           # print(odd ['A', 'C', 'E']
print(a[1::2])                                          # print(even ['B', 'D', 'F']
print(a[::-1])                                          # reverse ['F', 'E', 'D', 'C', 'B', 'A']
text = "Hello Hi World"
print(text[:5] + text[8:])                              # 'Hello World'

# functions
map(round, [5.5, 6.2, 7.9, 11.123])                     # [6.0, 6.0, 8.0, 11.0]
map(str, [6, 7, 8])                                     # ['6', '7', '8']
filter(None, [1, 2, 2, 3, 0, 0, 1, 2])                  # [1, 2, 2, 3, 1, 2]
filter(lambda x: x % 2 == 0, [1, 2, 2, 3, 0, 0, 1, 2])  # [2, 2, 0, 0, 2]

# comprehension
names = ["george", "kevin", "bob"]
result = [name.capitalize() for name in names]          # ['George', 'Kevin', 'Bob']
data = [1, 2, 3, 5, 6, 7, 44, 55, 66]
filtered = [x * 2 for x in data if x > 6]               # [14, 88, 110, 132]
print([y + 44 for y in [x * 2 for x in data if x > 6] if y < 100])      # [58, 132]
