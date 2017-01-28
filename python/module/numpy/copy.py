from numpy import *

# simple assignments make no copy of array objects or of their data.
a = arange(12)
b = a                                           # no new object is created
b is a                                          # a and b are two names for the same ndarray object

# view or Shallow Copy
# view method creates a new array object that looks at the same data.
# slicing an array returns a view of it
c = a.view()
c is a                                          # False
c.base is a                                     # True, c is a view of the data owned by a
c.flags.owndata                                 # False
c.shape = 2,6                                   # a's shape doesn't change
c[0, 4] = 1234                                  # a's data changes

# Deep Copy
d = a.copy()                                    # a new array object with new data is created
d is a                                          # False
d.base is a                                     # False, d doesn't share anything with a
d[0] = 9999                                     # a's data won't change
