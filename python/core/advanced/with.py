# -*- coding: utf-8 -*-
import sys
import urllib2
from contextlib import closing


class silence(object):
    # called when with statement is executed, "as x" will be the value what __enter__ returns
    def __enter__(self):
        pass

    # Called when with block ends with or without exception, Receives the exception's type, value and traceback,
    # If returns True, exception will be suppressed
    def __exit__(self, type, value, traceback):
        if type:
            sys.stdout.write(str(value)+"\n")
        return True

with silence():
    6/0

# closing calls the close() method on the object specified when exiting
with closing(urllib2.urlopen('http://www.python.org')) as page:
    for line in page:
        print line
