import pyarrow as pa
import pyarrow.compute as pc


def buffer_demo():
    """
    Buffer object wraps the C++ arrow::Buffer type.
    It permits higher-level array classes to safely interact with memory which they may or may not own.
    arrow::Buffer can be zero-copy sliced to permit Buffers to cheaply reference other Buffers.
    """
    data = b'abcdefghijklmnopqrstuvwxyz'
    buf = pa.py_buffer(data)
    print(buf)
    print(buf.size)

    m = memoryview(buf)
    print(m)

    b = buf.to_pybytes()  # making a copy of the data
    print(b)


def pool_demo():
    print(pa.total_allocated_bytes())
    buf = pa.allocate_buffer(1024, resizable=True)  # allocate a resizable Buffer from the default pool
    print(pa.total_allocated_bytes())
    buf = None
    print(pa.total_allocated_bytes())  # gc
    print(pa.default_memory_pool().backend_name)


if __name__ == '__main__':
    buffer_demo()
    pool_demo()
