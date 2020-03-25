import plotly.express as px

df = px.data.tips()
fig = px.box(df, x="time", y="total_bill", color="smoker",
             notched=True,          # used notched shape
             title="Box plot of total bill",
             hover_data=["day"]     # add day column to hover data
             )
fig.show()
