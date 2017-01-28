import re

# match / search returns None if the regexp doesn't match
my_reg_exp = re.compile(r"(\w+)\s*=\s*(.+)")
my_reg_exp.match("temp_dir = /tmp")
my_reg_exp.search("blabla temp_dir = /tmp")

# match email address
re.match("[a-z]+://[a-zA-Z0-9][a-zA-Z0-9\.-]+/.*", "http://www.google.com/")
re.match("[a-z]+://[a-zA-Z0-9][a-zA-Z0-9\.-]+/.*", "www.google.com")

# groups
re.match("([a-z]+)://([a-zA-Z0-9][a-zA-Z0-9\.-]+)/(.*)", "http://www.google.com/").groups()
re.match("([a-z]+)://([a-zA-Z0-9][a-zA-Z0-9\.-]+)/(.*)", "http://www.google.com/blalba/qwqq").groups()

# keyed groups
my_reg_exp = re.compile(r"(?P<key>\w+)\s*=\s*(?P<value>.+)")
my_reg_exp.match("temp_dir = /tmp").groupdict()                         # {'key': 'temp_dir', 'value': '/tmp'}

# replace / substitute
re.sub(",\s*", ",", "this, line ,  contains,   more, items ")           # 'this,line,contains,more,items'

# split
re.split(",\s*", "this, line ,  contains,   more, items ")              # ['this', 'line', 'contains', 'more', 'items']

# findall
re.findall("\d{4}-\d\d-\d\d", "dates: 2008-02-05 and 2009-10-12")       # ['2008-02-05', '2009-10-12']
