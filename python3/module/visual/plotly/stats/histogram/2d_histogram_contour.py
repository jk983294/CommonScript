import plotly.graph_objects as go
import numpy as np


def demo1():
    x = np.random.uniform(-1, 1, size=500)
    y = np.random.uniform(-1, 1, size=500)

    fig = go.Figure(go.Histogram2dContour(x=x, y=y, colorscale='Blues'))
    fig.show()


def demo2():
    t = np.linspace(-1, 1.2, 2000)
    x = (t**3) + (0.3 * np.random.randn(2000))
    y = (t**6) + (0.3 * np.random.randn(2000))

    fig = go.Figure()
    fig.add_trace(go.Histogram2dContour(
        x=x,
        y=y,
        colorscale='Blues',
        reversescale=True,
        xaxis='x',
        yaxis='y'
    ))
    fig.add_trace(go.Scatter(
        x=x,
        y=y,
        xaxis='x',
        yaxis='y',
        mode='markers',
        marker=dict(
            color='rgba(0,0,0,0.3)',
            size=3
        )
    ))
    fig.add_trace(go.Histogram(
        y=y,
        xaxis='x2',
        marker=dict(
            color='rgba(0,0,0,1)'
        )
    ))
    fig.add_trace(go.Histogram(
        x=x,
        yaxis='y2',
        marker=dict(
            color='rgba(0,0,0,1)'
        )
    ))

    fig.update_layout(
        autosize=False,
        xaxis=dict(
            zeroline=False,
            domain=[0,0.85],
            showgrid=False
        ),
        yaxis=dict(
            zeroline=False,
            domain=[0,0.85],
            showgrid=False
        ),
        xaxis2=dict(
            zeroline=False,
            domain=[0.85,1],
            showgrid=False
        ),
        yaxis2=dict(
            zeroline=False,
            domain=[0.85,1],
            showgrid=False
        ),
        height=600,
        width=600,
        bargap=0,
        hovermode='closest',
        showlegend=False
    )

    fig.show()


# demo1()
demo2()
