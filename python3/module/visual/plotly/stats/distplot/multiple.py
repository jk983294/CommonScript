import plotly.figure_factory as ff
import numpy as np


def demo1():
    # Add histogram data
    x1 = np.random.randn(200) - 2
    x2 = np.random.randn(200)
    x3 = np.random.randn(200) + 2
    x4 = np.random.randn(200) + 4

    # Group data together
    hist_data = [x1, x2, x3, x4]

    group_labels = ['Group 1', 'Group 2', 'Group 3', 'Group 4']

    # Create distplot with custom bin_size
    fig = ff.create_distplot(hist_data, group_labels, bin_size=.2)
    fig.show()


def demo_change_bin_size():
    # Add histogram data
    x1 = np.random.randn(200) - 2
    x2 = np.random.randn(200)
    x3 = np.random.randn(200) + 2
    x4 = np.random.randn(200) + 4

    # Group data together
    hist_data = [x1, x2, x3, x4]

    group_labels = ['Group 1', 'Group 2', 'Group 3', 'Group 4']

    # Create distplot with custom bin_size
    fig = ff.create_distplot(hist_data, group_labels, bin_size=[.1, .25, .5, 1])
    fig.show()


demo_change_bin_size()
