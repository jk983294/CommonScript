def bad_filename(filename):
    return repr(filename)[1:-1]


filename = 'a.txt'

try:
    print(filename)
except UnicodeEncodeError:
    print(bad_filename(filename))
