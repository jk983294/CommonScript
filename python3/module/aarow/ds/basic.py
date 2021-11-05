import pyarrow as pa
import tempfile
import pathlib
import pyarrow.parquet as pq
import numpy as np
import pyarrow.dataset as ds

if __name__ == '__main__':
    base = pathlib.Path(tempfile.gettempdir())
    base = base / "parquet_dataset"
    base.mkdir(exist_ok=True)
    table = pa.table({'a': range(10), 'b': np.random.randn(10), 'c': [1, 2] * 5})
    pq.write_table(table.slice(0, 5), base / "data1.parquet")
    pq.write_table(table.slice(5, 10), base / "data2.parquet")
    print("prepare data to {}".format(base))

    # Dataset discovery
    dataset = ds.dataset(base, format="parquet")
    print(dataset.files)
    print(dataset.schema.to_string(show_field_metadata=False))
    table2 = dataset.to_table()
    print(table2)
    df2 = dataset.to_table().to_pandas()
    print(df2.head())
