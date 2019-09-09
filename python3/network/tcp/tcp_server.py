import socket
from socketserver import BaseRequestHandler, TCPServer
from threading import Thread


class EchoHandler(BaseRequestHandler):
    def handle(self):
        print('Got connection from', self.client_address)
        while True:
            msg = self.request.recv(8192)
            if not msg:
                break
            self.request.send(msg)


if __name__ == '__main__':
    NWORKERS = 16
    TCPServer.allow_reuse_address = True
    serv = TCPServer(('', 20000), EchoHandler)

    # use thread pool to handle client request
    for n in range(NWORKERS):
        t = Thread(target=serv.serve_forever)
        t.daemon = True
        t.start()
    serv.serve_forever()
