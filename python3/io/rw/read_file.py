# read file line by line
fo = open("foo.txt", "r+")
print(fo.readline())
fo.close()                          # must manually close if not in with block

# read file of all lines
with open('data.txt', 'rt', encoding='utf-8') as f:
    data = f.readlines()
    for line in data:
        words = line.split()
        print(words)


# read with line stripped
with open('data.txt', 'rt') as f:
    lines = (line.strip() for line in f)
    for line in lines:
        print(line)


# read with line number
def parse_data(filename):
    with open(filename, 'rt') as f:
        for lineno, line in enumerate(f, 1):
            fields = line.split()
            try:
                count = int(fields[1])
                # ...
            except ValueError as e:
                print('Line {}: Parse error: {}'.format(lineno, e))