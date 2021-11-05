import pyarrow as pa

if __name__ == '__main__':
    print(pa.__version__)
    print(pa.get_include())
    print(pa.get_libraries())
    print(pa.get_library_dirs())
