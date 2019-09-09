import re

# built-in
print('88example88'.strip('8'))                                     # 'example'
print('88example88'.rstrip('8'))                                    # '88example'
print('88example88'.lstrip('8'))                                    # 'example88'

# re module
s = ' hello     world \n'
print(re.sub('\s+', ' ', s).strip())                                # 'hello world'
