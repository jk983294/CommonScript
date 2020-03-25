from plotly.subplots import make_subplots
import plotly.graph_objects as go

fig = make_subplots(
    rows=3, cols=1, shared_xaxes=True, vertical_spacing=0.02
)

fig.add_trace(go.Scatter(x=[0, 1, 2], y=[10, 11, 12]), row=3, col=1)
fig.add_trace(go.Scatter(x=[2, 3, 4], y=[100, 110, 120]), row=2, col=1)
fig.add_trace(go.Scatter(x=[3, 4, 5], y=[1000, 1100, 1200]), row=1, col=1)

fig.update_layout(height=600, width=600, title_text="Stacked Subplots with Shared X-Axes")
fig.show()
