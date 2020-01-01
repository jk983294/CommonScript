import numpy as np

b = np.arange(3)
booleans = np.array([True, False, True])

print(booleans.all())                                       # False
print(all(booleans))                                        # False
print(all(b > 0))                                           # False
print(np.alltrue(booleans))                                 # False
print(np.sometrue(booleans))                                # True
print(np.alltrue(b > 0))                                    # False
print(booleans.any())                                       # True
print(any(booleans))                                        # True
print((b >= 1).any())                                       # True
