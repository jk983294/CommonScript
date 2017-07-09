import pandas as pd
import numpy as np


df = pd.DataFrame({'A': 1.,
                   'B': pd.Timestamp('20130102'),
                   'C': pd.Series(1, index=list(range(4)), dtype='float32'),
                   'D': np.array([3] * 4, dtype='int32'),
                   'E': pd.Categorical(["test", "train", "test", "train"]),
                   'F': 'foo'})

# data types for all columns
print df.dtypes

# show head or tail rows, default is 5, also allow feed number to it
print df.head()
print df.tail(3)

# display the index, columns, and the underlying numpy data
print df.index
print df.columns
print df.values

# quick statistic summary: count, mean, std, min, 25%, 50%, 75%, max
print df.describe()
print df.mean()