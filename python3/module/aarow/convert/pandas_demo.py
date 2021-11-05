import pyarrow as pa
import numpy as np
import pandas as pd


def normal():
    df = pd.DataFrame({"a": [1, 2, 3]})
    table = pa.Table.from_pandas(df)
    df_new = table.to_pandas()

    schema = pa.Schema.from_pandas(df)
    print(schema)
    print(df)
    print(df_new)


def categorical_demo():
    df = pd.DataFrame({"cat": pd.Categorical(["a", "b", "c", "a", "b", "c"])})
    table = pa.Table.from_pandas(df)
    column = table[0]
    chunk = column.chunk(0)
    print(chunk.dictionary)
    print(chunk.indices)


def timestamp_demo():
    df = pd.DataFrame({"datetime": pd.date_range("2020-01-01T00:00:00Z", freq="H", periods=3)})
    print(df.dtypes)
    table = pa.Table.from_pandas(df)
    column = table[0]
    chunk = column.chunk(0)
    print(chunk.type)  # timestamp[ns, tz=UTC]
    print(chunk)


def null_demo():
    """
    when an Arrow array or table gets converted to pandas,
    integer columns will become float when missing values are present
    """
    arr = pa.array([1, 2, None])
    df = arr.to_pandas()
    print(arr)
    print(df)


if __name__ == '__main__':
    normal()
    categorical_demo()
    timestamp_demo()
    null_demo()
