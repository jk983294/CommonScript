import fileinput

# example: cat cat.py | python cat.py
# loop through all the lines in the input specified as file names given in command-line arguments,
# or the standard input if no arguments are provided

for line in fileinput.input():
    print line
