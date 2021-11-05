import pyarrow as pa
import pyarrow.compute as pc

if __name__ == '__main__':
    t = pa.table({'x': [1, 2, 3], 'y': [3, 2, 1]})
    i = pc.sort_indices(t, sort_keys=[('y', 'ascending')])
    print(i)
