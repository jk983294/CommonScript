import plotly.express as px
import pandas as pd

df = pd.read_csv('/home/kun/github/math/data/000001.csv')
fig = px.line(df, x='date', y='close')
fig.show()
