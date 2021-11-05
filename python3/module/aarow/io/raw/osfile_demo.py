import pyarrow as pa

if __name__ == '__main__':
    path_ = '/tmp/example.pa.1'
    with pa.OSFile(path_, 'wb') as f:
        f.write(b'some data' * 3)

    file_obj = pa.OSFile(path_)
    print(file_obj.read())

    mmap = pa.memory_map(path_)
    print(mmap.read())

    mmap.seek(0)
    buf = mmap.read_buffer(4)
    print(buf)
