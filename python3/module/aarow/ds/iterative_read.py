import pyarrow as pa
import tempfile
import pathlib
import pyarrow.parquet as pq
import numpy as np
import pyarrow.dataset as ds
from pyarrow import fs
import pyarrow.compute as pc

if __name__ == '__main__':
    base = pathlib.Path(tempfile.gettempdir())
    base = base / "parquet_dataset_manual"

    # create a Dataset from a list of files
    schema = pa.schema([("year", pa.int64()), ("col1", pa.int64()), ("col2", pa.float64())])
    dataset = ds.FileSystemDataset.from_paths(
        ["data_2018.parquet", "data_2019.parquet"], schema=schema, format=ds.ParquetFileFormat(),
        filesystem=fs.SubTreeFileSystem(str(base), fs.LocalFileSystem()),
        partitions=[ds.field('year') == 2018, ds.field('year') == 2019])

    col2_sum = 0
    count = 0
    for batch in dataset.to_batches(columns=["col2"], filter=~ds.field("col2").is_null()):
        col2_sum += pc.sum(batch.column("col2")).as_py()
        count += batch.num_rows

    mean_a = col2_sum / count
    print(mean_a)
