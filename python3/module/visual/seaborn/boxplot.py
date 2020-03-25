import matplotlib.pyplot as plt
import seaborn as sns

tips = sns.load_dataset("tips")
sns.boxplot(x="day", y="tip", data=tips)
plt.show()
