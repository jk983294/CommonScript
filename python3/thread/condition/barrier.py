import threading
import time

'''
Each of the threads tries to pass the barrier by calling the wait() method 
and will block until all of the threads have made their wait() calls. 
At this point, the threads are released simultaneously.
'''

b = threading.Barrier(2, timeout=5)


# Worker thread
def worker(n):
    b.wait()
    # Do some work
    print('Working', n)


# Create some threads
nWorkers = 2
for n in range(nWorkers):
    t = threading.Thread(target=worker, args=(n,))
    t.start()

time.sleep(10)
