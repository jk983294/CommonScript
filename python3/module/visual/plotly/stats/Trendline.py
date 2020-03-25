import plotly.express as px


def demo1():
    df = px.data.tips()
    fig = px.scatter(df, x="total_bill", y="tip", trendline="ols")
    fig.show()


def fitting_multiple_lines():
    df = px.data.tips()
    fig = px.scatter(df, x="total_bill", y="tip", facet_col="smoker", color="sex", trendline="ols")
    fig.show()

    results = px.get_trendline_results(fig)
    print(results)
    print(results.query("sex == 'Male' and smoker == 'Yes'").px_fit_results.iloc[0].summary())


def fit_non_linear():
    df = px.data.gapminder().query("year == 2007")
    fig = px.scatter(df, x="gdpPercap", y="lifeExp", color="continent", trendline="lowess")
    fig.show()


# demo1()
# fitting_multiple_lines()
fit_non_linear()
