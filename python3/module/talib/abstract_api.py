import numpy as np
import talib
from talib import abstract

inputs = {
    'open': np.random.random(50),
    'high': np.random.random(50),
    'low': np.random.random(50),
    'close': np.random.random(50),
    'volume': np.random.random(50)
}

inputs2 = {
    'open': np.random.random(50),
    'high': np.random.random(50),
    'low': np.random.random(50),
    'close': np.random.random(50),
    'volume': np.random.random(50)
}

sma = abstract.SMA
sma = abstract.Function('sma')

output = sma(inputs, timeperiod=25)   # calculate on close prices by default
print('sma on close', output)

output = sma(inputs, timeperiod=25, price='open')     # calculate on opens
print('sma on open', output)

upper, middle, lower = abstract.BBANDS(inputs, 20, 2, 2)
print('middle', middle)

slowk, slowd = abstract.STOCH(inputs, 5, 3, 0, 3, 0)   # uses high, low, close by default
slowk, slowd = abstract.STOCH(inputs, 5, 3, 0, 3, 0, prices=['high', 'low', 'open'])
print(slowk)
print(slowd)

# change inputs
sma.parameters = {'timeperiod': 15}
result1 = sma.run(inputs)
result2 = sma.run(inputs2)

# or change the parameters:
sma.input_arrays = inputs2
ma10 = sma(timeperiod=5)
ma20 = sma(10)
print(ma10)
print(ma20)
