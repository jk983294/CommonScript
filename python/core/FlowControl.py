#!/usr/bin/python

# if condition
if var == 200:
   print "1 - Got a true expression value"
elif var == 150:
   print "2 - Got a true expression value"
else:
   print "3 - Got a false expression value"

# while loop
count = 0
while count < 5:
   print count, " is  less than 5"
   count = count + 1
else:
   print count, " is not less than 5"


# for loop
fruits = ['banana', 'apple',  'mango']
for fruit in fruits:
   print 'Current fruit :', fruit

for index in range(len(fruits)):
   print 'Current fruit :', fruits[index]

# walking through multi-dimensional lists
for x, y in [[1,2], [3,4], [5,6]]:
    print x, y

# pass statement, when a statement is required syntactically but you do not want any command or code to execute
if a > 5:
    pass
print "this line is always executed"
class EmptyClass:
    pass