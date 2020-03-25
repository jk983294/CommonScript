import plotly.graph_objects as go


def demo1():
    fig = go.Figure(data=[go.Table(header=dict(values=['A Scores', 'B Scores']),
                                   cells=dict(values=[[100, 90, 80, 90], [95, 85, 75, 95]]))
                          ])
    fig.show()


def demo2():
    fig = go.Figure(data=[go.Table(
        header=dict(values=['A Scores', 'B Scores'],
                    line_color='darkslategray',
                    fill_color='lightskyblue',
                    align='left'),
        cells=dict(values=[[100, 90, 80, 90], # 1st column
                           [95, 85, 75, 95]], # 2nd column
                   line_color='darkslategray',
                   fill_color='lightcyan',
                   align='left'))
    ])
    fig.update_layout(width=500, height=300)
    fig.show()


# demo1()
demo2()
