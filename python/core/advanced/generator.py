# generator is a special function which uses yield statement
# yield statement can only be used in a function/method
# generators is memory efficient, only the current loop variable will be created


def fibonacci():
    a = 0
    b = 1
    yield a
    yield b
    while True:
        a, b = b, a + b
        yield b

for i in fibonacci():
    if i>100:
        break
    print i


# more feature
def my_gen():
    i = 0
    while True:
        try:
            received = yield i
        except GeneratorExit:
            print "Closing"
            return
        print "Generator received: %r" % received
        i += 1

my = my_gen() # initialize
print "Caller received: %r" % my.next()                         # start the generator, get the next value
print "Caller received: %r" % my.send("Hello world")            # sends the value back to the generator
my.close()                                                      # raises GeneratorExit exception in the generator
