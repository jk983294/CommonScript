# all parameters in the Python language are passed by reference


def print_info(name, age=10):
    """This prints a passed info into this function"""
    print "Name: ", name
    print "Age ", age
    return

print_info(age=50, name="miki")
print_info(name="miki")


# variable-length arguments
# vartuple holds the values of all non-keyword variable arguments
# kwargs holds the values of all keyword variable arguments
def print_info(arg1, *vartuple, **kwargs):
    print "Output is: "
    print "single argument: ", arg1
    for var in vartuple:
        print var
    for key, value in kwargs.iteritems():
        print key, value
    return


print_info(10)
print_info(70, 60, 50)
print_info(70, 60, 50, a=1, b=2)
my_arguments = (70, 60, 50)
print_info(*my_arguments)                           # positional arguments
my_arguments_dict = {"a": 1, "b": 2}
print_info(*my_arguments, **my_arguments_dict)

# lambda
sum_func = lambda arg1, arg2: arg1 + arg2
print "Value of total : ", sum_func(10, 20)


# Functions as variables
def divide(a, b):
    return a / b


def call(func, *args, **kwargs):
    return func(*args, **kwargs)

call(divide, 6, 3)                                  # 2
