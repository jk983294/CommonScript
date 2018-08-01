import pandas as pd
import numpy as np
from itertools import izip

df = pd.DataFrame({'A': 1.,
                   'B': pd.Timestamp('20130102'),
                   'C': pd.Series(1, index=list(range(4)), dtype='float32'),
                   'D': np.array([3] * 4, dtype='int32'),
                   'E': pd.Categorical(["test", "train", "test", "train"]),
                   'F': 'foo'})

# be care for below iteration method, index is pd's index, not the row number, i.e. it could be string
for index, row in df.iterrows():
    print(index, row['A'], row['B'], row['C'], row['D'], row['E'], row['F'])

# modify the rows you're iterating over, then df.apply is preferred:
df['new_column'] = df.apply(lambda row: row['A'] + 1.0, axis=1)
print('new column added')
print (df)

# or
another_column = []
for i, row in df.iterrows():
    another_column.append(row['A'] + 2.0)
df['another_column'] = another_column
print('another new column added')
print (df)

# better performance, it lost info, only refer as position value as row[1]
another_column1 = []
for i, row in enumerate(df.values):     # here i is int counter not pd's index
    another_column1.append((df.index[i] + row[0]))
df['another_column1'] = another_column1
print('another new column1 added')
print (df)

# most efficient
another_column2 = []
for row in izip(df.index, df['A']):
    another_column2.append((row[0] + row[1] + 2.0))
df['another_column2'] = another_column2
print('another new column2 added')
print (df)
