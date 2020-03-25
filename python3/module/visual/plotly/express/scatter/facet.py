import plotly.graph_objects as go
from plotly.subplots import make_subplots
import plotly.express as px


def scatter_with_facet():
    df = px.data.tips()
    fig = px.scatter(df, x="total_bill", y="tip", facet_row="time", facet_col="day", color="smoker", trendline="ols",
                     category_orders={"day": ["Thur", "Fri", "Sat", "Sun"], "time": ["Lunch", "Dinner"]})
    fig.show()


scatter_with_facet()

