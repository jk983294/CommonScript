import pyarrow as pa

if __name__ == '__main__':
    path_ = '/tmp/bigfile.arrow'
    BATCH_SIZE = 10000
    NUM_BATCHES = 1000
    schema = pa.schema([pa.field('nums', pa.int32())])

    with pa.OSFile(path_, 'wb') as sink:
        with pa.ipc.new_file(sink, schema) as writer:
            for row in range(NUM_BATCHES):
                batch = pa.record_batch([pa.array(range(BATCH_SIZE), type=pa.int32())], schema)
                writer.write(batch)

    with pa.OSFile(path_, 'rb') as source:
        loaded_array = pa.ipc.open_file(source).read_all()
    print("LEN:", len(loaded_array))
    print("RSS: {}MB".format(pa.total_allocated_bytes() >> 20))  # RSS: 38MB

    # avoid having to allocate its own memory
    with pa.memory_map(path_, 'rb') as source:
        loaded_array = pa.ipc.open_file(source).read_all()
    print("LEN:", len(loaded_array))
    print("RSS: {}MB".format(pa.total_allocated_bytes() >> 20))  # RSS: 0MB
