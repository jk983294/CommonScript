import math
import random
import operator

# Immutable : int, float, complex, string, bool, tuple
# Mutable : list, dictionary, set

counter = 100                                                               # An integer assignment
miles = 1000.0                                                              # A floating point
name = "John"                                                               # A string

a = b = c = 1
d, e, f = 1, 2, "john"
list1 = [1, 2, 3, 4, 5]


# data type conversion
print(int('42'))                                                            # Converts x to an integer. base specifies the base if x is a string.
print(float('42.3'))                                                        # Converts x to a floating-point number.
print(complex(1, 2))                                                        # Creates a complex number.
print(str(42))                                                              # Converts object x to a string representation.
print(repr((4, 2, ('spam', 'eggs'))))                                       # Converts object x to an expression string.
print(eval('40 + 2'))                                                       # Evaluates a string and returns an object.
print(tuple([1, 2, 3]))                                                     # Converts s to a tuple.
print(list((1, 2, 3)))                                                      # Converts s to a list.
print(set([1, 2, 3, 3]))                                                    # Converts s to a set.
print(dict([('limited', 1), ('all', 16), ('concept', 1)]))                  # Creates a dictionary. d must be a sequence of (key,value) tuples.
print(frozenset([1, 2, 3, 3]))                                              # Converts s to a frozen set.
print(chr(42))                                                              # Converts an integer to a character.
print(ord('a'))                                                             # Converts a single character to its integer value.
print(hex(32))                                                              # Converts an integer to a hexadecimal string.
print(oct(32))                                                              # Converts an integer to an octal string.


# operator
print(2 ** 4)                                                               # power
print(9 // 2)                                                               # floor division
print(a and b)
print(a or b)
print(not (a or b))
print(a in list1)
print(a not in list1)
print(a is b)                                                               # Identity operators compare the memory locations of two objects
print(a is not b)


# any, check any row satisfy some condition
def has_primary_key(rows):
    return any(row[1] == 0 and row[9] != 'YES' for row in rows)

# math
print(abs(-1))                                                              # The absolute value of x: the (positive) distance between x and zero.
print(math.ceil(1.1))                                                       # The ceiling of x: the smallest integer not less than x
print(math.floor(1.1))                                                      # The floor of x: the largest integer not greater than x
print(operator.le(1, 2))                                                    # -1 if x < y, 0 if x == y, or 1 if x > y
print(math.exp(1))                                                          # The exponential of x: ex
print(math.fabs(-1.3))                                                      # The absolute value of x.
print(math.log(2.73))                                                       # The natural logarithm of x, for x> 0
print(math.log10(100))                                                      # The base-10 logarithm of x for x> 0 .
print(max(1, 2, 3, 5, 6))                                                   # The largest of its arguments: the value closest to positive infinity
print(min(1, 2, 3, 5, 6))                                                   # The smallest of its arguments: the value closest to negative infinity
print(math.modf(4.2))                                                       # The fractional and integer parts of x in a two-item tuple. Both parts have the same sign as x. The integer part is returned as a float.
print(pow(2, 4))                                                            # The value of x**y.
print(round(0.4645, 2))                                                     # x rounded to n digits from the decimal point. Python rounds away from zero as a tie-breaker: round(0.5) is 1.0 and round(-0.5) is -1.0.
print(math.sqrt(100))                                                       # The square root of x for x > 0

# random number
random.seed(5)                                                              # Sets the integer starting value used in generating random numbers. Call this function before calling any other random module function. Returns None.
print(random.choice([1, 2, 4]))                                             # A random item from a list, tuple, or string.
print(random.randrange(1, 10, 2))                                           # A randomly selected element from range(start, stop, step), step is 2 means only odd number to be returned
print(random.random())                                                      # A random float r, such that 0 is less than or equal to r and r is less than 1
print(random.shuffle(list1))                                                # Randomizes the items of a list in place. Returns None.
print(random.uniform(1.0, 5.0))                                             # A random float r, such that x is less than or equal to r and r is less than y
