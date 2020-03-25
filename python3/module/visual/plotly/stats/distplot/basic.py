import plotly.figure_factory as ff
import numpy as np
np.random.seed(1)

x = np.random.randn(1000)
hist_data = [x]
group_labels = ['distplot']     # name of the dataset

fig = ff.create_distplot(hist_data, group_labels)
fig.show()
