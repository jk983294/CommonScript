import logging


if __name__ == '__main__':
    # Configure the logging system
    # logging.config.fileConfig('logconfig.ini')    # better to give config file
    logging.basicConfig(
        filename='app.log',
        level=logging.INFO,
        format='%(levelname)s:%(asctime)s:%(message)s'
    )

    # Variables (to make the calls that follow work)
    hostname = 'www.python.org'
    item = 'spam'
    filename = 'data.csv'
    mode = 'r'

    # Example logging calls (insert into your program)
    logging.critical('Host %s unknown', hostname)
    logging.error("Couldn't find %r", item)
    logging.warning('Feature is deprecated')
    logging.info('Opening file %r, mode=%r', filename, mode)

    # change level manually
    logging.getLogger().level = logging.DEBUG
    logging.debug('Got here')
