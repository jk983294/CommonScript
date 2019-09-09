import logging
from multiprocessing import Pool
from functools import partial


def output_result(result, log=None):
    if log is not None:
        log.debug('Got: %r', result)


def add(x, y):
    return x + y


if __name__ == '__main__':
    logging.basicConfig(level=logging.DEBUG)
    log = logging.getLogger('test')

    p = Pool()
    p.apply_async(add, (3, 4), callback=partial(output_result, log=log))
    p.close()
    p.join()
