from multiprocessing.connection import Client

"""
all data which can be pickled, then it can be sent
"""

c = Client(('localhost', 25000), authkey=b'peekaboo')
c.send('hello')
resp = c.recv()
print(resp)                 # 'hello'
c.send(42)
resp = c.recv()
print(resp)                 # 42
c.send([1, 2, 3, 4, 5])
resp = c.recv()
print(resp)                 # [1, 2, 3, 4, 5]
