import plotly.graph_objects as go
from plotly.colors import n_colors
import pandas as pd
import numpy as np


def demo1():
    headerColor = 'grey'
    rowEvenColor = 'lightgrey'
    rowOddColor = 'white'

    fig = go.Figure(data=[go.Table(
        header=dict(
            values=['<b>EXPENSES</b>', '<b>Q1</b>', '<b>Q2</b>', '<b>Q3</b>', '<b>Q4</b>'],
            line_color='darkslategray',
            fill_color=headerColor,
            align=['left', 'center'],
            font=dict(color='white', size=12)
        ),
        cells=dict(
            values=[
                ['Salaries', 'Office', 'Merchandise', 'Legal', '<b>TOTAL</b>'],
                [1200000, 20000, 80000, 2000, 12120000],
                [1300000, 20000, 70000, 2000, 130902000],
                [1300000, 20000, 120000, 2000, 131222000],
                [1400000, 20000, 90000, 2000, 14102000]],
            line_color='darkslategray',
            # 2-D list of colors for alternating rows
            fill_color=[[rowOddColor, rowEvenColor, rowOddColor, rowEvenColor, rowOddColor]*5],
            align=['left', 'center'],
            font=dict(color='darkslategray', size=11)
        ))
    ])

    fig.show()


def demo2():
    colors = ['rgb(239, 243, 255)', 'rgb(189, 215, 231)', 'rgb(107, 174, 214)',
              'rgb(49, 130, 189)', 'rgb(8, 81, 156)']
    data = {'Year' : [2010, 2011, 2012, 2013, 2014], 'Color' : colors}
    df = pd.DataFrame(data)

    fig = go.Figure(data=[go.Table(
        header=dict(
            values=["Color", "<b>YEAR</b>"],
            line_color='white', fill_color='white',
            align='center', font=dict(color='black', size=12)
        ),
        cells=dict(
            values=[df.Color, df.Year],
            line_color=[df.Color], fill_color=[df.Color],
            align='center', font=dict(color='black', size=11)
        ))
    ])

    fig.show()


def demo3():
    np.random.seed(1)

    colors = n_colors('rgb(255, 200, 200)', 'rgb(200, 0, 0)', 9, colortype='rgb')
    a = np.random.randint(low=0, high=9, size=10)
    b = np.random.randint(low=0, high=9, size=10)
    c = np.random.randint(low=0, high=9, size=10)

    fig = go.Figure(data=[go.Table(
        header=dict(
            values=['<b>Column A</b>', '<b>Column B</b>', '<b>Column C</b>'],
            line_color='white', fill_color='white',
            align='center',font=dict(color='black', size=12)
        ),
        cells=dict(
            values=[a, b, c],
            line_color=[np.array(colors)[a],np.array(colors)[b], np.array(colors)[c]],
            fill_color=[np.array(colors)[a],np.array(colors)[b], np.array(colors)[c]],
            align='center', font=dict(color='white', size=11)
        ))
    ])

    fig.show()


# demo1()
# demo2()
demo3()
