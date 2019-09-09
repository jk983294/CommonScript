import os
import fnmatch
import gzip
import bz2
import re


"""
yield is data producer while for loop is data consumer
when generator put together, every yield will pass each item to next pipe stage
"""


def gen_find(filepat, top):
    """
    Find all filenames in a directory tree that match a shell wildcard pattern
    """
    for path, dirlist, filelist in os.walk(top):
        for name in fnmatch.filter(filelist, filepat):
            yield os.path.join(path, name)


def gen_opener(filenames):
    """
    Open a sequence of filenames one at a time producing a file object.
    The file is closed immediately when proceeding to the next iteration.
    """
    for filename in filenames:
        if filename.endswith('.gz'):
            f = gzip.open(filename, 'rt')
        elif filename.endswith('.bz2'):
            f = bz2.open(filename, 'rt')
        else:
            f = open(filename, 'rt')
        yield f
        f.close()


def gen_concatenate(iterators):
    """
    Chain a sequence of iterators together into a single sequence.
    """
    for it in iterators:
        yield from it       # this delegate to its parent's generator so memory foot print is small


def gen_grep(pattern, lines):
    """
    Look for a regex pattern in a sequence of lines
    """
    pat = re.compile(pattern)
    for line in lines:
        if pat.search(line):
            yield line


lognames = gen_find('*.py', './')
files = gen_opener(lognames)
lines = gen_concatenate(files)
# lines = itertools.chain(*files)       # do not use this, it will create a huge collection
matched_lines = gen_grep('generator', lines)

for line in matched_lines:
    print(line)
