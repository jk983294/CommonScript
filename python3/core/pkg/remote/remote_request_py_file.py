from urllib.request import urlopen

u = urlopen('http://localhost:15000/fib.py')
data = u.read().decode('utf-8')
print(data)
