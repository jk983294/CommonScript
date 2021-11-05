import pyarrow as pa

if __name__ == '__main__':
    """
    A Record Batch in Apache Arrow is a collection of equal-length array instances.
    """
    data = [pa.array([1, 2, 3, 4]), pa.array(['foo', 'bar', 'baz', None]), pa.array([True, None, False, True])]
    batch = pa.RecordBatch.from_arrays(data, ['f0', 'f1', 'f2'])
    print(batch.num_columns)  # 3
    print(batch.num_rows)  # 4
    print(batch.schema)  # f0: int64 f1: string f2: bool

    #  sliced without copying memory like an array
    batch2 = batch.slice(1, 3)
    print(batch2[1])
