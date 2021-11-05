import pyarrow as pa

if __name__ == '__main__':
    """
    Fixed-length primitive types: numbers, booleans, date and times, fixed size binary, decimals
    Variable-length primitive types: binary, string
    Nested types: list, struct, and union
    Dictionary type: An encoded categorical type (more on this later)
    """
    t1 = pa.int32()
    t4 = pa.binary(10)
    t5 = pa.timestamp('ms')
    t6 = pa.list_(t1)
    print(t1, t4, t5, t6)

    """
    The Field type is a type plus a name and optional user-defined metadata
    """
    f0 = pa.field('int32_field', t1)
    print(f0, f0.name, f0.type)

    """
    A struct is a collection of named fields
    """
    fields = [pa.field('s0', t1), pa.field('s2', t4), pa.field('s3', t6)]
    t7 = pa.struct(fields)
    print('struct', t7)

    """
    The Schema type defines the column names and types in a record batch or table data structure.
    """
    my_schema = pa.schema(fields)
    print('my_schema', my_schema)
