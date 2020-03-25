import plotly.express as px
import numpy as np
import plotly.graph_objects as go


def demo1():
    t = np.linspace(0, 2*np.pi, 100)
    fig = px.line(x=t, y=np.cos(t), labels={'x':'t', 'y':'cos(t)'})
    fig.show()


def demo2():
    df = px.data.gapminder().query("continent == 'Oceania'")
    fig = px.line(df, x='year', y='lifeExp', color='country')
    fig.show()


def demo3():
    x = np.arange(10)
    fig = go.Figure(data=go.Scatter(x=x, y=x**2))
    fig.show()


def demo4_plot_mode():
    np.random.seed(1)

    N = 100
    random_x = np.linspace(0, 1, N)
    random_y0 = np.random.randn(N) + 5
    random_y1 = np.random.randn(N)
    random_y2 = np.random.randn(N) - 5

    fig = go.Figure()
    fig.add_trace(go.Scatter(x=random_x, y=random_y0, mode='lines', name='lines'))
    fig.add_trace(go.Scatter(x=random_x, y=random_y1, mode='lines+markers', name='lines+markers'))
    fig.add_trace(go.Scatter(x=random_x, y=random_y2, mode='markers', name='markers'))
    fig.show()


def demo4_plot_style():
    month = ['January', 'February', 'March', 'April', 'May', 'June', 'July',
             'August', 'September', 'October', 'November', 'December']
    high_2000 = [32.5, 37.6, 49.9, 53.0, 69.1, 75.4, 76.5, 76.6, 70.7, 60.6, 45.1, 29.3]
    low_2000 = [13.8, 22.3, 32.5, 37.2, 49.9, 56.1, 57.7, 58.3, 51.2, 42.8, 31.6, 15.9]
    high_2007 = [36.5, 26.6, 43.6, 52.3, 71.5, 81.4, 80.5, 82.2, 76.0, 67.3, 46.1, 35.0]
    low_2007 = [23.6, 14.0, 27.0, 36.8, 47.6, 57.7, 58.9, 61.2, 53.3, 48.5, 31.0, 23.6]
    high_2014 = [28.8, 28.5, 37.0, 56.8, 69.7, 79.7, 78.5, 77.8, 74.1, 62.6, 45.3, 39.9]
    low_2014 = [12.7, 14.3, 18.6, 35.5, 49.9, 58.0, 60.0, 58.6, 51.7, 45.2, 32.2, 29.1]

    fig = go.Figure()
    # Create and style traces
    fig.add_trace(go.Scatter(x=month, y=high_2014, name='High 2014',
                             line=dict(color='firebrick', width=4)))
    fig.add_trace(go.Scatter(x=month, y=low_2014, name = 'Low 2014',
                             line=dict(color='royalblue', width=4)))
    fig.add_trace(go.Scatter(x=month, y=high_2007, name='High 2007',
                             line=dict(color='firebrick', width=4,
                                       dash='dash') # dash options include 'dash', 'dot', and 'dashdot'
                             ))
    fig.add_trace(go.Scatter(x=month, y=low_2007, name='Low 2007',
                             line = dict(color='royalblue', width=4, dash='dash')))
    fig.add_trace(go.Scatter(x=month, y=high_2000, name='High 2000',
                             line = dict(color='firebrick', width=4, dash='dot')))
    fig.add_trace(go.Scatter(x=month, y=low_2000, name='Low 2000',
                             line=dict(color='royalblue', width=4, dash='dot')))

    # Edit the layout
    fig.update_layout(title='Average High and Low Temperatures in New York',
                      xaxis_title='Month',
                      yaxis_title='Temperature (degrees F)')
    fig.show()


# demo1()
# demo2()
# demo3()
# demo4_plot_mode()
demo4_plot_style()
