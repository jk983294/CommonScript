import threading
import time

'''
Semaphore signal one thread at a time
'''


# Worker thread
def worker(n, sema):
    # Wait to be signaled
    sema.acquire()

    # Do some work
    print('Working', n)


# Create some threads
sema = threading.Semaphore(0)
nWorkers = 10
for n in range(nWorkers):
    t = threading.Thread(target=worker, args=(n, sema,))
    t.start()


for n in range(nWorkers):
    sema.release()
    time.sleep(1)
