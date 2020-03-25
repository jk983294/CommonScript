import seaborn as sns
import matplotlib.pyplot as plt

sns.set()
tips = sns.load_dataset("tips")
print(tips.head(5))
sns.lmplot(x="total_bill", y="tip", col="time", hue="smoker", data=tips)
plt.show()
