from socket import *

s = socket(AF_INET, SOCK_DGRAM)
s.sendto(b'', ('localhost', 14000))

resp = s.recvfrom(128)
print(resp[0])
s.sendto(b'Hello', ('localhost', 15000))
resp = s.recvfrom(128)
print(resp[0].decode('utf-8'))
