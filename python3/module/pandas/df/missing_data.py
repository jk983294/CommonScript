import pandas as pd
import numpy as np

dates = pd.date_range('20130101', periods=6)
df = pd.DataFrame(np.random.randn(6, 4), index=dates, columns=list('ABCD'))

# drop any rows that have missing data
df.dropna(how='any')

# fill missing data with given value
df.fillna(value=5)

# get the boolean mask where values are nan
print(pd.isnull(df))
