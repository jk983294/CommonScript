import pyarrow as pa
import numpy as np

if __name__ == '__main__':
    data = np.arange(10, dtype='int16')
    arr = pa.array(data)
    print(arr)

    data_view = arr.to_numpy()
    print(data_view)
