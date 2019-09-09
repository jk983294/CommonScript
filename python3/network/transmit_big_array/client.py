from socket import *
import numpy
import learn.network.transmit_big_array.zerocopy as zerocopy

c = socket(AF_INET, SOCK_STREAM)
c.connect(('localhost', 25000))
a = numpy.zeros(shape=50000000, dtype=float)
print(a[0:10])
zerocopy.recv_into(a, c)
print(a[0:10])
