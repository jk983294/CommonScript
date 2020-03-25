import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np

sns.set()
x = np.array(list("ABCDEFGHIJ"))
y1 = np.arange(1, 11)
sns.barplot(x=x, y=y1, palette="deep")
plt.show()
