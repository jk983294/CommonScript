import time
from contextlib import contextmanager


@contextmanager
def timethis(label):
    start = time.time()             # __enter__() call before yield
    try:
        yield
    finally:
        end = time.time()           # __exit__() call after yield
        print('{}: {}'.format(label, end - start))


with timethis('counting'):
    n = 10000000
    while n > 0:
        n -= 1


@contextmanager
def list_transaction(orig_list):
    """
    it only works when all operation under with finish without exception, then orig_list can take effect
    """
    working = list(orig_list)
    yield working
    orig_list[:] = working


items = [1, 2, 3]
with list_transaction(items) as working:
    working.append(4)
    working.append(5)
print(items)
