"""
do not calculate util explicitly request it
after calculation, cache the result for next query
"""
import math


class lazyproperty:
    def __init__(self, func):
        self.func = func

    def __get__(self, instance, cls):
        if instance is None:
            return self
        else:
            value = self.func(instance)
            setattr(instance, self.func.__name__, value)
            return value


class Circle:
    def __init__(self, radius):
        self.radius = radius

    @lazyproperty
    def area(self):
        print('Computing area')
        return math.pi * self.radius ** 2


c = Circle(4.0)
print(c.radius)                         # 4.0
print(c.area)                           # Computing area 50.26548245743669
print(c.area)                           # 50.26548245743669
