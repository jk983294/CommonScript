import seaborn as sns
import matplotlib.pyplot as plt

# jointplot focuses on a single relationship
sns.set()
iris = sns.load_dataset("iris")
sns.jointplot(x="sepal_length", y="petal_length", data=iris)
plt.show()
