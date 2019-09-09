import requests

resp = requests.get('http://pypi.python.org/pypi?:action=login',
                    auth=('user', 'password'))

print(resp.status_code)
print(resp.headers['content-length'])
