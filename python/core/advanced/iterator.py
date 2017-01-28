import itertools

# Iterator is an object which has next() method.
# iterator of an object is returned by its __iter__() method.
# Iterators can be converted to list by list() constructor
# Built-in iterators: list, dictionary, string, xrange(start, end, step), file()


class Fibonacci(object):
    def __init__(self):
        self.a = 0
        self.b = 1
        self.state = 0

    def __iter__(self):
        return self

    def next(self):
        if self.state < 2:
            self.state += 1
            return self.state-1
        else:
            self.a, self.b = self.b, self.a + self.b
            return self.b

for i in Fibonacci():
    if i > 100:
        break
    print i


def display_iterator_content(o, stop_value=None):
    for i in o:
        if stop_value is not None and i > stop_value:
            break
        print i,
    print

L = [i * i for i in range(5)]
# iterator with index
for index, data in enumerate(L, 1):
    print(index, ':',  data)

# iterator reverse order
for item in reversed(L):
    print(item)

# itertools module
display_iterator_content(itertools.chain('ABC', 'DEF'))                                     # A B C D E F
display_iterator_content(itertools.chain.from_iterable(['ABC', 'DEF']))                     # A B C D E F
display_iterator_content(itertools.count(10), 15)                                           # 10 11 12 13 14 15
display_iterator_content(itertools.count(2.5, 0.5), 5)                                      # 2.5 3.0 3.5 4.0 4.5 5.0
display_iterator_content(itertools.cycle('ABCD'), 'C')                                      # A B C D A B C D ...
display_iterator_content(itertools.repeat(10, 3))                                           # 10 10 10
list(itertools.imap(pow, xrange(10), itertools.repeat(2)))                                  # common use for repeat is to supply a stream of constant values to imap or zip, [0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
display_iterator_content(itertools.compress('ABCDEF', [1,0,1,0,1,1]))                       # A C E F
display_iterator_content(itertools.dropwhile(lambda x: x<5, [1,4,6,4,1]))                   # 6 4 1
display_iterator_content(itertools.takewhile(lambda x: x<5, [1,4,6,4,1]))                   # 1 4
display_iterator_content(itertools.ifilter(lambda x: x%2, range(10)))                       # 1 3 5 7 9
display_iterator_content(itertools.ifilterfalse(lambda x: x%2, range(10)))                  # 0 2 4 6 8
display_iterator_content(itertools.imap(pow, (2,2,2), (2,3,4)))                             # 4 8 16
display_iterator_content(itertools.starmap(pow, [(2,2), (2,3), (2,4)]))                     # 4 8 16
display_iterator_content(itertools.islice('ABCDEFG', 2))                                    # A B
display_iterator_content(itertools.islice('ABCDEFG', 2, 4))                                 # C D
display_iterator_content(itertools.islice('ABCDEFG', 2, None))                              # C D E F G
display_iterator_content(itertools.islice('ABCDEFG', 0, None, 2))                           # A C E G
display_iterator_content(itertools.izip('ABCD', 'xy'))                                      # ('A', 'x') ('B', 'y')
display_iterator_content(itertools.izip_longest('ABCD', 'xy', fillvalue='-'))               # ('A', 'x') ('B', 'y') ('C', '-') ('D', '-')
display_iterator_content(itertools.product('ABCD', 'xy'))                                   # Ax Ay Bx By Cx Cy Dx Dy
display_iterator_content(itertools.product('ABCD', repeat=2))                               # AA AB AC AD BA BB BC BD CA CB CC CD DA DB DC DD
display_iterator_content(itertools.permutations('ABC', 2))                                  # ('A', 'B') ('A', 'C') ('B', 'A') ('B', 'C') ('C', 'A') ('C', 'B')
display_iterator_content(itertools.permutations(range(3)))                                  # 012 021 102 120 201 210
display_iterator_content(itertools.combinations('ABC', 2))                                  # ('A', 'B') ('A', 'C') ('B', 'C')
display_iterator_content(itertools.combinations_with_replacement('ABC', 2))                 # ('A', 'A') ('A', 'B') ('A', 'C') ('B', 'B') ('B', 'C') ('C', 'C')


# test if one object is an iterator
a = [1, 2]
li = a.__iter__()
li.next()                                           # 1
li.next()                                           # 2
li.next()                                           # StopIteration Exception
