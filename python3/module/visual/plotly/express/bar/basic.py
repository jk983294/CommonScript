import plotly.express as px
import plotly.graph_objects as go


def demo1():
    data_canada = px.data.gapminder().query("country == 'Canada'")
    fig = px.bar(data_canada, x='year', y='pop')
    fig.show()


def demo2():
    animals = ['giraffes', 'orangutans', 'monkeys']

    fig = go.Figure(data=[
        go.Bar(name='SF Zoo', x=animals, y=[20, 14, 23]),
        go.Bar(name='LA Zoo', x=animals, y=[12, 18, 29])
    ])
    # Change the bar mode
    fig.update_layout(barmode='group')
    fig.show()


def demo_with_color():
    data = px.data.gapminder()
    data_canada = data[data.country == 'Canada']
    fig = px.bar(data_canada, x='year', y='pop',
                 hover_data=['lifeExp', 'gdpPercap'], color='lifeExp',
                 labels={'pop':'population of Canada'}, height=400)
    fig.show()


def demo_with_stack():
    df = px.data.tips()
    fig = px.bar(df, x="sex", y="total_bill", color='smoker', barmode='group', height=400)
    fig.show()


def demo_with_facet():
    df = px.data.tips()
    fig = px.bar(df, x="sex", y="total_bill", color="smoker", barmode="group",
                 facet_row="time", facet_col="day",
                 category_orders={"day": ["Thur", "Fri", "Sat", "Sun"],
                                  "time": ["Lunch", "Dinner"]})
    fig.show()


# demo1()
# demo2()
# demo_with_color()
# demo_with_stack()
# demo_with_facet()
