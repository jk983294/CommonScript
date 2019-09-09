import gzip
import bz2

# gzip compression
with gzip.open('somefile.gz', 'rt') as f:
    text = f.read()

# bz2 compression
with bz2.open('somefile.bz2', 'rt') as f:
    text = f.read()
