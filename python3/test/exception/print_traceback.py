import traceback
import sys


def func(n):
    return n + 10


try:
    func('Hello')
except Exception as e:
    print('**** AN ERROR OCCURRED ****')
    traceback.print_exc(file=sys.stderr)
