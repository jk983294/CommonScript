import plotly.express as px
import plotly.graph_objects as go
import pandas as pd

df = pd.read_csv('/home/kun/github/math/data/000001.csv')

fig = go.Figure()
fig.add_trace(go.Scatter(
    x=df.date,
    y=df['high'],
    name="high",
    line_color='deepskyblue',
    opacity=0.8))

fig.add_trace(go.Scatter(
    x=df.date,
    y=df['low'],
    name="low",
    line_color='dimgray',
    opacity=0.8))

# Use date string to set xaxis range
fig.update_layout(xaxis_range=['2018-01-01', '2019-01-01'],
                  title_text="Manually Set Date Range")
fig.show()
