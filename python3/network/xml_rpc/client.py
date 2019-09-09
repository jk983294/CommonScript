from xmlrpc.client import ServerProxy

s = ServerProxy('http://localhost:15000', allow_none=True)
s.set('foo', 'bar')
s.set('spam', [1, 2, 3])
print(s.keys())             # ['spam', 'foo']
print(s.get('foo'))         # 'bar'
print(s.get('spam'))        # [1, 2, 3]
s.delete('spam')
print(s.exists('spam'))     # False


# object test
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y


p = Point(2, 3)
s.set('foo', p)             # only its dict get passed to server and retrieved
print(s.get('foo'))         # {'x': 2, 'y': 3}

# binary test
s.set('foo', b'Hello World')
binaryObj = s.get('foo')
print(binaryObj.data)       # b'Hello World'

