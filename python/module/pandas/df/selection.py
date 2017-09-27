import pandas as pd
import numpy as np

dates = pd.date_range('20130101', periods=6)
df = pd.DataFrame(np.random.randn(6, 4), index=dates, columns=list('ABCD'))

# select a single column, which yields a series, equivalent to df.A
print df['A']
print df['A'].tolist()          # get column as python list
# select multi columns
print df.loc[:, ['A', 'B']]

# select rows
print df[0:3]
print df['20130102':'20130104']
print df.loc[dates[0]]          # first row


# select both row and column
print df.loc['20130102':'20130104', ['A', 'B']]
print df.loc[dates[0], 'A']


# select by position
print df.iloc[0]                # first row
print df.iloc[3:5, 0:2]
print df.iloc[[1, 2, 4], [0, 2]]
print df.iloc[1:3, :]            # row
print df.iloc[:, 1:3]            # column
print df.iloc[1, 1]              # scalar
print df.iat[1, 1]


# boolean select
print df[df.A > 0]
