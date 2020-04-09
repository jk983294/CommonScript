import sys

# StopIteration                 when the next() of an iterator point to None
# SystemExit                    sys.exit()
# StandardError                 Base class for all built-in exceptions except StopIteration and SystemExit.
# ArithmeticError               Base class for all errors that occur for numeric calculation.
# OverflowError                 calculation exceeds maximum limit for a numeric type.
# FloatingPointError            floating point calculation fails.
# ZeroDivisonError              division or modulo by zero
# AssertionError                failure of the Assert statement.
# AttributeError                failure of attribute reference or assignment.
# EOFError                      no input from either the input() function and the end of file is reached.
# ImportError                   import statement fails.
# KeyboardInterrupt             when the user interrupts program execution, usually by pressing Ctrl+c.
# LookupError                   Base class for all lookup errors.
# IndexError                    when an index is not found in a sequence.
# KeyError                      when the specified key is not found in the dictionary.
# NameError                     identifier is not found in the local or global namespace.
# UnboundLocalError             trying to access a local variable in a function or method but no value has been assigned to it.
# EnvironmentError              Base class for all exceptions that occur outside the Python environment.
# IOError                       IO operation fails
# SyntaxError                   an error in Python syntax.
# IndentationError              indentation is not specified properly.
# SystemError                   the interpreter finds an internal problem
# SystemExit                    interpreter is quit by using the sys.exit() function
# ValueError                    data type has the valid type of arguments, but the arguments have invalid values specified.
# RuntimeError                  a generated error does not fall into any category.
# NotImplementedError           an abstract method that needs to be implemented in an inherited class is not actually implemented.


# assert
def kelvin2fahrenheit(temperature):
    assert (temperature >= 0), "Colder than absolute zero!"
    return ((temperature - 273) * 1.8) + 32


# try catch
try:
    fh = open("testfile", "w")
    fh.write("This is my test file for exception handling!!")
except IOError as err:
    print("Error: can\'t find file or read data", file=sys.stderr)
    raise  # re-raise the exception
except (ValueError, TypeError):
    print("Handling multiple exceptions within the same except block")
else:  # 没有捕获到异常，执行else语句
    print("Written content in the file successfully")
    fh.close()
finally:  # 不管是否捕获到异常，都执行finally语句
    print("must execute")

# catch all exceptions
try:
    x = open("file.txt", "r")
except IOError as e:
    print("Unable to open file.txt")

try:
    pass
except:
    print("catch all")


# custom exceptions
class UsageError(Exception):
    pass


raise UsageError("User error, invalid input string specified")
