import plotly.graph_objects as go
from plotly.subplots import make_subplots
import plotly.express as px

"""cell(i,j) of such a matrix displays the scatter plot of the variable X(i) versus X(j)"""


def scatter_matrix1():
    df = px.data.iris()
    fig = px.scatter_matrix(df)
    fig.show()


def scatter_matrix2():
    df = px.data.iris()
    fig = px.scatter_matrix(df, dimensions=["sepal_width", "sepal_length", "petal_width", "petal_length"], color="species")
    fig.show()


# scatter_matrix1()
scatter_matrix2()
