#!/usr/bin/python

# string
str1 = 'Hello World!'
# Prints complete string
print str1
# Prints first character of the string
print str1[0]
# Prints characters starting from 3rd to 5th
print str1[2:5]
# Prints string starting from 3rd character
print str1[2:]
# remove first and last character
print str1[1:-1]
# Prints string two times
print str1 * 2
# Prints concatenated string
print str1 + "TEST"
print 'H' in str1

# raw string
print 'C:\\nowhere'
print r'C:\\nowhere'

# Unicode string
print u'Hello, world!'

# formatting
print "%s  %d" % ('Zara', 21)
fields = {"firstName": "John", "surName": "Smith"}
print "Your are %(firstName)s %(surName)s" % fields

# built-in
print len('hello, world!')                                      # 13
print max('hello, world!')                                      # 'w'
print min('hello, world!')                                      # ' '
print 'hello, world!'.count('ll')                               # 1

print 'hello, world!'.find('ll')                                # 2
# 2 raises an exception if no such index exists
print 'hello, world!'.index('ll')
print 'hello, world!'.rfind('o')                                # 8
# 8 raises an exception if no such index exists
print 'hello, world!'.rindex('o')

# '---hello, world!----'
print 'hello, world!'.center(20, '-')
# '0000000hello, world!'
print 'hello, world!'.zfill(20)
# 'hello,  world!'
print 'hello, \tworld!'.expandtabs(4)
print 'hello, WORLD!'.swapcase()                                # 'HELLO, world!'
# '----- hello, world!'
print ' hello, world! '.rjust(20, '-')
# ' hello, world! -----'
print ' hello, world! '.ljust(20, '-')
print '88example88'.strip('8')                                  # 'example'
print '88example88'.rstrip('8')                                 # '88example'
print '88example88'.lstrip('8')                                 # 'example88'

# join array data
print '-'.join(("a", "b", "c"))                                 # 'a-b-c'
# 'HELLO, world!'
print 'hello, world!'.replace("hello", "HELLO")
# ['hello,', 'world!']
print 'hello, \nworld!'.split()
# ['hello,', '\nworld!']
print 'hello, \nworld!'.split(" ")
# ['hello, ', 'world!']
print 'hello, \nworld!'.splitlines()

# decodes the string using the codec registered for encoding
print 'hello, world!'.decode(encoding='UTF-8', errors='strict')
# an encoded version of the string
print 'hello, world!'.encode(encoding='UTF-8', errors='strict')

print 'ABC'.lower()
print 'hello, world!'.islower()
print 'abc'.upper()
print 'ABC'.isupper()

print 'hello, world!'.isalnum()                                 # False
print 'helloworld'.isalpha()                                    # True
print '42'.isdigit()                                            # True
print u'42'.isdecimal()                                         # True
print u'42.0'.isnumeric()                                       # False
print '   '.isspace()                                           # True
print 'This Is Title'.istitle()                                 # True
print 'hello, world!'.endswith('!')                             # True
print 'hello, world!'.startswith("hello")                       # True

print 'hello, world!'.capitalize()                              # 'Hello, world!'
print 'hello, world!'.title()                                   # 'Hello, World!'
