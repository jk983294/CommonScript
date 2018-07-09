import pandas as pd
import numpy as np


df = pd.DataFrame({'A': [1, 2, 3], 'B': [400, 500, 600]})

# iterate and update
for index, row in df.iterrows():
    if row['A'] == 1:
        row['B'] = 4

print df

# update with replace column
new_df = pd.DataFrame({'B': [4, 5, 6]})
df.update(new_df)
print df

# update 'B' to 0 when 'A' is 0
df.loc[df['A'] == 1, 'B'] = 0
print df

# update with a if-then-else scheme
df["B"] = np.where((df.A == 2), 0, 1)
print df
