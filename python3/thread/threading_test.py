import time
from threading import Thread

'''
python thread suit for IO work and not good for computation bounded task due to GIL
'''


def countdown(n):
    while n > 0:
        print('T-minus', n)
        n -= 1
        time.sleep(1)


t = Thread(target=countdown, args=(5,))
t.start()

if t.is_alive():
    print('Still running')
else:
    print('Completed')

t.join()


# another way to inherit thread
class CountdownThread(Thread):
    def __init__(self, n):
        super().__init__()
        self.n = n

    def run(self):
        while self.n > 0:
            print('T-minus', self.n)
            self.n -= 1
            time.sleep(1)


c = CountdownThread(5)
c.start()
t.join()
