from contextlib import contextmanager
import threading

"""
when get multiple lock, always acquire lock by smaller id lock to bigger id lock
"""

# Thread-local state to stored information on locks already acquired
_local = threading.local()


@contextmanager
def acquire(*locks):
    # Sort locks by object identifier
    locks = sorted(locks, key=lambda x: id(x))

    # Make sure lock order of previously acquired locks is not violated
    acquired = getattr(_local, 'acquired', [])
    if acquired and max(id(lock) for lock in acquired) >= id(locks[0]):
        raise RuntimeError('Lock Order Violation')

    # Acquire all of the locks
    acquired.extend(locks)
    _local.acquired = acquired

    try:
        for lock in locks:
            lock.acquire()
        yield
    finally:
        # Release locks in reverse order of acquisition
        for lock in reversed(locks):
            lock.release()
        del acquired[-len(locks):]


x_lock = threading.Lock()
y_lock = threading.Lock()


def thread_1():
    while True:
        with acquire(x_lock, y_lock):
            print('Thread-1')


def thread_2():
    while True:
        with acquire(y_lock, x_lock):
            print('Thread-2')


t1 = threading.Thread(target=thread_1)
t1.start()

t2 = threading.Thread(target=thread_2)
t2.start()

t1.join()
t2.join()


def thread_3():
    while True:
        with acquire(x_lock):
            with acquire(y_lock):
                print('Thread-3')


def thread_4():
    while True:
        with acquire(y_lock):
            with acquire(x_lock):
                print('Thread-4')


print("thread_3 and thread_4 are potentially dead lock")
