import seaborn as sns
import matplotlib.pyplot as plt

sns.set()
tips = sns.load_dataset("tips")
# kernel density estimation to represent the underlying distribution that the points
sns.catplot(x="day", y="total_bill", hue="smoker", kind="violin", split=True, data=tips)
plt.show()
