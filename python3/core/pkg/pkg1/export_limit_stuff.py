def spam():
    pass


def grok():
    pass


def no_exported():
    pass


blah = 42

"""
below only export 'spam' and 'grok'
when using 'from module import *', only 'spam' and 'grok' get import
"""
__all__ = ['spam', 'grok']
