from urllib import request, parse

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

# Encode the query string
querystring = parse.urlencode(parms)

# Make a GET request and read the response
req = request.Request(url, querystring.encode('utf-8'), headers=headers)
u = request.urlopen(req)
resp = u.read()
print(resp.decode('utf-8'))
