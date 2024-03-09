import polars as pl

if __name__ == '__main__':
    s = pl.Series("a", [1, 3, 3, 2, 5])
    print(s.min())
    print(s.max())
    print(s.mean())
    print(s.std(ddof=1))
    print(s.sum())
    print(s.sort())
