import seaborn as sns
import matplotlib.pyplot as plt

sns.set()
tips = sns.load_dataset("tips")
sns.catplot(x="day", y="total_bill", hue="smoker", kind="swarm", data=tips)
plt.show()
