import numpy as np

weights = np.array([2.8, 9.2, 5.4, 6.8])
print(np.sort(weights))
print('not in place sort', weights)

# inplace sort
weights.sort()
print(weights)  # [2.8 5.4 6.8 9.2]
