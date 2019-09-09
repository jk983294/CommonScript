#!/bin/python3
# coding: utf-8

# encode
x = u'\xe4\xf6\xfc'
# print(x                           # failed: UnicodeEncodeError: 'ascii' codec can't encode characters
print(x.encode("utf-8"))

# decode
x=b'\xc3\xa4\xc3\xb6\xc3\xbc'
print(x.decode("utf8"))
