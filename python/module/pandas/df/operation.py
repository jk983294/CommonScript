import pandas as pd
import numpy as np

dates = pd.date_range('20130101', periods=6)
df = pd.DataFrame(np.random.randn(6, 4), index=dates, columns=list('ABCD'))

# shift down
s = pd.Series([1, 3, 5, np.nan, 6, 8], index=dates).shift(2)

print df.sub(s, axis='index')

# apply function to element
print df.apply(np.abs)
# apply function to column
print df.apply(lambda x: x.max() - x.min())
