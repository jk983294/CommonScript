from multiprocessing.connection import Client
import pickle


class RPCProxy:
    def __init__(self, connection):
        self._connection = connection

    def __getattr__(self, name):
        def do_rpc(*args, **kwargs):
            self._connection.send(pickle.dumps((name, args, kwargs)))
            result = pickle.loads(self._connection.recv())
            if isinstance(result, Exception):
                raise result
            return result
        return do_rpc


c = Client(('localhost', 17000), authkey=b'peekaboo')
proxy = RPCProxy(c)
print(proxy.add(2, 3))          # 5
print(proxy.sub(2, 3))          # -1
# print(proxy.sub([1, 2], 4))   # exception
