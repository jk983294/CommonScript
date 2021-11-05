import pyarrow as pa
import pandas as pd
import pyarrow.feather as feather

if __name__ == '__main__':
    d = {'one': pd.Series([1.1, 2.2, 3.3, 4.4]),
         'two': pd.Series([1., 2., 3., 4.])}
    df = pd.DataFrame(d)
    path_ = "/tmp/test.df.feather"
    feather.write_feather(df, path_)  # Uses LZ4 by default
    print('write to {}'.format(path_))

    table = pa.Table.from_pandas(df)
    path_ = "/tmp/test.table.feather"
    feather.write_feather(table, path_, compression='zstd')  # Uses zstd compression
    print('write to {}'.format(path_))
