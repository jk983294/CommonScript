import pyarrow as pa
import pyarrow.plasma as plasma
import numpy as np

if __name__ == '__main__':
    client = plasma.connect("/tmp/plasma")

    data = np.random.randn(10, 4)
    tensor = pa.Tensor.from_numpy(data)

    object_id = plasma.ObjectID(np.random.bytes(20))
    data_size = pa.ipc.get_tensor_size(tensor)
    buf = client.create(object_id, data_size)

    # Write the tensor into the Plasma-allocated buffer
    stream = pa.FixedSizeBufferWriter(buf)
    pa.ipc.write_tensor(tensor, stream)
    client.seal(object_id)

    # read out data
    [buf2] = client.get_buffers([object_id])
    reader = pa.BufferReader(buf2)
    tensor2 = pa.ipc.read_tensor(reader)
    data2 = tensor2.to_numpy()

    print(data[1], data2[1])
