#!/bin/python3
import array

# Type  C Type	            Python Type	        Minimum size in bytes
# 'b'   signed char	        int	                1
# 'B'	unsigned char	    int	                1
# 'u'	Py_UNICODE	        Unicode (wchar_t)	2
# 'h'	signed short	    int	                2
# 'H'	unsigned short	    int	                2
# 'i'	signed int	        int	                2
# 'I'	unsigned int	    int	                2
# 'l'	signed long	        int	                4
# 'L'	unsigned long	    int	                4
# 'q'	signed long long	int	                8
# 'Q'	unsigned long long	int	                8
# 'f'	float	            float	            4
# 'd'	double	            float	            8

print(array.array('l'))
print(array.array('b', b'hello world'))
print(array.array('l', [1, 2, 3, 4, 5]))
print(array.array('d', [1.0, 2.0, 3.14]))

