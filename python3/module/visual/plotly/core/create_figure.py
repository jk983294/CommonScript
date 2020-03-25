import plotly.graph_objects as go
import plotly.io as pio
import plotly.express as px


def plot_with_dict():
    fig = {
        "data": [{"type": "bar",
                  "x": [1, 2, 3],
                  "y": [1, 3, 2]}],
        "layout": {"title": {"text": "A Bar Chart"}}
    }
    pio.show(fig)


def plot_as_graph_object():
    fig = go.Figure(
        data=[go.Bar(x=[1, 2, 3], y=[1, 3, 2])],
        layout=go.Layout(
            title=go.layout.Title(text="A Bar Chart")
        )
    )
    fig.show()


def plot_with_plotly_express():
    """high-level data exploration API that produces graph object figures"""
    df = px.data.iris()
    fig = px.scatter(df, x="sepal_width", y="sepal_length", color="species")
    fig.show()


def plot_with_update1():
    fig = go.Figure()
    fig.add_trace(go.Bar(x=[1, 2, 3], y=[1, 3, 2]))
    fig.show()


def plot_with_plotly_express_update():
    df = px.data.iris()
    fig = px.scatter(df, x="sepal_width", y="sepal_length", color="species")
    fig.add_trace(
        go.Scatter(
            x=[2, 4],
            y=[4, 8],
            mode="lines",
            line=go.scatter.Line(color="gray"),
            showlegend=False)
    )
    fig.show()


# plot_with_dict()
# plot_as_graph_object()
# plot_with_plotly_express()
# plot_with_update1()
plot_with_plotly_express_update()
