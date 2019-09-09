# all parameters in the Python language are passed by reference


def print_info(name, age=10):
    """This prints a passed info into this function"""
    print("Name: ", name)
    print("Age ", age)
    return


print_info(age=50, name="miki")
print_info(name="miki")


# Functions as variables
def divide(a, b):
    return a / b


def call(func, *args, **kwargs):
    return func(*args, **kwargs)


print(call(divide, 6, 3))                           # 2.0
