import math


class Circle:
    def __init__(self, radius):
        self.radius = radius

    @property
    def area(self):
        return math.pi * self.radius ** 2

    @property
    def diameter(self):
        return self.radius * 2

    @property
    def perimeter(self):
        return 2 * math.pi * self.radius


c = Circle(4.0)
print(c.radius)                         # 4.0
print(c.area)                           # Notice lack of ()          50.26548245743669
print(c.perimeter)                      # Notice lack of ()          25.132741228718345


class Person:
    def __init__(self, first_name):
        self.first_name = first_name

    # this makes first_name a property
    @property
    def first_name(self):
        return self._first_name

    # add setter for property first_name
    @first_name.setter
    def first_name(self, value):
        if not isinstance(value, str):
            raise TypeError('Expected a string')
        self._first_name = value


a = Person('Guido')
print(a.first_name)
a.first_name = 42           # call the setter failed due to type mismatch
