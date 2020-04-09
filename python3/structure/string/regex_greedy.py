import re

"""
default is greedy mode, use ? after ?/+ to change away from greedy mode
"""

str_pat = re.compile(r'"(.*)"')
text1 = 'Computer says "no."'
print(str_pat.findall(text1))               # ['no.']
text2 = 'Computer says "no." Phone says "yes."'
print(str_pat.findall(text2))               # ['no." Phone says "yes.']


# turn off greedy mode
# （.*）是贪婪匹配, （.*?）是非贪婪匹配
str_pat = re.compile(r'"(.*?)"')
print(str_pat.findall(text2))               # ['no.', 'yes.']


