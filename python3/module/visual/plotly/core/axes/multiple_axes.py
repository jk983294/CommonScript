import plotly.graph_objects as go
from plotly.subplots import make_subplots


def two_y_axes():
    # create figure with secondary y-axis
    fig = make_subplots(specs=[[{"secondary_y": True}]])

    fig.add_trace(go.Scatter(x=[1, 2, 3], y=[40, 50, 60], name="yaxis data"), secondary_y=False,)
    fig.add_trace(go.Scatter(x=[2, 3, 4], y=[4, 5, 6], name="yaxis2 data"), secondary_y=True,)
    fig.update_layout(title_text="Double Y Axis Example")
    fig.update_xaxes(title_text="xaxis title")

    # set y-axes titles
    fig.update_yaxes(title_text="<b>primary</b> yaxis title", secondary_y=False)
    fig.update_yaxes(title_text="<b>secondary</b> yaxis title", secondary_y=True)

    fig.show()


def two_y_axes_subplots():
    fig = make_subplots(rows=2, cols=2, specs=[[{"secondary_y": True}, {"secondary_y": True}], [{"secondary_y": True}, {"secondary_y": True}]])

    fig.add_trace(go.Scatter(x=[1, 2, 3], y=[2, 52, 62], name="yaxis data"), row=1, col=1, secondary_y=False)
    fig.add_trace(go.Scatter(x=[1, 2, 3], y=[40, 50, 60], name="yaxis2 data"), row=1, col=1, secondary_y=True,)

    fig.add_trace(go.Scatter(x=[1, 2, 3], y=[2, 52, 62], name="yaxis3 data"), row=1, col=2, secondary_y=False,)
    fig.add_trace(go.Scatter(x=[1, 2, 3], y=[40, 50, 60], name="yaxis4 data"), row=1, col=2, secondary_y=True,)

    fig.add_trace(go.Scatter(x=[1, 2, 3], y=[2, 52, 62], name="yaxis5 data"), row=2, col=1, secondary_y=False,)
    fig.add_trace(go.Scatter(x=[1, 2, 3], y=[40, 50, 60], name="yaxis6 data"), row=2, col=1, secondary_y=True,)

    fig.add_trace(go.Scatter(x=[1, 2, 3], y=[2, 52, 62], name="yaxis7 data"), row=2, col=2, secondary_y=False,)
    fig.add_trace(go.Scatter(x=[1, 2, 3], y=[40, 50, 60], name="yaxis8 data"), row=2, col=2, secondary_y=True,)
    fig.show()


def multiple_axes():
    fig = go.Figure()

    fig.add_trace(go.Scatter(
        x=[1, 2, 3],
        y=[4, 5, 6],
        name="yaxis1 data"
    ))

    fig.add_trace(go.Scatter(
        x=[2, 3, 4],
        y=[40, 50, 60],
        name="yaxis2 data",
        yaxis="y2"
    ))

    fig.add_trace(go.Scatter(
        x=[4, 5, 6],
        y=[40000, 50000, 60000],
        name="yaxis3 data",
        yaxis="y3"
    ))

    fig.add_trace(go.Scatter(
        x=[5, 6, 7],
        y=[400000, 500000, 600000],
        name="yaxis4 data",
        yaxis="y4"
    ))

    # Create axis objects
    fig.update_layout(
        xaxis=dict(
            domain=[0.3, 0.7]
        ),
        yaxis=dict(
            title="yaxis title",
            titlefont=dict(
                color="#1f77b4"
            ),
            tickfont=dict(
                color="#1f77b4"
            )
        ),
        yaxis2=dict(
            title="yaxis2 title",
            titlefont=dict(
                color="#ff7f0e"
            ),
            tickfont=dict(
                color="#ff7f0e"
            ),
            anchor="free",
            overlaying="y",
            side="left",
            position=0.15
        ),
        yaxis3=dict(
            title="yaxis4 title",
            titlefont=dict(
                color="#d62728"
            ),
            tickfont=dict(
                color="#d62728"
            ),
            anchor="x",
            overlaying="y",
            side="right"
        ),
        yaxis4=dict(
            title="yaxis5 title",
            titlefont=dict(
                color="#9467bd"
            ),
            tickfont=dict(
                color="#9467bd"
            ),
            anchor="free",
            overlaying="y",
            side="right",
            position=0.85
        )
    )

    # Update layout properties
    fig.update_layout(
        title_text="multiple y-axes example",
        width=800,
    )
    fig.show()


# two_y_axes()
# two_y_axes_subplots()
multiple_axes()
