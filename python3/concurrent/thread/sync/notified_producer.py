from queue import Queue
from threading import Thread, Event
import time


# A thread that produces data
def producer(out_q):
    data = 0
    while True:
        # Produce some data
        data += 1
        # Make an (data, event) pair and hand it to the consumer
        evt = Event()
        out_q.put((data, evt))
        print("produce data", data)
        # Wait for the consumer to process the item
        evt.wait()
        print("consumer consumed data", data)
        time.sleep(1)


# A thread that consumes data
def consumer(in_q):
    while True:
        # Get some data
        data, evt = in_q.get()
        # Process the data
        print("get data", data)
        # Indicate completion
        evt.set()


# Create the shared queue and launch both threads
q = Queue()
t1 = Thread(target=consumer, args=(q,))
t2 = Thread(target=producer, args=(q,))
t1.start()
t2.start()
