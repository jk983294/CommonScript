import os

# std IO
str = raw_input("Enter your input: ")
print "Received input is : ", str

# input is python expression
str = input("Enter your input: ")                                   # [x*5 for x in range(2,10,2)]
print "Received input is : ", str                                   # [10, 20, 30, 40]



# os
os.rename( "test1.txt", "test2.txt" )
os.remove("text2.txt")
os.rmdir( "/tmp/test"  )
os.mkdir("newdir")
os.getcwd()                                                         # get the current directory
os.chdir("newdir")                                                  # change the current directory


# file open
fo = open("foo.txt", "wb")
print "Name of the file: ", fo.name
print "Closed or not : ", fo.closed
print "Opening mode : ", fo.mode
print "Softspace flag : ", fo.softspace
