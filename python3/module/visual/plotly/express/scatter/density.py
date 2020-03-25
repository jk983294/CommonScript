import plotly.express as px


def scatter_with_density1():
    df = px.data.iris()
    fig = px.scatter(df, x="sepal_width", y="sepal_length", color="species", marginal_y="rug", marginal_x="histogram")
    fig.show()


def scatter_with_density2():
    df = px.data.iris()
    fig = px.scatter(df, x="sepal_width", y="sepal_length", color="species", marginal_y="violin",
                     marginal_x="box", trendline="ols")
    fig.show()


# scatter_with_density1()
scatter_with_density2()
