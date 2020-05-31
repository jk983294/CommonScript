import pandas as pd
import plotly.graph_objects as go


def visual_csv(path_):
    df = pd.read_csv(path_)
    print(df.index)
    print(df.columns)
    has_index = False
    index_column_name = ''
    if 'index' in df.columns:
        has_index = True
        index_column_name = 'index'
    elif 'Index' in df.columns:
        has_index = True
        index_column_name = 'Index'

    has_date = False
    if 'date' in df.columns:
        has_date = True
        index_column_name = 'date'
    elif 'Date' in df.columns:
        has_date = True
        index_column_name = 'Date'

    print(has_index, has_date, index_column_name)

    fig = go.Figure()
    for column_name in df.columns:
        if column_name == index_column_name:
            continue

        fig.add_trace(go.Scatter(x=df[index_column_name], y=df[column_name], mode='lines', name=column_name))
    fig.show()


if __name__ == '__main__':
    def parse_args():
        import argparse
        default_path = '/tmp/a.csv'
        parser = argparse.ArgumentParser(description='read file and visualize it')
        parser.add_argument('path', nargs='?', type=str, default=default_path, help='file path')
        args = parser.parse_args()
        return args

    args = parse_args()
    visual_csv(args.path)
    print("end")
