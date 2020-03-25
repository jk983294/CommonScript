import plotly.express as px


def simple():
    df = px.data.tips()
    fig = px.violin(df, y="tip", x="smoker", color="sex", box=True, points="all", hover_data=df.columns)
    fig.show()


simple()
