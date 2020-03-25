import plotly.graph_objects as go

fig = go.Figure()

fig.add_trace(go.Box(
    x=[2, 3, 1, 5],
    y=[['First', 'First', 'First', 'First'],
         ["A", "A", "A", "A"]],
    name="A",
    orientation="h"
))

fig.add_trace(go.Box(
    x=[8, 3, 6, 5],
    y=[['First', 'First', 'First', 'First'],
         ["B", "B", "B", "B"]],
    name="B",
    orientation="h"
))

fig.add_trace(go.Box(
    x=[2, 3, 2, 5],
    y=[['Second', 'Second', 'Second', 'Second'],
         ["C", "C", "C", "C"]],
    name="C",
    orientation="h"
))

fig.add_trace(go.Box(
    x=[7.5, 3, 6, 4],
    y=[['Second', 'Second', 'Second', 'Second'],
         ["D", "D", "D", "D"]],
    name="D",
    orientation="h"
))

fig.update_layout(title_text="Multi-category axis",)
fig.show()
