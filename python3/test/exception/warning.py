import warnings

"""
python3 -W all warning.py
python3 -W ignore warning.py
python3 -W error warning.py                 # turn warning to error
"""


def func(x, y, logfile=None, debug=False):
    if logfile is not None:
         warnings.warn('logfile argument deprecated', DeprecationWarning)


func(1, 2, 'logfile')
