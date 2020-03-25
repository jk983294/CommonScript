import plotly.graph_objects as go
from plotly.subplots import make_subplots
import plotly.express as px


def multi_plot1():
    fig = make_subplots(rows=1, cols=2)
    fig.add_trace(go.Scatter(y=[4, 2, 1], mode="lines"), row=1, col=1)
    fig.add_trace(go.Bar(y=[2, 1, 3]), row=1, col=2)
    fig.show()


def multi_plot2():
    fig = make_subplots(rows=1, cols=2)
    fig.add_scatter(y=[4, 2, 1], mode="lines", row=1, col=1)
    fig.add_bar(y=[2, 1, 3], row=1, col=2)
    fig.show()


def multi_plot_facet_row():
    df = px.data.iris()
    fig = px.scatter(df, x="sepal_width", y="sepal_length", color="species", facet_col="species")
    reference_line = go.Scatter(x=[2, 4],
                                y=[4, 8],
                                mode="lines",
                                line=go.scatter.Line(color="gray"),
                                showlegend=False)
    fig.add_trace(reference_line, row=1, col=1)
    fig.add_trace(reference_line, row=1, col=2)
    fig.add_trace(reference_line, row=1, col=3)
    fig.show()


def update_traces():
    """
    update_traces to modify the color of all traces
    it can also apply selector to update matched properties only
    it can also apply selector to update matched (row, col) only
    """
    fig = make_subplots(rows=1, cols=2)
    fig.add_scatter(y=[4, 2, 3.5], mode="markers", marker=dict(size=20, color="LightSeaGreen"), name="a", row=1, col=1)
    fig.add_bar(y=[2, 1, 3], marker=dict(color="MediumPurple"), name="b", row=1, col=1)
    fig.add_scatter(y=[2, 3.5, 4], mode="markers", marker=dict(size=20, color="MediumPurple"), name="c", row=1, col=2)
    fig.add_bar(y=[1, 3, 2], marker=dict(color="LightSeaGreen"), name="d", row=1, col=2)
    # fig.update_traces(marker=dict(color="RoyalBlue"))
    # fig.update_traces(marker_color="RoyalBlue", selector=dict(marker_color="MediumPurple"))
    fig.update_traces(marker=dict(color="RoyalBlue"), col=2)
    fig.show()


# multi_plot1()
# multi_plot2()
# multi_plot_facet_row()
update_traces()
