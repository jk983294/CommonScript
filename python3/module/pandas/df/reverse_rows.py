import pandas as pd
import numpy as np

# df from numpy array and date array
dates = pd.date_range('20130101', periods=6)
df = pd.DataFrame(np.random.randn(6, 4), index=dates, columns=list('ABCD'))
print(df)

reversed_df = df.iloc[::-1]
print(reversed_df)
