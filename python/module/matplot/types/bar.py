import matplotlib.pyplot as plt
import numpy as np

plt.bar([1, 2, 3], [3, 2, 5])
plt.show()

data = {'A': 40, 'B': 70, 'C': 30, 'D': 85}
for i, key in enumerate(data):
    plt.bar(i, data[key])
plt.xticks(np.arange(len(data)) + 0.4, data.keys())
plt.yticks(data.values())
plt.show()
