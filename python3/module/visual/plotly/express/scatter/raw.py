import plotly.graph_objects as go
from plotly.subplots import make_subplots
import plotly.express as px

"""
Plotly Express operates on "tidy" data and produces easy-to-style figures
"""


def scatter_raw():
    df = px.data.iris()
    print(df.head())
    fig = px.scatter(df, x="sepal_width", y="sepal_length")
    fig.show()


scatter_raw()
