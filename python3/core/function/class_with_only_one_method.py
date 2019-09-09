"""
class with only one method can be converted to closure returned from function
it can keep internal states within closure
"""


def my_func(internal_value):
    def add(value):
        return internal_value + value
    return add


f = my_func(42)
print(f(1))                 # 43
print(f(2))                 # 44
