import pyarrow as pa
from pyarrow import csv

if __name__ == '__main__':
    fn = '/tmp/test.csv.gz'
    table = csv.read_csv(fn, convert_options=pa.csv.ConvertOptions(
        column_types={
            'one': pa.decimal128(precision=10, scale=2),
            'two': pa.decimal128(precision=10, scale=2),
        }))

    print(len(table))
    df = table.to_pandas()
    print(df.head())
