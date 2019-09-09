import importlib

math = importlib.import_module('math')
print(math.sin(2))                  # 0.9092974268256817


# same as 'from . import pkg3'
b = importlib.import_module('.pkg3', __package__)
