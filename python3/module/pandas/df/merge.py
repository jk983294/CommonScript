import pandas as pd
import numpy as np

# concat by row
df = pd.DataFrame(np.random.randn(10, 4))
pieces = [df[:3], df[3:7], df[7:]]
print(pd.concat(pieces))

# append to row, example show append row 3 to the tail
df1 = pd.DataFrame(np.random.randn(8, 4), columns=['A', 'B', 'C', 'D'])
s = df1.iloc[3]                             # get row 3
print(df1.append(s, ignore_index=True))

# SQL like join to merge dataframe
left = pd.DataFrame({'key': ['foo', 'foo'], 'lval': [1, 2]})
right = pd.DataFrame({'key': ['foo', 'foo'], 'rval': [4, 5]})
print(left)
print(right)
print(pd.merge(left, right, on='key'))       # inner join

# SQL like group by
df2 = pd.DataFrame({'A': ['foo', 'bar', 'foo', 'bar',
                          'foo', 'bar', 'foo', 'foo'],
                    'B': ['one', 'one', 'two', 'three',
                          'two', 'two', 'one', 'three'],
                    'C': np.random.randn(8),
                    'D': np.random.randn(8)})
print(df2.groupby('A').sum())
print(df2.groupby(['A', 'B']).sum())
