from plotly.subplots import make_subplots
import plotly.graph_objects as go

fig = make_subplots(rows=1, cols=2, shared_yaxes=True)

fig.add_trace(go.Bar(x=[1, 2, 3], y=[4, 5, 6], marker=dict(color=[4, 5, 6], coloraxis="coloraxis")), 1, 1)
fig.add_trace(go.Bar(x=[1, 2, 3], y=[2, 3, 5], marker=dict(color=[2, 3, 5], coloraxis="coloraxis")), 1, 2)

fig.update_layout(coloraxis=dict(colorscale='Bluered_r'), showlegend=False)
fig.show()
