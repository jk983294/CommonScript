import sys
import urllib2
from contextlib import closing

class Silence(object):
    def __enter__(self):                            # called when with statement is executed, "as x" will be the value what __enter__ returns
        pass
    def __exit__(self, type, value, traceback):     # Called when with block ends with or without exception, Receives the exception's type, value and traceback, If returns True, exception will be suppressed
        if type:
            sys.stdout.write(str(value)+"\n")
        return True

with Silence():
    6/0

# closing calls the close() method on the object specified when exiting
with closing(urllib2.urlopen('http://www.python.org')) as page:
    for line in page:
        print line
