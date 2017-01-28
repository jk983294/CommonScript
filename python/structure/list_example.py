#!/usr/bin/python

list1 = ['abcd', 786, 2.23, 'john', 70.2]
tiny_list = [123, 'john']

print list1  # Prints complete list
print list1[0]  # Prints first element of the list
print list1[1:3]  # Prints elements starting from 2nd till 3rd
print list1[2:]  # Prints elements starting from 3rd element
print tiny_list * 2  # Prints list two times
print list1 + tiny_list  # Prints concatenated lists

[1, 2, 3] + [4, 5, 6]  # [1, 2, 3, 4, 5, 6]
['Hi!'] * 4  # ['Hi!', 'Hi!', 'Hi!', 'Hi!']
3 in [1, 2, 3]  # True

# built-in
len([1, 2, 3])  # 3
cmp([123, 'xyz'], [456, 'abc'])  # -1
max([456, 700, 200])  # 700
min([456, 700, 200])  # 200
list((123, 'xyz', 'zara', 'abc'))  # [123, 'xyz', 'zara', 'abc']
[123, 'xyz'].append(2009)  # [123, 'xyz', 2009]
[123, 'xyz'].count(123)  # 1
[123, 'xyz'].extend([2009, 'manni'])  # [123, 'xyz', 2009, 'manni']
[123, 'xyz'].index('xyz')  # 1
[123, 'xyz'].insert(1, 2009)  # [123, 2009, 'xyz']
[123, 'xyz'].pop()  # [123] and return 'xyz'
[123, 'xyz'].remove(123)  # ['xyz']
[123, 'xyz'].reverse()  # ['xyz', 123]
[123, 'xyz'].sort()  # ['xyz', 123]

# Iteration
for x in [1, 2, 3]:
    print x
for i, val in enumerate([1, 2, 3]):
    print i, val
