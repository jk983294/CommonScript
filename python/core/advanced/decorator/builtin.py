import time
import random
from retrying import retry
from timeout import timeout

# TODO need to find accepts returns timeout decorator package

@accepts(int, int)
@returns(int)
def my_add(a, b):
    return a + b

@timeout(1, 'Function slow; aborted')
def slow_function():
    time.sleep(5)

@retry(stop_max_attempt_number=3, stop_max_delay=10000, wait_random_min=1000, wait_random_max=2000)
def do_something_unreliable():
    if random.randint(0, 10) > 1:
        raise IOError("Broken sauce, everything is hosed!!!111one")
    else:
        return "Awesome sauce!"
