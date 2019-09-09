import re
from calendar import month_abbr

print('hello, world!'.replace("hello", "HELLO"))                    # 'HELLO, world!'


# use re module
text = 'Today is 11/27/2012. PyCon starts 3/13/2013.'
# \n means nth group captured
datepat = re.compile(r'(\d+)/(\d+)/(\d+)')
print(datepat.sub(r'\3-\1-\2', text))                               # Today is 2012-11-27. PyCon starts 2013-3-13.


# replace with reg callback
def change_date(m):
    mon_name = month_abbr[int(m.group(1))]
    return '{} {} {}'.format(m.group(2), mon_name, m.group(3))


print(datepat.sub(change_date, text))                               # Today is 27 Nov 2012. PyCon starts 13 Mar 2013.
