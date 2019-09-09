import matplotlib.pyplot as plt
import numpy as np

x = [4, 9, 21, 55, 30, 18]
labels = ['Swiss', 'Austria', 'Spain', 'Italy', 'France', 'Benelux']
explode = [0.2, 0.1, 0, 0, 0.1, 0]
plt.pie(x, labels=labels, explode=explode, autopct='%1.1f%%')
plt.show()
