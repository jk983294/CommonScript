import heapq
import threading
from threading import Thread
import time
import random


class PriorityQueue:
    def __init__(self):
        self._queue = []
        self._count = 0
        self._cv = threading.Condition()

    def put(self, item, priority):
        with self._cv:
            heapq.heappush(self._queue, (-priority, self._count, item))
            self._count += 1
            self._cv.notify()

    def get(self):
        with self._cv:
            while len(self._queue) == 0:
                self._cv.wait()
            return heapq.heappop(self._queue)[-1]


batch = 10


# A thread that produces data
def producer(out_q):
    data = 0
    while True:
        for n in range(batch):
            # Produce some data
            data += 1
            priority = random.uniform(1, 10)
            out_q.put(data, random.uniform(1, 10))
            print("produce data %d with priority %d" % (data, priority))
        time.sleep(batch)


# A thread that consumes data
def consumer(in_q):
    while True:
        for n in range(batch):
            data = in_q.get()
            # Process the data
            print("get data", data)
        time.sleep(batch)


# Create the shared queue and launch both threads
q = PriorityQueue()
t1 = Thread(target=consumer, args=(q,))
t2 = Thread(target=producer, args=(q,))
t1.start()
t2.start()
