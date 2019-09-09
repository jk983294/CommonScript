#!/bin/python3

# bytes is immutable

a = b"hello world"
print(a.replace(b"h", b"f"))                        # b'fello world'
print(a.count(b"o"))                                # 2
print(a.decode(encoding="utf-8", errors="strict"))  # 'hello world'
print(a.endswith(b"world"))                         # True
print(a.startswith(b"world"))                       # False
print(a.find(b"world"))                             # 6
print(b'-'.join([b"hello", b"world"]))              # b'hello-world'
print(a.partition(b' '))                            # (b'hello', b' ', b'world')
print(a.replace(b'hello', b'HELLO'))                # b'HELLO world'
print(b'1,2,3'.split(b','))                         # [b'1', b'2', b'3']
print(b'   spacious   '.strip())                    # b'spacious'
print(b'01\t012\t0123\t01234'.expandtabs(4))        # b'01  012 0123    01234'
print(b'1234'.isdigit())                            # True
print(b'ab c\n\nde fg\rkl\r\n'.splitlines())        # [b'ab c', b'', b'de fg', b'kl']
print(b"42".zfill(5))                               # b'00042'

print(b'%(var1)s %(var2)03d' % {b'var1': b"hello", b"var2": 2})         # b'hello 002'

