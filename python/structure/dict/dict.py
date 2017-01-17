#!/usr/bin/python
from itertools import izip

dict = {}
dict['one'] = 'This is one'
dict[2]     = 'This is two'
tinydict = {'name': 'john','code':6734, 'dept': 'sales'}
print dict['one']                                                           # Prints value for 'one' key
print dict[2]                                                               # Prints value for 2 key
print tinydict                                                              # Prints complete dictionary


print cmp({'Name': 'Zara', 'Age': 7}, {'Name': 'Mahnaz', 'Age': 27})        # -1
print len ({'Name': 'Zara', 'Age': 7})                                      # 2
print str ({'Name': 'Zara', 'Age': 7})                                      # '{'Age': 7, 'Name': 'Zara'}'
print type ({'Name': 'Zara', 'Age': 7})                                     # <type 'dict'>


dict.update(tinydict)
dict.setdefault('Age', None)                                                # if has key 'Age', set it to None
print dict.items()                                                          # [(2, 'This is two'), ('one', 'This is one')]
dict.has_key('No Exist')                                                    # False
dict.get('No Exist', 'Never')                                               # 'Never'
dict = dict.fromkeys(('name', 'age', 'sex'), 10)                            # {'age': 10, 'name': 10, 'sex': 10}
dict2 = dict.copy()                                                         # shallow copy
print tinydict.keys()                                                       # ['dept', 'code', 'name']
print tinydict.values()                                                     # ['sales', 6734, 'john']
del dict['one']                                                             # remove entry with key 'one'
dict.clear()                                                                # remove all entries in dict

# Convert a list to a dictionary in Python
a = ['hello','world','1','2']
i = iter(a)
b = dict(izip(i, i))                                                        # {'1': '2', 'hello': 'world'}

# iterate
prices={"Orange": 110, "Apple": 240}
for key, value in prices.iteritems():
    print key, value
