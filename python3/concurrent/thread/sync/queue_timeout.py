from queue import Queue
import queue
from threading import Thread
import time


# A thread that produces data
def producer(out_q):
    data = 0
    while True:
        # Produce some data
        data += 1
        try:
            out_q.put(data, block=False)
            print("produce data", data)
        except queue.Full:
            print('warning queued item %r discarded!' % data)
        time.sleep(1)


# A thread that consumes data
def consumer(in_q):
    while True:
        time.sleep(10)
        for i in range(10):
            # Get some data
            data = in_q.get()
            # Process the data
            print("get data", data)


# Create the shared queue and launch both threads
q = Queue(maxsize=8)
t1 = Thread(target=consumer, args=(q,))
t2 = Thread(target=producer, args=(q,))
t1.start()
t2.start()
