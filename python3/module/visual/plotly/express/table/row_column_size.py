import plotly.graph_objects as go

values = [['Salaries', 'Office', 'Merchandise', 'Legal', '<b>TOTAL<br>EXPENSES</b>'],     #1st col
          ["Lorem ipsum dolor sit amet, tollit discere inermis pri ut. Eos ea iusto timeam, an prima laboramus vim. Id usu aeterno adversarium, summo mollis timeam vel ad",
           "Lorem ipsum dolor sit amet, tollit discere inermis pri ut. Eos ea iusto timeam, an prima laboramus vim. Id usu aeterno adversarium, summo mollis timeam vel ad",
           "Lorem ipsum dolor sit amet, tollit discere inermis pri ut. Eos ea iusto timeam, an prima laboramus vim. Id usu aeterno adversarium, summo mollis timeam vel ad",
           "Lorem ipsum dolor sit amet, tollit discere inermis pri ut. Eos ea iusto timeam, an prima laboramus vim. Id usu aeterno adversarium, summo mollis timeam vel ad",
           "Lorem ipsum dolor sit amet, tollit discere inermis pri ut. Eos ea iusto timeam, an prima laboramus vim. Id usu aeterno adversarium, summo mollis timeam vel ad"]]


fig = go.Figure(data=[go.Table(
    columnorder=[1, 2],
    columnwidth=[80, 400],
    header=dict(
        values=[['<b>EXPENSES</b><br>as of July 2017'], ['<b>DESCRIPTION</b>']],
        line_color='darkslategray',
        fill_color='royalblue',
        align=['left', 'center'],
        font=dict(color='white', size=12),
        height=40
    ),
    cells=dict(
        values=values,
        line_color='darkslategray',
        fill=dict(color=['paleturquoise', 'white']),
        align=['left', 'center'],
        font_size=12,
        height=30)
)
])
fig.show()
