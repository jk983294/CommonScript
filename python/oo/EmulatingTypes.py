# case-insensitive dictionary, adding new method to a dict
class CIDict(dict):
    def __setitem__(self, key, value):
        if type(key) == str:
            key = key.lower()
        dict.__setitem__(self, key, value)

    def __getitem__(self, key):
        if type(key) == str:
            key = key.lower()
        return dict.__getitem__(self, key)


c = CIDict()
c["Apple"] = 88
c["ORangE"] = 99
print c                                                 # {'orange': 99, 'apple': 88}


# Emulating a function
class MyFunc(object):
    def __call__(self, a, b):
        return a / b


divide = MyFunc()
divide(6, 2)


# Overriding operators
class Severity(object):
    def __init__(self, level, text):
        self.level = int(level)
        self.text = text

    def __str__(self):
        return self.text

    def __repr__(self):
        return "<Severity level=%d text=%s>" % (self.level, self.text)

    def __cmp__(self, other):
        try:
            return cmp(self.level, other.level)
        except AttributeError:
            return


s1 = Severity(5, "debug")
s2 = Severity(6, "emerg")
s1 < s2  # True


# Properties are look like as simple attributes from the outside,
# but actually a method is called when the attribute's value is changed or read
# we define setter / getter functions for properties red & hex
class Color(object):
    def __init__(self, red, green, blue):
        self.color = [red, green, blue]

    def as_hex(self):
        return "#%02X%02X%02X" % tuple(self.color)

    def get_red(self):
        return self.color[0]

    def set_red(self, value):
        self.color[0] = value

    red = property(get_red, set_red)
    hex = property(as_hex)


my_color = Color(10, 20, 30)
print my_color.hex                                      # #0A141E
print my_color.red                                      # 10
