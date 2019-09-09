from socket import socket, AF_INET, SOCK_STREAM
import learn.network.simple_authenticate.authentication as auth


secret_key = b'peekaboo'


def echo_handler(address, client_sock):
    if not auth.server_authenticate(client_sock, secret_key):
        client_sock.close()
        return
    print('Got connection from {}'.format(address))
    while True:
        msg = client_sock.recv(8192)
        if not msg:
            break
        client_sock.sendall(msg)
    client_sock.close()


def echo_server(address, backlog=5):
    sock = socket(AF_INET, SOCK_STREAM)
    sock.bind(address)
    sock.listen(backlog)
    while True:
        client_sock, client_addr = sock.accept()
        echo_handler(client_addr, client_sock)


if __name__ == '__main__':
    echo_server(('', 20000))
