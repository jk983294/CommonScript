import gzip
import bz2

text = 'hello world!'

# gzip compression
with gzip.open('somefile.gz', 'wt') as f:
    f.write(text)

# bz2 compression
with bz2.open('somefile.bz2', 'wt') as f:
    f.write(text)
