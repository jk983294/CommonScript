from collections import OrderedDict
import json

s = '{"name": "ACME", "shares": 50, "price": 490.1}'

data = json.loads(s, object_pairs_hook=OrderedDict)
print(data)


# convert json dict to an object
class JSONObject:
    def __init__(self, d):
        self.__dict__ = d


data = json.loads(s, object_hook=JSONObject)
print(data.name, data.shares, data.price)
