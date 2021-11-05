import pyarrow as pa
import pyarrow.parquet as pq
import pyarrow.compute as pc


def create_table():
    days = pa.array([1, 12, 17, 23, 28], type=pa.int8())
    months = pa.array([1, 3, 5, 7, 1], type=pa.int8())
    years = pa.array([1990, 2000, 1995, 2000, 1995], type=pa.int16())
    return pa.table([days, months, years], names=["days", "months", "years"])


def do_calc(table_):
    res = pc.value_counts(table_["years"])
    print(res)


if __name__ == '__main__':
    table = create_table()
    print(table)

    path_ = "/tmp/birthdays.parquet.test"
    pq.write_table(table, path_)

    table2 = pq.read_table(path_)
    print(table2)

    do_calc(table2)
