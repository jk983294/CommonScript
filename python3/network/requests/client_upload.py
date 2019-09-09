import requests

# Base URL being accessed
url = 'http://httpbin.org/get'

url = 'http://httpbin.org/post'
files = {'file': ('data.csv', open('data.csv', 'rb'))}

r = requests.post(url, files=files)
print(r.text)
