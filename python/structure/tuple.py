#!/usr/bin/python

tuple = ( 'abcd', 786 , 2.23, 'john', 70.2  )
tinytuple = (123, 'john')

print tuple                                                                     # Prints complete tuple
print tuple[0]                                                                  # Prints first element of the tuple
print tuple[1:3]                                                                # Prints elements starting from 2nd till 3rd
print tuple[2:]                                                                 # Prints elements starting from 3rd element
print tinytuple * 2                                                             # Prints tuple two times
print tuple + tinytuple                                                         # Prints concatenated tuple

print len(tuple)                                                                # 5
786 in tuple                                                                    # True
print cmp((123, 'xyz'), (456, 'abc'))                                           # -1
max((456, 700, 200))                                                            # 700
min((456, 700, 200))                                                            # 200
aList = (123, 'xyz', 'zara', 'abc');
tuple((456, 700, 200))
for x in (1, 2, 3):
    print x
