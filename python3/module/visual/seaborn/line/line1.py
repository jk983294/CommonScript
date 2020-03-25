import seaborn as sns
import matplotlib.pyplot as plt

sns.set()
fmri = sns.load_dataset("fmri")
# Timeseries plot with error bands
sns.lineplot(x="timepoint", y="signal", hue="region", style="event", data=fmri)
plt.show()
