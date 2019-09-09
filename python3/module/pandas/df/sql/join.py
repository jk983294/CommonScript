import pandas as pd
import numpy as np

df1 = pd.DataFrame({'key': ['A', 'B', 'C', 'D'], 'value': np.random.randn(4)})
df2 = pd.DataFrame({'key': ['B', 'D', 'D', 'E'], 'value': np.random.randn(4)})
print(df1)
print(df2)

# SELECT * FROM df1 INNER JOIN df2 ON df1.key = df2.key;
print(pd.merge(df1, df2, on='key'))
# in case join key is different
print(pd.merge(df1, df2, left_on='key', right_on='key'))

# SELECT * FROM df1 LEFT OUTER JOIN df2 ON df1.key = df2.key;
print(pd.merge(df1, df2, on='key', how='left'))

# SELECT * FROM df1 RIGHT OUTER JOIN df2 ON df1.key = df2.key;
print(pd.merge(df1, df2, on='key', how='right'))

# SELECT * FROM df1 FULL OUTER JOIN df2 ON df1.key = df2.key;
print(pd.merge(df1, df2, on='key', how='outer'))
