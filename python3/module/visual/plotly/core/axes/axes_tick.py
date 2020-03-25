import plotly.graph_objects as go
import pandas as pd


def tick_mode_linear():
    fig = go.Figure(go.Scatter(
        x=[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12],
        y=[28.8, 28.5, 37, 56.8, 69.7, 79.7, 78.5, 77.8, 74.1, 62.6, 45.3, 39.9]
    ))
    fig.update_layout(xaxis=dict(tickmode='linear', tick0=0.5, dtick=0.75))
    fig.show()


def tick_mode_array():
    fig = go.Figure(go.Scatter(
        x=[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12],
        y=[28.8, 28.5, 37, 56.8, 69.7, 79.7, 78.5, 77.8, 74.1, 62.6, 45.3, 39.9]
    ))
    fig.update_layout(xaxis=dict(
        tickmode='array',
        tickvals=[1, 3, 5, 7, 9, 11],
        ticktext=['One', 'Three', 'Five', 'Seven', 'Nine', 'Eleven']
    ))
    fig.show()


def tick_format_percent():
    fig = go.Figure(go.Scatter(
        x=[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12],
        y=[28.8, 28.5, 37, 56.8, 69.7, 79.7, 78.5, 77.8, 74.1, 62.6, 45.3, 39.9]
    ))
    fig.update_layout(yaxis_tickformat='%')
    fig.show()


def tick_format_time():
    df = pd.read_csv('https://raw.githubusercontent.com/plotly/datasets/master/finance-charts-apple.csv')
    fig = go.Figure(go.Scatter(
        x=df['Date'],
        y=df['AAPL.High'],
    ))
    fig.update_layout(
        title='Time Series with Custom Date-Time Format',
        xaxis_tickformat='%d %B (%a)<br>%Y'
    )
    fig.show()


# tick_mode_linear()
# tick_mode_array()
# tick_format_percent()
tick_format_time()
