#!/bin/python
# coding: utf-8

# encode
x=u'\xe4\xf6\xfc'
# print x                                               # failed: UnicodeEncodeError: 'ascii' codec can't encode characters
print x.encode("utf-8")

# decode
x='\xc3\xa4\xc3\xb6\xc3\xbc'
x.decode("utf8")
