import datetime
import pyarrow as pa
import pyarrow.dataset as ds
import pyarrow.compute as pc
from module.aarow.table.table_demo import create_table


def save_ds(data_, dir_, partition_key):
    ds.write_dataset(data_, dir_, format="parquet",
                     partitioning=ds.partitioning(pa.schema([data_.schema.field(partition_key)])))


if __name__ == '__main__':
    table = create_table()

    # dataset work with large data, which will handle partitioning of data in smaller chunks
    save_dir = '/tmp/ds_test_dir/'
    # save_ds(table, save_dir, "years")

    ds2 = ds.dataset(save_dir, format="parquet", partitioning=["years"])
    print(ds2.files)

    current_year = datetime.datetime.utcnow().year
    for table_chunk in ds2.to_batches():
        print("AGES", pc.subtract(pa.scalar(current_year, type=pa.int32()), table_chunk["years"]))
