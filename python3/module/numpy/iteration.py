import numpy as np

# vector
for i in np.arange(6):
    print(i, end=' ')                   # 0 1 2 3 4 5
print()

# matrix
b = np.arange(6).reshape(2, 3)
for row in b:
    print(row)                          # [0 1 2] [3 4 5]
print()

for element in b.flat:
    print(element, end=' ')             # 0 1 2 3 4 5
