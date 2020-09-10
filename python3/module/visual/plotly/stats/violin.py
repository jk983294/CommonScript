import plotly.express as px
import plotly.graph_objects as go
import pandas as pd
import numpy as np


def simple():
    df = px.data.tips()
    print(df.head(5))
    fig = px.violin(df, y="tip", x="smoker", color="sex", box=True, points="all", hover_data=df.columns)
    fig.show()


def draw_df():
    df = pd.DataFrame(np.random.randn(6, 4), columns=list('ABCD'))
    print(df.head(5))
    columns = ['A', 'B', 'C', 'D']

    fig = go.Figure()
    for column in columns:
        fig.add_trace(go.Violin(y=df[column], name=column, box_visible=True, meanline_visible=True))

    fig.show()


# simple()
draw_df()
