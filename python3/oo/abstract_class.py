from abc import ABCMeta, abstractmethod
import collections.abc


class IStream(metaclass=ABCMeta):
    @abstractmethod
    def read(self, maxbytes=-1):
        pass

    @abstractmethod
    def write(self, data):
        pass


class SocketStream(IStream):
    def read(self, maxbytes=-1):
        pass

    def write(self, data):
        pass


def serialize(obj, stream):
    if not isinstance(stream, IStream):
        raise TypeError('Expected an IStream')
    pass


# below all are interfaces
print(isinstance([], collections.abc.Sequence))
print(isinstance([], collections.abc.Iterable))
print(isinstance([], collections.abc.Sized))
print(isinstance({}, collections.abc.Mapping))
