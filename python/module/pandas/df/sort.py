import pandas as pd
import numpy as np

dates = pd.date_range('20130101', periods=6)
df = pd.DataFrame(np.random.randn(6, 4), index=dates, columns=list('ABCD'))

# sorting by an axis
print df.sort_index(axis=1, ascending=False)

# sorting by value
print df.sort_values(by='B')
