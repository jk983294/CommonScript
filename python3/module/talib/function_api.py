import numpy as np
import talib
from talib import MA_Type

close = np.random.random(50)
output = talib.SMA(close)
print(close)
print(output)

upper, middle, lower = talib.BBANDS(close, matype=MA_Type.T3) # bollinger bands with triple exponential moving average
print(middle)

output = talib.MOM(close, timeperiod=5)     # momentum
print(output)
