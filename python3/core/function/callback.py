"""
let callback access outside state
either use class or closure to keep state
"""


def apply_async(func, args, *, callback):
    # Compute the result
    result = func(*args)

    # Invoke the callback with the result
    callback(result)


class ResultHandler:
    def __init__(self):
        self.sequence = 0

    def handler(self, result):
        self.sequence += 1
        print('[{}] Got: {}'.format(self.sequence, result))


def print_result(result):
    print('Got:', result)


def add(x, y):
    return x + y


# callback without outside state
apply_async(add, (2, 3), callback=print_result)
apply_async(add, ('hello', 'world'), callback=print_result)

# callback with class state
r = ResultHandler()
apply_async(add, (2, 3), callback=r.handler)
apply_async(add, ('hello', 'world'), callback=r.handler)


def make_handler():
    sequence = 0

    def handler(result):
        nonlocal sequence           # will change in future
        sequence += 1
        print('[{}] Got: {}'.format(sequence, result))
    return handler


# callback with closure state
handler = make_handler()
apply_async(add, (2, 3), callback=handler)
apply_async(add, ('hello', 'world'), callback=handler)


def make_handler_coroutine():
    sequence = 0
    while True:
        result = yield
        sequence += 1
        print('[{}] Got: {}'.format(sequence, result))


# callback with co-routine state
handler = make_handler_coroutine()
next(handler)
apply_async(add, (2, 3), callback=handler.send)
apply_async(add, ('hello', 'world'), callback=handler.send)
