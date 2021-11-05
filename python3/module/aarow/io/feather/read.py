import pyarrow as pa
import pyarrow.feather as feather

if __name__ == '__main__':
    path_ = "/tmp/test.df.feather"
    df = feather.read_feather(path_)
    print('read from {}'.format(path_))
    print(df.head())

    path_ = "/tmp/test.table.feather"
    table = feather.read_table(path_)
    print('read from {}'.format(path_))
    print(len(table))
    df = table.to_pandas()
    print(df.head())
