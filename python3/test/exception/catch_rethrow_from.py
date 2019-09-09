"""
keep exception chain
"""


def example():
    try:
        int('N/A')
    except ValueError as e:
        raise RuntimeError('A parsing error occurred') from e


try:
    example()
except RuntimeError as e:
    print("It didn't work:", e)

    if e.__cause__:
        print('Cause:', e.__cause__)


def ignore_exception_chain():
    try:
        int('N/A')
    except ValueError:
        raise RuntimeError('A parsing error occurred') from None
