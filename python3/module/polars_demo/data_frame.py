import polars as pl
from datetime import datetime

if __name__ == '__main__':
    df = pl.DataFrame(
        {
            "integer": [1, 2, 3, 4, 5],
            "date": [
                datetime(2022, 1, 1),
                datetime(2022, 1, 2),
                datetime(2022, 1, 3),
                datetime(2022, 1, 4),
                datetime(2022, 1, 5),
            ],
            "float": [4.0, 5.0, 6.0, 7.0, 8.0],
        }
    )
    print(df)
    print(df.head(1))
    print(df.tail(1))
    print(df.sample(2))
    print(df.describe())
