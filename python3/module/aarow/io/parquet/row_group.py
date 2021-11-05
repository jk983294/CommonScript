import pyarrow as pa
import pandas as pd
import numpy as np
import pyarrow.parquet as pq

if __name__ == '__main__':
    # write
    path_ = "/tmp/test.parquet"
    parquet_file = pq.ParquetFile(path_)
    meta = parquet_file.metadata
    print(meta)
    print(parquet_file.schema)
    print(meta.row_group(0))
    print(meta.row_group(0).column(0))

    table = parquet_file.read_row_group(0)
    df = table.to_pandas()
    print(df.head())
