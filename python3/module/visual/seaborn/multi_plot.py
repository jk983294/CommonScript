import matplotlib.pyplot as plt
import seaborn as sns

tips = sns.load_dataset("tips")
f, axes = plt.subplots(1, 2, sharey=True, figsize=(6, 4))
sns.boxplot(x="day", y="tip", data=tips, ax=axes[0])
sns.scatterplot(x="total_bill", y="tip", hue="day", data=tips, ax=axes[1])
plt.show()
