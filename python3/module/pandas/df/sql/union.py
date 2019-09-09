import pandas as pd
import numpy as np

df1 = pd.DataFrame(
    {'city': ['Chicago', 'San Francisco', 'New York City'], 'rank': range(1, 4)})
df2 = pd.DataFrame(
    {'city': ['Chicago', 'Boston', 'Los Angeles'], 'rank': [1, 4, 5]})

# SELECT city, rank FROM df1 UNION ALL SELECT city, rank FROM df2;
print(pd.concat([df1, df2]))                             # keep dupe

# SELECT city, rank FROM df1 UNION SELECT city, rank FROM df2;
print(pd.concat([df1, df2]).drop_duplicates())           # remove dupe
