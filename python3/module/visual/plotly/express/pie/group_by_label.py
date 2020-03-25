import plotly.express as px

# This dataframe has 244 lines, but 4 distinct values for day
df = px.data.tips()
fig = px.pie(df, values='tip', names='day')     # group by day
fig.show()
