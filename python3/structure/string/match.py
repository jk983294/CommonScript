import re

# built-in
print('hello, world!'.count('ll'))                                  # 1
print('hello, world!'.find('ll'))                                   # 2
print('hello, world!'.index('ll'))                                  # 2 raises an exception if no such index exists
print('hello, world!'.rfind('o'))                                   # 8
print('hello, world!'.rindex('o'))                                  # 8 raises an exception if no such index exists


# match / search returns None if the regexp doesn't match
def is_regex_match(regex, text):
    if re.match(regex, text):
        return True
    else:
        return False


text1 = '11/27/2012'
text2 = 'Nov 27, 2012'
print(is_regex_match(r'\d+/\d+/\d+', text1))                        # True
print(is_regex_match(r'\d+/\d+/\d+', text2))                        # False

datepat = re.compile(r'\d+/\d+/\d+')
text = 'Today is 11/27/2012. PyCon starts 3/13/2013.'
print(datepat.findall(text))                                        # ['11/27/2012', '3/13/2013']

# group capture
datepat = re.compile(r'(\d+)/(\d+)/(\d+)')
m = datepat.match('11/27/2012')
print(m.group(0), m.group(1), m.group(2), m.group(3))               # 11/27/2012 11 27 2012
print(m.groups())                                                   # ('11', '27', '2012')
month, day, year = m.groups()
print(month, day, year)                                             # 11 27 2012

print(datepat.findall(text))                                        # [('11', '27', '2012'), ('3', '13', '2013')]

for month, day, year in datepat.findall(text):
    print('{}-{}-{}'.format(year, month, day))

# find ignore case
text = 'UPPER PYTHON, lower python, Mixed Python'
print(re.findall('python', text, flags=re.IGNORECASE))              # ['PYTHON', 'python', 'Python']
print(re.sub('python', 'snake', text, flags=re.IGNORECASE))         # UPPER snake, lower snake, Mixed snake

