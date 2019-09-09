from io import StringIO

"""
string io can be used as unit test for file
"""

input1 = StringIO('1\n53\n42')
print(input1.readline())            # "1\n"
print(input1.readline())            # "53\n"
print(input1.readline())            # "42"
input1.close()
