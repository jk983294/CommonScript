from queue import Queue
from threading import Thread
import time

'''
Queue is thread safe
'''

# Object that signals shutdown
_sentinel = -1


# A thread that produces data
def producer(out_q):
    data = 0
    while True:
        # Produce some data
        if data == 10:
            out_q.put(-1)           # signal termination
            break

        data += 1
        out_q.put(data)
        print("produce data", data)
        time.sleep(1)


# A thread that consumes data
def consumer(in_q):
    while True:
        data = in_q.get()

        # Check for termination
        if data is _sentinel:
            in_q.put(_sentinel)     # put back so that other consumer can see this sentinel to terminate
            break

        # Process the data
        print("get data", data)


# Create the shared queue and launch both threads
q = Queue()
t1 = Thread(target=consumer, args=(q,))
t2 = Thread(target=producer, args=(q,))
t1.start()
t2.start()
