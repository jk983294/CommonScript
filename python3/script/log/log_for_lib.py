import logging

log = logging.getLogger(__name__)               # dedicate log
log.addHandler(logging.NullHandler())


# Example function (for testing)
def func():
    log.critical('A Critical Error!')
    log.debug('A debug message')
