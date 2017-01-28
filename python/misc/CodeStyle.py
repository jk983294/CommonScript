# indent is 4 spaces

# whitespace in Expressions and Statements
# spam(ham[1], {eggs: 2})

# Naming Convention
# CamelCase for classes
# underscore_separated method names, function names, variables

# use same typed variables in containers
# DO NOT: a=["a", "b", 42, [8,4,5], (1,2,3), {"id": 77}]


# Type conversion, Instead of type checking, convert it, It will raise TypeError / ValueError if it's not possible
def arithmetic_multiply(op1, op2):
    return int(op1) * int(op2)
