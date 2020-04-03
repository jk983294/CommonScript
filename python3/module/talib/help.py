from talib import abstract
import talib

print('function_flags', abstract.Function('sma').function_flags)
print('input_names', abstract.Function('sma').input_names)
print('input_arrays', abstract.Function('sma').input_arrays)
print('parameters', abstract.Function('sma').parameters)
print('lookback', abstract.Function('sma').lookback)
print('output_names', abstract.Function('sma').output_names)
print('output_flags', abstract.Function('sma').output_flags)
print('info', abstract.Function('sma').info)
print('info', abstract.Function('sma', timeperiod=5).info)

print('get_function_groups', talib.get_function_groups())
print('get_functions', talib.get_functions())

# https://mrjbq7.github.io/ta-lib/doc_index.html
