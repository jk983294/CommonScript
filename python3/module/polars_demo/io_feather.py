import polars as pl

if __name__ == '__main__':
    file_ = "/home/kun/sim_data/fra_test/fut.feather"
    out_file = "/tmp/sample.feather"
    schema = pl.read_ipc_schema(file_)
    print(schema)

    df = pl.read_ipc(file_)
    print(df.describe())

    df1 = df.sample(3)
    df1.write_ipc(out_file)

    df2 = pl.read_ipc(out_file)
    print(df2)
