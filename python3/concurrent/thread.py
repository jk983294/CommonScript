import threading
import time

# thread (low-level) and threading (higher-level, OOP) modules
# Python threads mostly used with Blocking operations(sockets in blocking mode) or I/O intensive applications
# Global Interpreter Lock (GIL):
# 1. Only one thread can execute low-level instruction in the VM at one time,
#    race condition still a problem since only low-level instruction doesn't have race condition
# 2. Threads don't scale to multiple cores / CPUs


class MyThread (threading.Thread):
    def __init__(self, thread_id, name, counter):
        threading.Thread.__init__(self)
        self.thread_id = thread_id
        self.name = name
        self.counter = counter

    def run(self):
        print("Starting " + self.name)
        # Get lock to synchronize threads
        threadLock.acquire()
        print_time(self.name, self.counter, 3)
        # Free lock to release next thread
        threadLock.release()


def print_time(thread_name, delay, counter):
    while counter:
        time.sleep(delay)
        print("%s: %s" % (thread_name, time.ctime(time.time())))
        counter -= 1


threadLock = threading.Lock()
threads = []

thread1 = MyThread(1, "Thread-1", 1)
thread2 = MyThread(2, "Thread-2", 2)

thread1.start()
thread2.start()

threads.append(thread1)
threads.append(thread2)


for t in threads:                                                       # Wait for all threads to complete
    t.join()

print("Exiting Main Thread")
