import seaborn as sns
import matplotlib.pyplot as plt

# pairplot show all pairwise relationships and the marginal distributions
sns.set()
iris = sns.load_dataset("iris")
sns.pairplot(data=iris, hue="species")
plt.show()
