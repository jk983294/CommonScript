import plotly.graph_objects as go
import plotly.io as pio
import plotly.express as px


def normal_way():
    fig = go.Figure(
        data=[go.Scatter(y=[1, 3, 2], line=dict(color="crimson"))],
        layout=dict(title=dict(text="A Chart"))
    )
    fig.show()


def plot_with_underscore_notation():
    """
    Magic underscore notation is supported throughout the graph objects API,
    and it can often significantly simplify operations involving deeply nested properties
    """
    fig = go.Figure(
        data=[go.Scatter(y=[1, 3, 2], line_color="crimson")],
        layout_title_text="A Chart"
    )
    fig.show()


# normal_way()
plot_with_underscore_notation()
