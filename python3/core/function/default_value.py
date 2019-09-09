"""
default value should be immutable data like boolean/none/number/string
should no be [], {}, below example show the caveat
the default value for array/dict should be None
"""


def spam_bad(a, b=[]):
    print(b)
    return b


x = spam_bad(1)
x.append(99)
x.append('Yow!')
spam_bad(1)                             # [99, 'Yow!'] Modified list gets returned!


def spam_good(a, b=None):
    if b is None:       # do not use 'not b', many case will evaluate to false
        b = []
    print(b)
    return b
