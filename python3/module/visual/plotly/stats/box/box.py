import plotly.express as px


def simple():
    df = px.data.tips()
    fig = px.box(df, x="day", y="total_bill", color="smoker", notched=True)
    fig.show()


def underlying_data():
    df = px.data.tips()
    fig = px.box(df, x="time", y="total_bill", points="all")
    fig.show()


# simple()
underlying_data()
