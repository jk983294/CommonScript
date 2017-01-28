#!/usr/bin/python

tuple1 = ('abcd', 786, 2.23, 'john', 70.2)
tiny_tuple = (123, 'john')

print tuple1                                                                # Prints complete tuple
print tuple1[0]                                                             # Prints first element of the tuple
print tuple1[1:3]                                                           # Prints elements starting from 2nd till 3rd
print tuple1[2:]                                                            # Prints elements starting from 3rd element
print tiny_tuple * 2                                                        # Prints tuple two times
print tuple1 + tiny_tuple                                                   # Prints concatenated tuple

print len(tuple1)                                                           # 5
print 786 in tuple1                                                         # True
print cmp((123, 'xyz'), (456, 'abc'))                                       # -1
max((456, 700, 200))                                                        # 700
min((456, 700, 200))                                                        # 200
aList = (123, 'xyz', 'zara', 'abc');
tuple((456, 700, 200))
for x in (1, 2, 3):
    print x
