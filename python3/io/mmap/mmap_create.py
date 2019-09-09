import os
import mmap

"""
first you need to create one binary file
then mmap to that file, and then operate on that memory and close
"""


def memory_map(filename, access=mmap.ACCESS_WRITE):
    size = os.path.getsize(filename)
    fd = os.open(filename, os.O_RDWR)
    return mmap.mmap(fd, size, access=access)


size = 100
with open('data', 'wb') as f:
    f.seek(size-1)
    f.write(b'\x00')


with memory_map('data') as m:
    print(len(m))                   # 100
    print(m[0:5])                   # b'\x00\x00\x00\x00\x00'
    # Reassign a slice
    m[0:11] = b'Hello World'


# Verify that changes were made
with open('data', 'rb') as f:
    print(f.read(11))
