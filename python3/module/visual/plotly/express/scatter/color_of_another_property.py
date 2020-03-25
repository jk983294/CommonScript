import plotly.express as px


def scatter_with_color():
    df = px.data.tips()
    fig = px.scatter(df, x="total_bill", y="tip", color="size", facet_col="sex",
                     color_continuous_scale=px.colors.sequential.Viridis, render_mode="webgl")
    fig.show()


scatter_with_color()
