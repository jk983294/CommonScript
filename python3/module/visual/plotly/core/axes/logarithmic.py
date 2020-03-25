import plotly.express as px
import plotly.graph_objects as go
import numpy as np


def demo1():
    x = np.arange(10)
    fig = px.scatter(x=x, y=x**3, log_x=True, log_y=True)
    fig.show()


def demo2():
    fig = go.Figure(data=[
        go.Scatter(
            x=[1, 10, 20, 30, 40, 50, 60, 70, 80],
            y=[80, 70, 60, 50, 40, 30, 20, 10, 1]
        ),
        go.Scatter(
            x=[1, 10, 20, 30, 40, 50, 60, 70, 80],
            y=[1, 10, 20, 30, 40, 50, 60, 70, 80]
        )
    ])
    fig.update_xaxes(type="log")
    fig.update_yaxes(type="log")
    fig.show()


demo2()
