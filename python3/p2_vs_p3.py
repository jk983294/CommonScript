# python3 <--> python2
# print(a) <--> print a
# print(a, end='') <--> print a,
# print(a, file=sys.stderr) <--> print sys.stderr, a
# items() <--> iteritems()
# except Exception as e: <--> except TypeError, msg:
# raise TypeError(msg) <--> raise TypeError, msg
# <--> xrange(15)
# operator.le(1, 2) <--> cmp(1, 2)
# __lt__ for s1 < s2 <--> __cmp__
# zip(i, i) <--> izip(i, i)
# map(pow, range(10), itertools.repeat(2)) <--> itertools.imap(pow, range(10), itertools.repeat(2))
# itertools.filterfalse <--> itertools.ifilterfalse
# itertools.zip_longest <--> itertools.izip_longest
# 'No Exist' in dict1 <--> dict1.has_key('No Exist')
# input <--> raw_input
# from io import StringIO <--> import StringIO
# int <--> long
# urllib.request.urlopen <--> urllib2.urlopen

