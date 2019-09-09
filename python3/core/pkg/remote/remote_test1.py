import imp
import urllib.request
import sys


def load_module(url):
    u = urllib.request.urlopen(url)
    source = u.read().decode('utf-8')
    mod = sys.modules.setdefault(url, imp.new_module(url))
    code = compile(source, url, 'exec')
    mod.__file__ = url
    mod.__package__ = ''
    exec(code, mod.__dict__)
    return mod


fib = load_module('http://localhost:15000/fib.py')
fib.fib(10)
spam = load_module('http://localhost:15000/spam.py')
spam.hello('Guido')
