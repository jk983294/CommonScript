import learn.thread.actor.actor_base as ActorBase
from threading import Event


"""
dispatch via function name
"""


class Result:
    def __init__(self):
        self._evt = Event()
        self._result = None

    def set_result(self, value):
        self._result = value
        self._evt.set()

    def result(self):
        self._evt.wait()
        return self._result


class Worker(ActorBase.Actor):
    def submit(self, func, *args, **kwargs):
        r = Result()
        self.send((func, args, kwargs, r))
        return r

    def run(self):
        while True:
            func, args, kwargs, r = self.recv()
            r.set_result(func(*args, **kwargs))


# Example
worker = Worker()
worker.start()
r = worker.submit(pow, 2, 3)
print(r.result())
worker.close()
worker.join()
