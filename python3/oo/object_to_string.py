class Pair:
    _formats = {
        'xy': '{d.x}-{d.y}',
        'yx': '{d.y}/{d.x}'
    }

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __repr__(self):
        # when type object in console, it use __repr__ to show the object
        return 'Pair({0.x!r}, {0.y!r})'.format(self)

    def __str__(self):
        # when use str() or print(), it use __str__
        # {0.x} means {self.x}
        # !r means use __repr__()
        # !s means use __str__()
        return '({0.x!s}, {0.y!s})'.format(self)

    def __format__(self, code):
        if code == '':
            code = 'xy'
        fmt = self._formats[code]
        return fmt.format(d=self)


p = Pair(3, 4)
print('p is {0!r}'.format(p))           # p is Pair(3, 4)
print('p is {0}'.format(p))             # p is 3-4
print('p is {:xy}'.format(p))           # p is 3-4
print('p is {:yx}'.format(p))           # p is 4/3
