import threading

"""
Reentrant lock
"""


class SharedCounter:
    """
    A counter object that can be shared by multiple threads.
    """
    _lock = threading.RLock()       # class wide lock

    def __init__(self, initial_value = 0):
        self._value = initial_value

    def incr(self,delta=1):
        # Increment the counter with locking
        with SharedCounter._lock:
            self._value += delta

    def decr(self,delta=1):
        # Decrement the counter with locking
        with SharedCounter._lock:
            self.incr(-delta)
