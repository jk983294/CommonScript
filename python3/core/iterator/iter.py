import sys

"""
io with iter to replace while loop
"""

f = open('/etc/passwd')
for chunk in iter(lambda: f.read(10), ''):
    n = sys.stdout.write(chunk)

CHUNK_SIZE = 512

def reader(s):
    for chunk in iter(lambda: s.recv(CHUNK_SIZE), b''):
        pass
        # process_data(data)
