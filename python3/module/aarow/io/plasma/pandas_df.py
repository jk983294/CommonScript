import pyarrow as pa
import pyarrow.plasma as plasma
import numpy as np
import pandas as pd

if __name__ == '__main__':
    client = plasma.connect("/tmp/plasma")

    d = {'one': pd.Series([1., 2., 3.], index=['a', 'b', 'c']),
         'two': pd.Series([1., 2., 3., 4.], index=['a', 'b', 'c', 'd'])}
    df = pd.DataFrame(d)
    record_batch = pa.RecordBatch.from_pandas(df)

    object_id = plasma.ObjectID(np.random.bytes(20))
    mock_sink = pa.MockOutputStream()
    with pa.RecordBatchStreamWriter(mock_sink, record_batch.schema) as stream_writer:
        stream_writer.write_batch(record_batch)
    data_size = mock_sink.size()
    buf = client.create(object_id, data_size)

    #  Write the PyArrow RecordBatch to Plasma
    stream = pa.FixedSizeBufferWriter(buf)
    with pa.RecordBatchStreamWriter(stream, record_batch.schema) as stream_writer:
        stream_writer.write_batch(record_batch)
    client.seal(object_id)

    # read out data
    [buf2] = client.get_buffers([object_id])
    buffer2 = pa.BufferReader(buf2)
    # Convert object back into an Arrow RecordBatch
    reader = pa.RecordBatchStreamReader(buffer2)
    record_batch = reader.read_next_batch()
    data2 = record_batch.to_pandas()

    print(df[1:2])
    print(data2[1:2])
