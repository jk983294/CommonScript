import plotly.express as px


def with_rug():
    df = px.data.tips()
    fig = px.histogram(df, x="total_bill", color="sex", marginal="rug", hover_data=df.columns)
    fig.show()


def with_box():
    df = px.data.tips()
    fig = px.histogram(df, x="total_bill", color="sex", marginal="box", hover_data=df.columns)
    fig.show()


def with_violin():
    df = px.data.tips()
    fig = px.histogram(df, x="total_bill", color="sex", marginal="violin", hover_data=df.columns)
    fig.show()


with_rug()
with_box()
with_violin()

