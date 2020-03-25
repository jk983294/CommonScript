import plotly.express as px


def scatter_with_error():
    df = px.data.iris()
    df["e"] = df["sepal_width"]/100
    fig = px.scatter(df, x="sepal_width", y="sepal_length", color="species", error_x="e", error_y="e")
    fig.show()


scatter_with_error()
