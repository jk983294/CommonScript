import seaborn as sns
import matplotlib.pyplot as plt

sns.set()       # apply the default seaborn theme, scaling, and color palette
tips = sns.load_dataset("tips")
print(tips.head(5))
sns.scatterplot(x="total_bill", y="tip", hue="day", data=tips)
plt.show()
