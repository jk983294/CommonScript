import pyarrow as pa

if __name__ == '__main__':
    ty = pa.struct([('x', pa.int8()), ('y', pa.bool_())])
    arr = pa.array([{'x': 1, 'y': True}, {'x': 2, 'y': False}, {'x': 3, 'y': False}], type=ty)
    arr1 = pa.array([(3, True), (4, False)], type=ty)
    arr2 = pa.array([{'x': 1}, None, {'y': None}], type=ty)  # missing key as null value
    print(arr.type)  # list<item: int64>
    print(len(arr))
    print(arr.null_count)
    print('index', arr[0])
    print('index', arr[1])
    print('slice', arr[0:2])

    print('missing key', arr2)

    """
    data storage will be shared with the individual arrays, and no copy is involved
    """
    xs = pa.array([5, 6, 7], type=pa.int16())
    ys = pa.array([False, True, True])
    arr3 = pa.StructArray.from_arrays((xs, ys), names=('x', 'y'))
    print(arr3)
