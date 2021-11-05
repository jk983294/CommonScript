import pyarrow as pa

if __name__ == '__main__':
    arr = pa.array([[], None, [1, 2], [None, 1]])
    print(arr.type)  # list<item: int64>
    print(len(arr))
    print(arr.null_count)
    print('index', arr[0])
    print('index', arr[2])
    print('slice', arr[1:3])
