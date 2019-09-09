x = 1234.56789

# Two decimal places of accuracy
print(format(x, '0.2f'))                    # '1234.57'

# Right justified in 10 chars, one-digit accuracy
print(format(x, '>10.1f'))                  # '    1234.6'

# Left justified
print(format(x, '<10.1f'))                  # '1234.6    '

# Centered
print(format(x, '^10.1f'))                  # '  1234.6  '

# Inclusion of thousands separator
print(format(x, ','))                       # '1,234.56789'
print(format(x, '0,.1f'))                   # '1,234.6'


print(format(x, 'e'))                       # '1.234568e+03'
print(format(x, '0.2E'))                    # '1.23E+03'
print('The value is {:0,.2f}'.format(x))    # The value is 1,234.57
