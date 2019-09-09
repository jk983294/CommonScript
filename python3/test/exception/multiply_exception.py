import logging
import errno

logger = logging.getLogger(__name__)
filename = 'not.exist'

try:
    f = open(filename)
except OSError as e:
    if e.errno == errno.ENOENT:
        logger.error('File not found')
    elif e.errno == errno.EACCES:
        logger.error('Permission denied')
    else:
        logger.error('Unexpected error: %d', e.errno)


# check exception hierarchy
print(FileNotFoundError.__mro__)
