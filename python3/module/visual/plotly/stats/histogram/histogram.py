import plotly.express as px


def simple():
    df = px.data.tips()
    fig = px.histogram(df, x="total_bill")
    fig.show()


def histogram():
    df = px.data.tips()
    fig = px.histogram(df, x="total_bill", y="tip", color="sex", marginal="rug", hover_data=df.columns)
    fig.show()


def histogram_group_facet():
    df = px.data.tips()
    fig = px.histogram(df, x="sex", y="tip", histfunc="avg", color="smoker", barmode="group",
                       facet_row="time", facet_col="day", category_orders={"day": ["Thur", "Fri", "Sat", "Sun"],
                                                                           "time": ["Lunch", "Dinner"]})
    fig.show()


simple()
# histogram()
# histogram_group_facet()
