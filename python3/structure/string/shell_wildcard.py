from fnmatch import fnmatch

"""
Unix Shell wildcard(like *.py, Dat[0-9]*.csv) to match text
"""


print(fnmatch('foo.txt', '*.txt'))                              # True
print(fnmatch('foo.txt', '?oo.txt'))                            # True
print(fnmatch('Dat45.csv', 'Dat[0-9]*'))                        # True
names = ['Dat1.csv', 'Dat2.csv', 'config.ini', 'foo.py']
print([name for name in names if fnmatch(name, 'Dat*.csv')])    # ['Dat1.csv', 'Dat2.csv']




