import requests

# Base URL being accessed
url = 'http://httpbin.org/post'

# Dictionary of query parameters (if any)
parms = {
   'name1': 'value1',
   'name2': 'value2'
}

# Extra headers
headers = {
    'User-agent': 'none/ofyourbusiness',
    'Spam': 'Eggs'
}

resp = requests.post(url, data=parms, headers=headers)

print(resp.content)         # binary data
print(resp.text)            # decoded data
print(resp.json)            # decoded json data
