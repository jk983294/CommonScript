import plotly.graph_objects as go
from plotly.subplots import make_subplots
import pandas as pd

df = pd.read_csv('/home/kun/github/math/data/000001.csv')

fig = make_subplots(
    rows=3, cols=1,
    shared_xaxes=True,
    vertical_spacing=0.03,
    specs=[[{"type": "table"}],
           [{"type": "scatter"}],
           [{"type": "scatter"}]]
)

fig.add_trace(go.Scatter(x=df.date, y=df['high'], name="High", line_color='deepskyblue'), row=3, col=1)
fig.add_trace(go.Scatter(x=df.date, y=df['low'], name="Low", line_color='dimgray'), row=2, col=1)

fig.add_trace(
    go.Table(
        header=dict(
            values=list(df.columns),
            font=dict(size=10),
            align="left"
        ),
        cells=dict(
            values=[df[k].tolist() for k in df.columns[:]],
            align="left")
    ),
    row=1, col=1
)

fig.update_layout(
    height=800,
    showlegend=False,
    title_text="data frame",
)

fig.show()
