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

    def __next__(self):
        if self.state < 2:
            self.state += 1
            return self.state-1
        else:
            self.a, self.b = self.b, self.a + self.b
            return self.b

    def next(self):
        return self.__next__()


for i in Fibonacci():
    if i > 100:
        break
    print(i)
