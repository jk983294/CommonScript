import seaborn as sns
import matplotlib.pyplot as plt

sns.set()
fmri = sns.load_dataset("fmri")
print(fmri.head(5))
sns.relplot(x="timepoint", y="signal", col="region",
            hue="event", style="event",
            kind="line", data=fmri)
plt.show()
