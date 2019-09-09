import re



# simple case
print('hello, \nworld!'.split())            # ['hello,', 'world!']
print('hello, \nworld!'.split(" "))         # ['hello,', '\nworld!']
print('hello, \nworld!'.splitlines())       # ['hello, ', 'world!']

# re case
line = 'asdf fjdk; afed, fjek,asdf, foo'
print(re.split(r'[;,\s]\s*', line))         # ['asdf', 'fjdk', 'afed', 'fjek', 'asdf', 'foo']

# print group info
print(re.split(r'(;|,|\s)\s*', line))       # ['asdf', ' ', 'fjdk', ';', 'afed', ',', 'fjek', ',', 'asdf', ',', 'foo']

# don't capture group info
print(re.split(r'(?:;|,|\s)\s*', line))     # ['asdf', 'fjdk', 'afed', 'fjek', 'asdf', 'foo']

