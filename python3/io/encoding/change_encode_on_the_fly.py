import io

"""
.detach() to remove encode layer
then equip with new encode layer
"""


f = open('sample.txt', 'w')
b = f.detach()
f = io.TextIOWrapper(b, encoding='latin-1')
