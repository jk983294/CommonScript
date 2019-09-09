import os

x = 1234
print(bin(x))                       # '0b10011010010'
print(oct(x))                       # '0o2322'
print(hex(x))                       # '0x4d2'

print(format(x, 'b'))               # '10011010010'
print(format(x, 'o'))               # '2322'
print(format(x, 'x'))               # '4d2'

# revert back
print(int('4d2', 16))               # 1234
print(int('10011010010', 2))        # 1234

# unsigned 32 bit value
x = -1234
print(format(2**32 + x, 'b'))       # '11111111111111111111101100101110'
print(format(2**32 + x, 'x'))       # 'fffffb2e'

# oct prefix is 0o
os.chmod('script.py', 0o755)
