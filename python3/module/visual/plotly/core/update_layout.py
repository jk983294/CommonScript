import plotly.graph_objects as go

fig = go.Figure(data=go.Bar(x=[1, 2, 3], y=[1, 3, 2]))
fig.update_layout(title_text="A Bar Chart",
                  title_font_size=30)
fig.show()
