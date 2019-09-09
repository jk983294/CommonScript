#!/bin/python3
import array
import struct

v = memoryview(b'abcefg')
print(v[1])                                     # 98
print(v[-1])                                    # 103
print(bytes(v[1:4]))                            # b'bce'
print(v.ndim, len(v))                           # 1 6

a = array.array('l', [-11111111, 22222222, -33333333, 44444444])
m = memoryview(a)
print(m.ndim, len(m))                           # 1 4
print(m[0])                                     # -11111111
print(m[::2].tolist())                          # [-11111111, -33333333]

# modify
data = bytearray(b'abcefg')
v = memoryview(data)
print(v.readonly)                               # False
v[0] = ord(b'z')                                # bytearray(b'zbcefg')
v[1:4] = b'123'                                 # bytearray(b'z123fg')

# convert back to bytes
print(memoryview(b"abc").tobytes())             # b'abc'

# convert back to array
print(memoryview(array.array('d', [1.1, 2.2, 3.3])).tolist())   # [1.1, 2.2, 3.3]

# cast
x = memoryview(array.array('l', [1, 2, 3]))
print(x.format)                                 # 'l'
print(x.itemsize)                               # 4
print(len(x))                                   # 3
print(x.nbytes)                                 # 12
# cast to unsigned char
y = x.cast('B')
print(y.format)                                 # 'B'
print(y.itemsize)                               # 1
print(len(y))                                   # 12
print(y.nbytes)                                 # 12

# cast 1D bytes to 3D ints
buf = struct.pack("i"*12, *list(range(12)))
x = memoryview(buf)
y = x.cast('i', shape=[2, 2, 3])
print(y.tolist())                               # [[[0, 1, 2], [3, 4, 5]], [[6, 7, 8], [9, 10, 11]]]
