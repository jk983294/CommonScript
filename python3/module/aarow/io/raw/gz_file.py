import gzip
import pyarrow as pa

if __name__ == '__main__':
    path_ = '/tmp/example.gz'
    # with gzip.open(path_, 'wb') as f:
    #     f.write(b'some data\n' * 3)

    stream = pa.input_stream(path_)
    print(stream.read())
