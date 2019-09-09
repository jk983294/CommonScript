#!/bin/python3

# bytearray objects are a mutable counterpart to bytes objects

ba1 = bytearray()                                   # bytearray(b'')
ba2 = bytearray(5)                                  # bytearray(b'\x00\x00\x00\x00\x00')
ba3 = bytearray(range(5))                           # bytearray(b'\x00\x01\x02\x03\x04')
ba4 = bytearray(b'hello world!')                    # bytearray(b'hello world!')
bHex = bytearray.fromhex('2Ef0 F1f2 ')              # bytearray(b'.\xf0\xf1\xf2')
strHex = bytearray(b'\xf0\xf1\xf2').hex()           # f0f1f2

print(strHex)
