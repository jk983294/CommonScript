from plotly.subplots import make_subplots
import plotly.graph_objects as go

fig = make_subplots(rows=1, cols=2, shared_yaxes=True)

fig.add_trace(go.Scatter(x=[1, 2, 3], y=[2, 3, 4]), row=1, col=1)
fig.add_trace(go.Scatter(x=[20, 30, 40], y=[5, 5, 5]), row=1, col=2)

fig.update_layout(height=600, width=600, title_text="Multiple Subplots with Shared Y-Axes")
fig.show()
