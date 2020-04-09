import numpy as np

a = np.array([[.2, .1, .5], [.4, .8, .3]])
print('default sort by row', np.sort(a))  # [[0.1 0.2 0.5], [0.3 0.4 0.8]]
print('sort by column', np.sort(a, axis=0))  # [[0.2 0.1 0.3], [0.4 0.8 0.5]]
print('sort by row', np.sort(a, axis=1))  # [[0.1 0.2 0.5], [0.3 0.4 0.8]]
