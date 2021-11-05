import pyarrow as pa
import pandas as pd
import pyarrow.csv as csv

if __name__ == '__main__':
    d = {'one': pd.Series([1.1, 2.2, 3.3, 4.4]),
         'two': pd.Series([1., 2., 3., 4.])}
    df = pd.DataFrame(d)
    table = pa.Table.from_pandas(df)

    path_ = "/tmp/test.csv"
    options = csv.WriteOptions(include_header=True)
    csv.write_csv(table, path_, options)
    with pa.CompressedOutputStream(path_ + ".gz", "gzip") as out:
        csv.write_csv(table, out)

    print('write to {}'.format(path_))
    print('write to {}.gz'.format(path_))
