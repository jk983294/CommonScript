import plotly.graph_objects as go
import plotly.io as pio


def config_renderer():
    print(pio.renderers)    # show the current default renderer
    pio.renderers.default = "browser"   # change default renderer


def display_to_html():
    fig = go.Figure(data=go.Bar(y=[2, 3, 1]))
    fig.write_html('/tmp/first_figure.html', auto_open=True)


def display_using_renderer_framework():
    """
    In many contexts, an appropriate renderer will be chosen automatically and you do not need any additional config,
    so use it in jupyter
    """
    fig = go.Figure(data=go.Bar(y=[2, 3, 1]))
    fig.show()


def display_using_static_image_renderer():
    fig = go.Figure(data=go.Bar(y=[2, 3, 1]))
    fig.show(renderer="png")    # need plotly orca installed


display_using_renderer_framework()
# display_to_html()
# display_using_static_image_renderer()
