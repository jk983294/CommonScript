from numpy import *

y = array([2., 4., 6., 8.])
y.tofile("myfile.dat")                                              # binary format
print(fromfile('myfile.dat', dtype=float))                          # array([ 2., 4., 6., 8.])

y.tofile("myfile.txt", sep='\n', format="%e")                       # ascii format, one column, exponential notation
print(fromfile('myfile.txt', dtype=float, sep='\n'))