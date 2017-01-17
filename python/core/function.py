# all parameters in the Python language are passed by reference

def printinfo( name, age = 10 ):
    "This prints a passed info into this function"
    print "Name: ", name
    print "Age ", age
    return

printinfo( age=50, name="miki" )
printinfo( name="miki" )


# variable-length arguments
# vartuple holds the values of all nonkeyword variable arguments
# kwargs holds the values of all keyword variable arguments
def printinfo( arg1, *vartuple, **kwargs ):
    print "Output is: "
    print "single argument: ", arg1
    for var in vartuple:
        print var
    for key, value in kwargs.iteritems():
        print key, value
    return

printinfo( 10 )
printinfo( 70, 60, 50 )
printinfo( 70, 60, 50, a = 1, b = 2 )
my_arguments = (70, 60, 50)
printinfo(*my_arguments)                                            # positional arguments
my_arguments_dict = { "a" : 1, "b" : 2}
printinfo(*my_arguments, **my_arguments_dict)


# lambda
sum = lambda arg1, arg2: arg1 + arg2
print "Value of total : ", sum( 10, 20 )

# Functions as variables
def divide(a, b):
    return a / b
def call(func, *args, **kwargs):
    return func(*args, **kwargs)
call(divide, 6, 3)                                                  # 2
