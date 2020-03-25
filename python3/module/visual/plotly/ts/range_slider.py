import plotly.graph_objects as go
import pandas as pd

df = pd.read_csv('/home/kun/github/math/data/000001.csv')

fig = go.Figure()
fig.add_trace(go.Scatter(x=df.date, y=df['high'], name="High", line_color='deepskyblue'))
fig.add_trace(go.Scatter(x=df.date, y=df['low'], name="Low", line_color='dimgray'))

fig.update_layout(title_text='Time Series with Rangeslider', xaxis_rangeslider_visible=True)
fig.show()
