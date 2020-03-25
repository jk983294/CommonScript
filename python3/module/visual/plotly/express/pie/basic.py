import plotly.express as px
import plotly.graph_objects as go


def demo1():
    df = px.data.gapminder().query("year == 2007").query("continent == 'Europe'")
    df.loc[df['pop'] < 2.e6, 'country'] = 'Other countries'     # Represent only large countries
    fig = px.pie(df, values='pop', names='country', title='Population of European continent')
    fig.show()


def demo2():
    labels = ['Oxygen', 'Hydrogen', 'Carbon_Dioxide', 'Nitrogen']
    values = [4500, 2500, 1053, 500]

    fig = go.Figure(data=[go.Pie(labels=labels, values=values)])
    fig.show()


# demo1()
demo2()
