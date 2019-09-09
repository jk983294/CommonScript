str1 = 'http://www.baidu.com'

print(str1.endswith(('com', 'net')))                            # True
print(str1.startswith(('http', 'https')))                       # True

print(str1.endswith('com'))                                     # True
print(str1.startswith('http'))                                  # True
