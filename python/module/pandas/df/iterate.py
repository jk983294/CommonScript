import pandas as pd
import numpy as np


df = pd.DataFrame({'A': 1.,
                   'B': pd.Timestamp('20130102'),
                   'C': pd.Series(1, index=list(range(4)), dtype='float32'),
                   'D': np.array([3] * 4, dtype='int32'),
                   'E': pd.Categorical(["test", "train", "test", "train"]),
                   'F': 'foo'})

for index, row in df.iterrows():
    print index, row['A'], row['B'], row['C'], row['D'], row['E'], row['F']
