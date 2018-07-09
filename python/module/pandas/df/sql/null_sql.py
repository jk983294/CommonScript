import pandas as pd
import numpy as np

frame = pd.DataFrame({'col1': ['A', 'B', np.NaN, 'C', 'D'], 'col2': [
                     'F', np.NaN, 'G', 'H', 'I']})

# SELECT * FROM frame WHERE col2 IS NULL;
print frame[frame['col2'].isna()]

# SELECT * FROM frame WHERE col1 IS NOT NULL;
print frame[frame['col1'].notna()]
