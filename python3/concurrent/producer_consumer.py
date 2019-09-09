from threading import Thread
import time
import random
import queue

q = queue.Queue(10)


class ProducerThread(Thread):
    def run(self):
        nums = range(5)
        global q
        while True:
            num = random.choice(nums)
            q.put(num)
            print("Produced", num)
            time.sleep(random.random())


class ConsumerThread(Thread):
    def run(self):
        global q
        while True:
            num = q.get()
            q.task_done()
            print("Consumed", num)
            time.sleep(random.random())


ProducerThread().start()
ConsumerThread().start()
