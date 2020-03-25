from plotly.subplots import make_subplots
import plotly.graph_objects as go

fig = make_subplots(
    rows=2, cols=2,
    specs=[[{}, {}], [{"colspan": 2}, None]],
    subplot_titles=("First Subplot", "Second Subplot", "Third Subplot"))

fig.add_trace(go.Scatter(x=[1, 2], y=[1, 2]), row=1, col=1)
fig.add_trace(go.Scatter(x=[1, 2], y=[1, 2]), row=1, col=2)
fig.add_trace(go.Scatter(x=[1, 2, 3], y=[2, 1, 2]), row=2, col=1)

fig.update_layout(showlegend=False, title_text="Specs with Subplot Title")
fig.show()
