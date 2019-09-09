import os
import time

# Expand the user's home directory
path1 = '~/Data/data.csv'
path = os.path.expanduser(path1)
print(path)                                                         # /home/jk/Data/data.csv
print(os.path.basename(path))                                       # data.csv
print(os.path.dirname(path))                                        # /home/jk/Data
print(os.path.splitext(path))                                       # ('/home/jk/Data/data', '.csv')
print(os.path.join('/', 'tmp', 'data', os.path.basename(path)))     # /tmp/data/data.csv
print(os.path.getsize('/etc/passwd'))                               # 2470
print(os.path.getmtime('/etc/passwd'))                              # 1513426614.8149128
print(time.ctime(os.path.getmtime('/etc/passwd')))                  # Sat Dec 16 20:16:54 2017

# test file
print(os.path.exists('/etc/passwd'))                                # True
print(os.path.exists('/etc/not_exist'))                             # False
print(os.path.isfile('/etc/passwd'))                                # True
print(os.path.isdir('/etc/passwd'))                                 # False
print(os.path.islink('/usr/bin/python'))                            # True
print(os.path.realpath('/usr/bin/python'))                          # /usr/bin/python2.7


# file open
fo = open("file_crud.py", "wb")
print("Name of the file: ", fo.name)
print("Closed or not : ", fo.closed)
print("Opening mode : ", fo.mode)
fo.close()
print("Closed or not : ", fo.closed)
