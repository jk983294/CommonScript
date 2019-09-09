import queue
import threading
import time


"""
only file can be polled by select, others you need to check via timer based check
"""


def consumer(queues):
    """
    Consumer that reads data on multiple queues simultaneously
    """
    while True:
        for q in queues:
            if not q.empty():
                item = q.get()
                print('Got:', item)

        # Sleep briefly to avoid 100% CPU
        time.sleep(0.01)


q1 = queue.Queue()
q2 = queue.Queue()
q3 = queue.Queue()
t = threading.Thread(target=consumer, args=([q1, q2, q3],))
t.start()

# Feed data to the queues
q1.put(1)
q2.put(10)
q3.put('hello')
q2.put(15)

t.join()
