from socket import *

sock = socket(AF_INET, SOCK_DGRAM)
for x in range(40):
    sock.sendto(str(x).encode('utf-8'), ('localhost', 16000))
    resp = sock.recvfrom(8192)
    print(resp[0])
