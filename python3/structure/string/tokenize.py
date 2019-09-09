import re
from collections import namedtuple


"""
?P<TOKENNAME> define a named pattern
long pattern must define first
"""

NAME = r'(?P<NAME>[a-zA-Z_][a-zA-Z_0-9]*)'
NUM = r'(?P<NUM>\d+)'
PLUS = r'(?P<PLUS>\+)'
TIMES = r'(?P<TIMES>\*)'
EQ = r'(?P<EQ>=)'
WS = r'(?P<WS>\s+)'

master_pat = re.compile('|'.join([NAME, NUM, PLUS, TIMES, EQ, WS]))

text = 'foo = 23 + 42 * 10'


def generate_tokens(pat, text):
    Token = namedtuple('Token', ['type', 'value'])
    scanner = pat.scanner(text)
    for m in iter(scanner.match, None):
        yield Token(m.lastgroup, m.group())


# Example use
tokens = (tok for tok in generate_tokens(master_pat, text) if tok.type != 'WS')
for tok in tokens:
    print(tok)

# Produces output
# Token(type='NAME', value='foo')
# Token(type='EQ', value='=')
# Token(type='NUM', value='23')
# Token(type='PLUS', value='+')
# Token(type='NUM', value='42')
# Token(type='TIMES', value='*')
# Token(type='NUM', value='10')
