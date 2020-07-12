from multiprocessing import Process, Lock

"""
a process lock to ensure that only one process prints to standard output at a time
"""


def f(l, i):
    l.acquire()
    try:
        print('hello world', i)
    finally:
        l.release()


if __name__ == '__main__':
    lock = Lock()

    for num in range(10):
        Process(target=f, args=(lock, num)).start()
