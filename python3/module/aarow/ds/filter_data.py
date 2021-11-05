import pyarrow.dataset as ds

if __name__ == '__main__':
    base = "/tmp/parquet_dataset"
    dataset = ds.dataset(base, format="parquet")
    df = dataset.to_table(columns=['a', 'b']).to_pandas()
    print(df.head())

    df = dataset.to_table(filter=ds.field('a') >= 7).to_pandas()
    print(df.head())

    df = dataset.to_table(filter=ds.field('a').isin([1, 2, 3])).to_pandas()
    print(df.head())

    df = dataset.to_table(filter=ds.field('c') == 2).to_pandas()
    print(df.head())

    df = dataset.to_table(filter=(ds.field('a') > ds.field('b')) & (ds.field('c') > 1)).to_pandas()
    print(df.head())
