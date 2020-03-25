import plotly.express as px


def bar_group():
    df = px.data.tips()
    fig = px.bar(df, x="sex", y="total_bill", color="smoker", barmode="group")
    fig.show()


def bar_group_category():
    df = px.data.tips()
    fig = px.bar(df, x="sex", y="total_bill", color="smoker", barmode="group", facet_row="time", facet_col="day",
                 category_orders={"day": ["Thur", "Fri", "Sat", "Sun"], "time": ["Lunch", "Dinner"]})
    fig.show()


# bar_group()
bar_group_category()
