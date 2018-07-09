import pandas as pd
import numpy as np

dates = pd.date_range('20130101', periods=6)
df = pd.DataFrame(np.random.randn(6, 4), index=dates, columns=list('ABCD'))
print df

# sorting by an axis
# sort by column name
print df.sort_index(axis=1, ascending=False)
print df.sort_index(axis=0, ascending=False)                    # sort by index

# sorting by column B
# sort by column B
print df.sort_values(by='B')
df.sort_values(by=['B', 'C'], ascending=[1, 0],
               inplace=True)   # multi-column sort
print df
