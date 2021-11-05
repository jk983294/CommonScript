import pyarrow as pa

if __name__ == '__main__':
    """
    In a sparse union array, each of the child arrays has the same length as the resulting union array. 
    They are adjuncted with a int8 “types” array that tells, for each value, 
    from which child array it must be selected
    """
    xs = pa.array([5, 6, 7])
    ys = pa.array([False, False, True])
    types = pa.array([0, 1, 1], type=pa.int8())
    union_arr = pa.UnionArray.from_sparse(types, [xs, ys])
    print(union_arr.type)
    print(union_arr)

    """
    In a dense union array, in addition to the int8 “types” array, a int32 “offsets” array that tells, 
    for each value, at each offset in the selected child array it can be found
    """
    xs = pa.array([5, 6, 7])
    ys = pa.array([False, True])
    types = pa.array([0, 1, 1, 0, 0], type=pa.int8())
    offsets = pa.array([0, 0, 1, 1, 2], type=pa.int32())
    union_arr = pa.UnionArray.from_dense(types, offsets, [xs, ys])
    print(union_arr.type)
    print(union_arr)  # [5, False, True, 6, 7]
