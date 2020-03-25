import plotly.graph_objects as go


def demo1():
    fig = go.Figure(data=[go.Scatter(
        x=[1, 2, 3, 4], y=[10, 11, 12, 13],
        mode='markers',
        marker_size=[40, 60, 80, 100])
    ])

    fig.show()


def demo2():
    fig = go.Figure(data=[go.Scatter(
        x=[1, 2, 3, 4], y=[10, 11, 12, 13],
        mode='markers',
        marker=dict(
            color=['rgb(93, 164, 214)', 'rgb(255, 144, 14)',
                   'rgb(44, 160, 101)', 'rgb(255, 65, 54)'],
            opacity=[1, 0.8, 0.6, 0.4],
            size=[40, 60, 80, 100],
        )
    )])

    fig.show()


# demo1()
demo2()
