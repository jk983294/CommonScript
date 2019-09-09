from configparser import ConfigParser
import sys

"""
case insensitive in ini config
"""

cfg = ConfigParser()
cfg.read('config.ini')
cfg.sections()
cfg.get('installation', 'library')
cfg.getboolean('debug', 'log_errors')   # for boolean value: true/TRUE/yes/1 they are equal
cfg.getint('server', 'port')
print(cfg.get('server', 'signature'))

# modify cfg and write back
cfg.set('server', 'port', '9000')
cfg.set('debug', 'log_errors', 'False')
cfg.write(sys.stdout)

# read user directory config
# cfg.read(os.path.expanduser('~/.config.ini'))
