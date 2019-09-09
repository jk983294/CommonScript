import sys

text = 'Hello'

print(format(text, '>10'))                              # '     Hello'
print(format(text, '<10'))                              # 'Hello     '
print(format(text, '^10'))                              # '  Hello   '
print(format(text, '=>10s'))                            # '=====Hello'
print(format(text, '*^10s'))                            # '**Hello***'
print('{:>10s} {:>10s}'.format('Hello', 'World'))       # '     Hello      World'

x = 1.2345
print(format(x, '>10'))                                 # '    1.2345'
print(format(x, '^10.2f'))                              # '   1.23   '

# format with name value
s = '{name} has {n} messages.'
print(s.format(name='Guido', n=37))                     # Guido has 37 messages.

# find variable in current context
name = 'Guido'
n = 37
print(s.format_map(vars()))                             # Guido has 37 messages.


# vars with object
class Info:
    def __init__(self, name, n):
        self.name = name
        self.n = n


a = Info('Guido', 37)
print(s.format_map(vars(a)))                            # Guido has 37 messages.


# handle key missing
class SafeSub(dict):
    """in case key missing"""
    def __missing__(self, key):
        return '{' + key + '}'


def sub(str_text):
    return str_text.format_map(SafeSub(sys._getframe(1).f_locals))


print(sub('Hello {name}'))                              # Hello Guido
print(sub('You have {n} messages.'))                    # You have 37 messages.
print(sub('Your favorite color is {color}'))            # Your favorite color is {color}

# % operator
print('%-10s' % text)                                   # 'Hello     '
print('%10s' % text)                                    # '     Hello'
