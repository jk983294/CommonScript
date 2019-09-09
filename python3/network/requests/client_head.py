import requests

resp = requests.head('http://www.python.org/index.html')

print(resp.status_code)
print(resp.headers['content-length'])
