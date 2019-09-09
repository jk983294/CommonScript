import sys
import csv

"""
general rule:
function faster than global code
local variable faster than global variable
    'sqrt = math.sqrt sqrt(9)' > 'math.sqrt(9)'
'from math import sqrt  sqrt(9)' > 'from math  math.sqrt(9)'
dict literal faster than dict
    {'name' : 'AAPL'}   >  dict(name='AAPL')
"""


class A(object):
    def my_method(self):
        return "something"

a = A()
print(a.my_method())
# how many lookup happen here:
# step 1: globals()
# step 2: locals()
# step 3: obj.__dict__

# remove global code, change it to function instead
with open(sys.argv[1]) as f:
    for row in csv.reader(f):
        pass


# local function gives better performance than code above
def main(filename):
    with open(filename) as f:
         for row in csv.reader(f):
             pass

main(sys.argv[1])
