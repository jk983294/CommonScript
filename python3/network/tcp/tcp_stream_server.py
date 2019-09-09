import socket
from socketserver import StreamRequestHandler, TCPServer


class EchoHandler(StreamRequestHandler):
    # Optional settings (defaults shown)
    timeout = 5  # Timeout on all socket operations
    rbufsize = -1  # Read buffer size
    wbufsize = 0  # Write buffer size
    disable_nagle_algorithm = False  # Sets TCP_NODELAY socket option

    def handle(self):
        print('Got connection from', self.client_address)
        try:
            # self.rfile is a file-like object for reading
            for line in self.rfile:
                # self.wfile is a file-like object for writing
                self.wfile.write(line)
        except socket.timeout:
            print('Timed out!')


if __name__ == '__main__':
    serv = TCPServer(('', 20000), EchoHandler)
    serv.serve_forever()
