import pandas as pd
import numpy as np

dates = pd.date_range('20130101', periods=6)
df = pd.DataFrame(np.random.randn(6, 4), index=dates, columns=list('ABCD'))
print(df)

# shift down
s = pd.Series([1, 3, 5, np.nan, 6, 8], index=dates).shift(2)

# subtraction based on index column, row[index] - s[index]
print(df.sub(s, axis='index'))


# apply function to element
print(df.apply(np.abs))
# apply function to element
print(df.iloc[:, :].apply(lambda x: x - 1))
# apply function to column
print(df.apply(lambda x: x.max() - x.min()))
print(df.apply(lambda x: x.max() - x.min(), axis=1))     # apply function to row
# apply column 2 element - 1
print(df.iloc[:, [2]].apply(lambda x: x - 1))
# apply row 2 element - 1
print(df.iloc[2, :].apply(lambda x: x - 1))
