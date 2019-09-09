import pkgutil


def function3():
    print("function3")


def get_data():
    return pkgutil.get_data(__package__, 'pkg2.data')
