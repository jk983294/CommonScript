import requests

# Base URL being accessed
url = 'http://httpbin.org/get'

# Dictionary of query parameters (if any)
payload = {
   'name1': 'value1',
   'name2': 'value2'
}

# First request
resp1 = requests.get(url, params=payload)
print(resp1.url)
print(resp1.text)

# Second requests with cookies received on first requests
resp2 = requests.get(url, params=payload, cookies=resp1.cookies)
print(resp2.url)
print(resp2.text)
