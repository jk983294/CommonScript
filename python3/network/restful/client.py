from urllib import request, parse

u = request.urlopen('http://localhost:8080/hello?name=Guido')
resp = u.read()
print(resp.decode('utf-8'))
