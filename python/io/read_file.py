# read file line by line
fo = open("foo.txt", "r+")
print file.readline()
fo.close()

# read file of all lines
with open('data.txt', 'r') as f:
    data = f.readlines()
    for line in data:
        words = line.split()
        print words