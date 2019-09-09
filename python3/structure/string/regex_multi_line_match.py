import re

"""
default is greedy mode, use ? after ?/+ to change away from greedy mode
"""

comment = re.compile(r'/\*(.*?)\*/')
text1 = '/* this is a comment */'
text2 = '''/* this is a
multiline comment */
'''
print(comment.findall(text1))               # [' this is a comment ']
print(comment.findall(text2))               # []


# (?:.|\n) is a non-captured group, only used for match
comment = re.compile(r'/\*((?:.|\n)*?)\*/')
print(comment.findall(text2))               # [' this is a\nmultiline comment ']

# re.DOTALL let . can match '\n'
comment = re.compile(r'/\*(.*?)\*/', re.DOTALL)
print(comment.findall(text2))               # [' this is a\nmultiline comment ']
