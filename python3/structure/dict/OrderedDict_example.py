from collections import OrderedDict
import json

my_dict = OrderedDict()
my_dict["first"] = 33
my_dict["second"] = 87
my_dict["third"] = 99
my_dict["fourth"] = 1010

for key, value in my_dict.items():
    print(key, value)

# last item ('fourth', 1010), OrderedDict([('first', 33), ('second', 87), ('third', 99)])
key, value = my_dict.popitem()

# when dump out, it keeps the order in the dumped out dict
print(json.dumps(my_dict))              # {"first": 33, "second": 87, "third": 99}
