import pyarrow as pa


def method1(batch):
    sink = pa.BufferOutputStream()
    with pa.ipc.new_stream(sink, batch.schema) as writer:
        for i in range(5):
            writer.write_batch(batch)

    buf = sink.getvalue()
    print('buf size {}'.format(buf.size))

    with pa.ipc.open_stream(buf) as reader:
        schema = reader.schema
        # batches = [b for b in reader]
        # print(len(batches))
        print(schema)

        df = reader.read_pandas()
        print(df)


def method2(batch):
    sink = pa.BufferOutputStream()
    with pa.ipc.new_file(sink, batch.schema) as writer:
        for i in range(5):
            writer.write_batch(batch)

    buf = sink.getvalue()
    print('buf size {}'.format(buf.size))

    with pa.ipc.open_file(buf) as reader:
        schema = reader.schema
        num_record_batches = reader.num_record_batches
        b = reader.get_batch(3)
        print(schema)
        print(b.equals(batch))

        df = reader.read_pandas()
        print(df)


if __name__ == '__main__':
    data = [pa.array([1, 2, 3, 4]), pa.array(['foo', 'bar', 'baz', None]), pa.array([True, None, False, True])]
    batch_ = pa.RecordBatch.from_arrays(data, ['f0', 'f1', 'f2'])
    method1(batch_)
    method2(batch_)
