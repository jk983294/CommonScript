import numpy as np

# choose(index_array, choice), new_a[i, j] = choice[control[i, j]]
control = np.array([[1, 0, 1], [2, 1, 0], [1, 2, 2]])

print(np.choose(control, [10, 11, 12]))  # [[11 10 11], [12 11 10], [11 12 12]]

# choose from [i0, 10, i2] which mixed with array and imm
i0 = np.array([[0, 1, 2], [3, 4, 5], [6, 7, 8]])
i2 = np.array([[20, 21, 22], [23, 24, 25], [26, 27, 28]])
control = np.array([[1, 0, 1], [2, 1, 0], [1, 2, 2]])
print(np.choose(control, [i0, 10, i2]))  # [[10  1 10], [23 10  5], [10 27 28]]
