import pandas as pd
import numpy as np


dates = pd.date_range('20130101', periods=6)
df = pd.DataFrame(np.random.randn(6, 4), index=dates, columns=list('ABCD'))
print(df)

# transpose
print(df.T)

# add new column, auto align with index column
df['E'] = ['one', 'one', 'two', 'three', 'four', 'three']
s1 = pd.Series([1, 2, 3, 4, 5, 6], index=pd.date_range('20130102', periods=6))
df['F'] = s1
print(df)

# set value
df.at[dates[0], 'A'] = 0
df.iat[0, 1] = 0
df.loc[:, 'D'] = np.array([5] * len(df))
print(df)
