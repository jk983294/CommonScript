import plotly.express as px


def density_contour1():
    df = px.data.iris()
    fig = px.density_contour(df, x="sepal_width", y="sepal_length")
    fig.show()


def density_contour2():
    df = px.data.iris()
    fig = px.density_contour(df, x="sepal_width", y="sepal_length", color="species", marginal_x="rug",
                             marginal_y="histogram")
    fig.show()


def density_heatmap():
    df = px.data.iris()
    fig = px.density_heatmap(df, x="sepal_width", y="sepal_length", marginal_x="rug", marginal_y="histogram")
    fig.show()


# density_contour()
# density_contour2()
density_heatmap()
