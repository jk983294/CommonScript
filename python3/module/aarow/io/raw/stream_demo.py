import pyarrow as pa

if __name__ == '__main__':
    path_ = '/tmp/example.ss'
    with pa.output_stream(path_) as stream:
        stream.write(b'some data' * 3)

    stream = pa.input_stream(path_)
    print(stream.read())
