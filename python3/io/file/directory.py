import os

names = os.listdir('.')
print(names)                # ['glob_example.py', 'directory.py', 'file_query.py', ...]

# get all regular files
names = [name for name in os.listdir('somedir') if os.path.isfile(os.path.join('somedir', name))]

# get all dirs
dirnames = [name for name in os.listdir('somedir') if os.path.isdir(os.path.join('somedir', name))]

# get all py files
pyfiles = [name for name in os.listdir('somedir') if name.endswith('.py')]