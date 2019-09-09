"""
*args holds the values of all non-keyword variable arguments
**kwargs holds the values of all keyword variable arguments
"""


def print_info(arg1, *args, **kwargs):
    print("single argument:", arg1, end=' ')
    print("tuple argument: ", end='')
    for var in args:
        print(var, end=' ')
    print("keyword argument: ", end='')
    for key, value in kwargs.items():
        print(key, value, end=' ')
    print()
    return


print_info(10)
print_info(70, 60, 50)
print_info(70, 60, 50, a=1, b=2)
my_arguments = (70, 60, 50)
print_info(*my_arguments)                           # positional arguments
my_arguments_dict = {"a": 1, "b": 2}
# *my_arguments called argument unpacking
# **my_arguments_dict called keyword argument unpacking
# func(**{'type':'Event'}) is equivalent to func(type='Event')
print_info(*my_arguments, **my_arguments_dict)
