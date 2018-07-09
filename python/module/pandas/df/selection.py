import pandas as pd
import numpy as np

dates = pd.date_range('20130101', periods=6)
df = pd.DataFrame(np.random.randn(6, 4), index=dates, columns=list('ABCD'))

# select a single column, which yields a series, equivalent to df.A
print df['A']                   # get index and A column
print df['A'].tolist()          # get column as python list
print df.loc[:, ['A']]          # select one column
print df.loc[:, ['A', 'B']]     # select multi columns

# select rows
print df[0:3]                   # get row 0 ~ 2
print df['20130102':'20130104']
print df.loc[dates[0]]          # first row


# select both row and column
print df.loc['20130102':'20130104', ['A', 'B']]
print df.loc[dates[0], 'A']

# loc select based on index while iloc select based on row number
# select by position
print df.iloc[0]                    # first row
print df.iloc[3:5, 0:2]
print df.iloc[[1, 2, 4], [0, 2]]
print df.iloc[1:3, :]               # row 1 ~ 2
print df.iloc[:, 1:3]               # column B and C
print df.iloc[:, [2]]               # column C
print df.iloc[1, 1]                 # scalar
print df.iat[1, 1]


# boolean select
print df[df.A > 0]

df1 = pd.DataFrame([[1, 2, 3], [1, 3, 4], [2, 4, 3]],
                   index=['a', 'b', 'c'], columns=['A', 'B', 'C'])
print df1[df1['A'].isin([1])]       # select rows which column A value is 1
