import pyarrow as pa

if __name__ == '__main__':
    arr = pa.array([1, 2, None, 3])
    print(arr.type)
    print(len(arr))
    print(arr.null_count)
    print('index', arr[0])
    print('index', arr[2])  # <pyarrow.Int64Scalar: None>
    print('slice', arr[1:3])  # [2, None] sliced without copying
