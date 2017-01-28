a = set((1, 2, 3, 4, 5))  # set([1, 2, 3, 4, 5])
a.add(1)  # set([1, 2, 3, 4, 5])
b = set((3, 4, 5, 6, 7))  # set([3, 4, 5, 6, 7])
1 in a  # True
a.intersection(b)  # set([3, 4, 5])
a - b  # set([1, 2])
list(a - b)  # [1, 2]
(a - b).issubset(a)  # True
