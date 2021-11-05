import pyarrow.dataset as ds

if __name__ == '__main__':
    base = "/tmp/parquet_dataset"
    dataset = ds.dataset(base, format="parquet")
    projection = {
        "a_renamed": ds.field("a"),
        "b_as_float32": ds.field("b").cast("float32"),
        "c_1": ds.field("c") == 1,
    }
    df = dataset.to_table(columns=projection).to_pandas()
    print(df.head())

    projection = {col: ds.field(col) for col in dataset.schema.names}
    projection.update({"b_large": ds.field("b") > 1})
    df = dataset.to_table(columns=projection).to_pandas()
    print(df.head())
