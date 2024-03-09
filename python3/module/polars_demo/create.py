import polars as pl
import numpy as np

if __name__ == '__main__':
    df = pl.DataFrame(
        {
            "a": np.arange(0, 8),
            "b": np.random.rand(8),
            "d": [1, 2.0, np.NaN, np.NaN, 0, -5, -42, None],
        }
    )

    df2 = pl.DataFrame(
        {
            "x": np.arange(0, 8),
            "y": ["A", "A", "A", "B", "B", "C", "X", "X"],
        }
    )

    df3 = pl.DataFrame(
        {
            "x": np.arange(0, 8),
            "y": ["C", "C", "X", "X", "B", "C", "Y", "Y"],
        }
    )

    stacked = df.hstack(df2)  # add columns
    print(stacked)

    stacked1 = df2.vstack(df3)  # add rows
    print(stacked1)
