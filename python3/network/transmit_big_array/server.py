from socket import *
import numpy
import learn.network.transmit_big_array.zerocopy as zerocopy

s = socket(AF_INET, SOCK_STREAM)
s.bind(('', 25000))
s.listen(1)
c, a = s.accept()

a = numpy.arange(0.0, 50000000.0)
zerocopy.send_from(a, c)

