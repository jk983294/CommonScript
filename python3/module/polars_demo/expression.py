import polars as pl


def select_demo(df):
    df1 = df.head(1)
    print(df1.select(pl.col("close", "volume")))
    print(df1.select(pl.col("*")))  # all columns
    print(df1.select(pl.exclude("close")))  # all columns but close
    print(df.select(pl.col("close"), pl.col("volume")).limit(3))
    print(df.select(pl.col("ukey"), pl.col("date")).n_unique())
    print(df.select(pl.col("ukey")).n_unique())
    print(df1.select([pl.col("close").max().alias("max"),
                      pl.col("close").mean().alias("mean"),
                      pl.col("close").median().alias("median")]))


def filter_demo(df):
    print(df.filter(pl.col("date").is_between(20080102, 20080103)).limit(1))
    print(df.filter((pl.col("date") <= 20080103) & (pl.col("close").is_not_nan())).limit(1))


def calc_new_column(df):
    df1 = df.with_columns(pl.col("date").sum().alias("date_sum"))
    df1 = df1.with_columns((pl.col("date_sum") + 42).alias("date_sum_add_42"))
    print(df1.select(pl.col("date_sum", "date_sum_add_42")).limit(3))
    df1 = df.filter(pl.col("close").is_not_nan()).limit(3)
    print(df1)
    df1_1 = df1.with_columns((pl.col("close") * pl.col("oi")).alias("close_*_oi")).select(
        pl.all().exclude(["major_rol", "tradable"])
    )
    print(df1_1)


def group_by_stat(df):
    print(df.group_by("ukey", maintain_order=True).count())
    print(df.group_by("ukey", maintain_order=True).
          agg(pl.count()).sort("count").
          with_columns([(pl.col("count") / pl.col("count").sum()).alias("n_pct")]))
    print(df.group_by(["ukey", "tradable"], maintain_order=True).count())
    df1 = df.filter(pl.col("close").is_not_nan())
    stats = df1.group_by(["ukey", "tradable"], maintain_order=True).agg(
        pl.col("close").count().alias("count"),
        pl.col("close").sum().alias("sum"),
    )
    print(stats)


if __name__ == '__main__':
    file_ = "/home/kun/sim_data/fra_test/fut.feather"
    df = pl.read_ipc(file_)
    select_demo(df)
    filter_demo(df)
    group_by_stat(df)
    # calc_new_column(df)
