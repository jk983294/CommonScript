from socket import socket, AF_INET, SOCK_STREAM
import learn.network.simple_authenticate.authentication as auth

secret_key = b'peekaboo'

s = socket(AF_INET, SOCK_STREAM)
s.connect(('localhost', 20000))
auth.client_authenticate(s, secret_key)
s.send(b'Hello')
resp = s.recv(8192)
print(resp.decode('utf-8'))
