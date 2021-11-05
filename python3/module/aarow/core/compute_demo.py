import pyarrow as pa
import pyarrow.compute as pc

if __name__ == '__main__':
    a = pa.array([1, 1, 2, 3], type=pa.float64())
    b = pa.array([4, 1, 2, 8], type=pa.float64())
    c = pa.array([True, False, True, False])

    # Aggregations
    print(pc.all(c))  # False
    print(pc.any(c))  # True
    print(pc.count(a))  # 4
    print(pc.count_distinct(a))  # 3
    print(pc.index(a, 2))  # 2
    print(pc.max(a))  # 3.
    print(pc.min(a))  # 1.
    print(pc.min_max(a))  # [('min', 1.0), ('max', 3.0)]
    print(pc.approximate_median(a))  # 1.5
    print('mean', pc.mean(a))  # 1.75
    print(pc.mode(a))  # [1.0, 2]
    print(pc.stddev(a))  # 0.82915619758885
    print(pc.variance(a))  # 0.6875
    print(pc.product(a))  # 6.0
    print(pc.sum(a))  # 7.
    print(pc.quantile(a, q=[0.1, 0.9]))  # [1, 2.7]
    print('tdigest', pc.tdigest(a))  # 1.5

    # bool op
    print(pc.equal(a, b))

    x, y = pa.scalar(7.8), pa.scalar(9.3)
    print(pc.multiply(x, y))
