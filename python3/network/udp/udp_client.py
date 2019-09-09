from socket import socket, AF_INET, SOCK_DGRAM

s = socket(AF_INET, SOCK_DGRAM)
s.sendto(b'', ('localhost', 20000))
resp = s.recvfrom(8192)             # (b'Wed Aug 15 20:35:08 2012', ('127.0.0.1', 20000))
print(resp[0].decode('utf-8'))
