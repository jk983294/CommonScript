import plotly.graph_objects as go
import plotly.express as px
from plotly.subplots import make_subplots
import pandas as pd
import numpy as np


INCREASING_COLOR = 'green'
DECREASING_COLOR = 'red'


def moving_average(data, window_size=10):
    return data.rolling(window=window_size).mean()


def calc_candle_color(open_, close_):
    colors_ = []
    for i in range(len(close_)):
        if close_[i] > open_[i]:
            colors_.append(INCREASING_COLOR)
        else:
            colors_.append(DECREASING_COLOR)
    return colors_


df = pd.read_csv('/home/kun/github/math/data/000001.csv')
print(df.head())
# df = df.sort_values(by='date')
df = df.iloc[::-1] # TODO recreate index column
print(df.head())
mv_y = moving_average(df.close)
colors = calc_candle_color(df.open, df.close)

fig = make_subplots(rows=2, cols=1, shared_xaxes=True, vertical_spacing=0.02, row_heights=[0.7, 0.3],
                    specs=[[{"secondary_y": True}], [{}]])

fig.add_trace(go.Candlestick(x=df['date'], open=df['open'], high=df['high'], low=df['low'], close=df['close']),
              secondary_y=False, row=1, col=1)
fig.add_trace(go.Scatter(x=df['date'], y=mv_y, mode="lines", name='Moving Average', line=go.scatter.Line(color="gray")),
              secondary_y=True, row=1, col=1)
fig.add_trace(go.Bar(name='volume', x=df['date'], y=df['volume'], marker=dict(color=colors)), row=2, col=1)

fig.update_yaxes(title_text="<b>price</b>", secondary_y=False, row=1, col=1)
fig.update_yaxes(title_text="<b>ma10</b>", secondary_y=True, row=1, col=1)

fig.update_layout(
    title_text='Stock Chart',
    xaxis=dict(
        rangeselector=dict(
            buttons=list([
                dict(count=1,
                     label="1m",
                     step="month",
                     stepmode="backward"),
                dict(count=6,
                     label="6m",
                     step="month",
                     stepmode="backward"),
                dict(count=1,
                     label="YTD",
                     step="year",
                     stepmode="todate"),
                dict(count=1,
                     label="1y",
                     step="year",
                     stepmode="backward"),
                dict(step="all")
            ])
        ),
        rangeslider=dict(
            visible=True
        ),
        type="date"
    )
)


fig.show()
