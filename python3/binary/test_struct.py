#!/bin/python
import struct
from collections import namedtuple

# Type  C Type	            Python Type	        Minimum size in bytes
# x     pad byte	        no value
# c	    char	            bytes of length 1	1
# 'b'   signed char	        int	                1
# 'B'	unsigned char	    int	                1
# ?	    _Bool	            bool	            1
# 'u'	Py_UNICODE	        Unicode (wchar_t)	2
# 'h'	signed short	    int	                2
# 'H'	unsigned short	    int	                2
# 'i'	signed int	        int	                2
# 'I'	unsigned int	    int	                2
# 'l'	signed long	        int	                4
# 'L'	unsigned long	    int	                4
# 'q'	signed long long	int	                8
# 'Q'	unsigned long long	int	                8
# n	    ssize_t	            integer
# N	    size_t	            integer
# e	    	                float	            2
# 'f'	float	            float	            4
# 'd'	double	            float	            8
# s	    char[]	            bytes
# p	    char[]	            bytes
# P	    void *	            integer

a = struct.pack('hhl', 1, 2, 3)
print(a)
b = struct.unpack('hhl', a)
print(b)                                                    # (1, 2, 3)
print(struct.calcsize('hhl'))                               # 8


record = b'raymond   \x32\x12\x08\x01\x08'
name, serialNum, school, gradeLevel = struct.unpack('<10sHHb', record)
print(name, serialNum, school, gradeLevel)                  # b'raymond   ' 4658 264 8

Student = namedtuple('Student', 'name serialNum school gradeLevel')
print(Student._make(struct.unpack('<10sHHb', record)))      # Student(name=b'raymond   ', serialNum=4658, school=264, gradeLevel=8)

# padding regard of order
print(struct.pack('ci', b'*', 0x12131415))                  # b'*\x00\x00\x00\x15\x14\x13\x12'
print(struct.pack('ic', 0x12131415, b'*'))                  # b'\x15\x14\x13\x12*'
