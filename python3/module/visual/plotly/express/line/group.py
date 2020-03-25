import plotly.express as px


def line_with_group():
    df = px.data.gapminder()
    fig = px.line(df, x="year", y="lifeExp", color="continent", line_group="country", hover_name="country",
                  line_shape="spline", render_mode="svg")
    fig.show()


line_with_group()
