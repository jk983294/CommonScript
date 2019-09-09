from functools import partial

RECORD_SIZE = 32

with open('somefile.data', 'rb') as f:
    records = iter(partial(f.read, RECORD_SIZE), b'')
    for r in records:
        pass


# another way
buf = bytearray(RECORD_SIZE)    # always reuse this buffer
with open('somefile', 'rb') as f:
    while True:
        n = f.readinto(buf)
        if n < RECORD_SIZE:
            break
        # Use the contents of buf
        pass
