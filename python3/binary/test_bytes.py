#!/bin/python3

# bytes is immutable

b1 = b'still allows embedded "double" quotes'
b2 = b"still allows embedded 'single' quotes"
b3 = b'''3 single quotes''', b"""3 double quotes"""
b4 = bytes(5)                                       # b'\x00\x00\x00\x00\x00'
b5 = bytes(range(5))                                # b'\x00\x01\x02\x03\x04'
bCopy = bytes(b4)                                   # b'\x00\x00\x00\x00\x00'
bHex = bytes.fromhex('2Ef0 F1f2 ')                  # b'.\xf0\xf1\xf2'
strHex = b'\xf0\xf1\xf2'.hex()                      # f0f1f2

print(list(b5))                                     # [0, 1, 2, 3, 4]
print(list(b5[0:2]))                                # [0, 1]
