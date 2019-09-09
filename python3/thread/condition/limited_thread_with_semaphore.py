from threading import Semaphore
import urllib.request

'''
Semaphore used to constraint the number of thread
Semaphore used by with, the counter - 1, when with block ends, the counter + 1
when counter < 0, it blocks
'''

# At most, five threads allowed to run at once
_fetch_url_sema = Semaphore(5)


def fetch_url(url):
    with _fetch_url_sema:
        return urllib.request.urlopen(url)
