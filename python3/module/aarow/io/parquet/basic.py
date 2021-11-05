import pyarrow as pa
import pandas as pd
import numpy as np
import pyarrow.parquet as pq

if __name__ == '__main__':
    df = pd.DataFrame({'one': [-1, np.nan, 2.5],
                       'two': ['foo', 'bar', 'baz'],
                       'three': [True, False, True]},
                      index=list('abc'))
    table = pa.Table.from_pandas(df, preserve_index=False)  # omit index give better perf

    # write
    path_ = "/tmp/test.parquet"
    pq.write_table(table, path_)
    print('write to {}'.format(path_))

    # read
    table2 = pq.read_table(path_)
    df2 = table2.to_pandas()
    print(df2.head())

    # read specified columns
    table3 = pq.read_table(path_, columns=['one', 'three'])
    df3 = table3.to_pandas()
    print(df3.head())
