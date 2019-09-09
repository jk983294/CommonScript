#!/usr/bin/python3
import operator

dict1 = {}
dict1['one'] = 'This is one'
dict1[2] = 'This is two'
tiny_dict = {'name': 'john', 'code': 6734, 'dept': 'sales'}
print(dict1['one'])                                 # Prints value for 'one' key
print(dict1[2])                                     # Prints value for 2 key
print(tiny_dict)                                    # Prints complete dictionary

print(len({'Name': 'Zara', 'Age': 7}))              # 2
print(str({'Name': 'Zara', 'Age': 7}))              # '{'Age': 7, 'Name': 'Zara'}'
print(type({'Name': 'Zara', 'Age': 7}))             # <type 'dict'>

dict1.update(tiny_dict)
dict1.setdefault('Age', None)                       # if has key 'Age', set it to None
print(dict1.items())                                # [(2, 'This is two'), ('one', 'This is one')]
print('No Exist' in dict1)                          # False
dict1.get('No Exist', 'Never')                      # 'Never'
dict1 = dict1.fromkeys(('name', 'age', 'sex'), 10)  # {'age': 10, 'name': 10, 'sex': 10}
dict2 = dict1.copy()                                # shallow copy
print(tiny_dict.keys())                             # ['dept', 'code', 'name']
print(tiny_dict.values())                           # ['sales', 6734, 'john']
del dict1['age']                                    # remove entry with key 'age'
dict1.clear()                                       # remove all entries in dict

# Convert a list to a dictionary in Python
a = ['hello', 'world', '1', '2']
i = iter(a)
b = dict(zip(i, i))                                 # {'1': '2', 'hello': 'world'}

# iterate
prices = {"Orange": 110, "Apple": 240}
for key, value in prices.items():
    print(key, value)
