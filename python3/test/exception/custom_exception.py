class UsageError(Exception):
    pass


class CustomError(Exception):
    def __init__(self, message, status):
        # must call below, it put your data into exception internal args dict for further print out
        super().__init__(message, status)
        self.message = message
        self.status = status


try:
    raise RuntimeError('It failed', 42, 'spam')
except RuntimeError as e:
    print(e.args)               # ('It failed', 42, 'spam')

raise UsageError("User error, invalid input string specified")



