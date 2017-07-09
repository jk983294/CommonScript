import glob
import os

# std IO
str1 = raw_input("Enter your input: ")
print "Received input is : ", str1

# input is python expression
str1 = input("Enter your input: ")                                  # [x*5 for x in range(2,10,2)]
print "Received input is : ", str1                                  # [10, 20, 30, 40]

# os
os.rename("test1.txt", "test2.txt")
os.remove("text2.txt")
os.rmdir("/tmp/test")
os.mkdir("newdir")
os.getcwd()                                                         # get the current directory
os.chdir("newdir")                                                  # change the current directory
os.makedirs('/tmp/a/b/c')                                           # makes all intermediate-level directories needed

# remove all files under one dir, but leave dir un-touch, shutil.rmtree will remove dir itself
data_files = glob.glob('/tmp/test/*')
for data_file in data_files:
    os.remove(data_file)

# file open
fo = open("foo.txt", "wb")
print "Name of the file: ", fo.name
print "Closed or not : ", fo.closed
print "Opening mode : ", fo.mode
print "Softspace flag : ", fo.softspace

# x mode, if file exist, then skip it, otherwise write it with w mode
with open('somefile', 'xt') as f:
    f.write('Hello\n')
