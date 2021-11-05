import pyarrow as pa
import tempfile
import pathlib
import pyarrow.parquet as pq
import numpy as np
import pyarrow.dataset as ds
from pyarrow import fs

if __name__ == '__main__':
    base = pathlib.Path(tempfile.gettempdir())
    base = base / "parquet_dataset_manual"
    base.mkdir(exist_ok=True)
    table = pa.table({'col1': range(3), 'col2': np.random.randn(3)})
    pq.write_table(table, base / "data_2018.parquet")
    pq.write_table(table, base / "data_2019.parquet")
    print("prepare data to {}".format(base))

    # create a Dataset from a list of files
    schema = pa.schema([("year", pa.int64()), ("col1", pa.int64()), ("col2", pa.float64())])
    dataset = ds.FileSystemDataset.from_paths(
        ["data_2018.parquet", "data_2019.parquet"], schema=schema, format=ds.ParquetFileFormat(),
        filesystem=fs.SubTreeFileSystem(str(base), fs.LocalFileSystem()),
        partitions=[ds.field('year') == 2018, ds.field('year') == 2019])

    # Dataset discovery
    table2 = dataset.to_table()
    print(table2)
    df2 = dataset.to_table(filter=ds.field('year') == 2019).to_pandas()
    print(df2.head())
