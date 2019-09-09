import os

# x mode, if file exist, then skip it, otherwise write it with w mode
with open('somefile', 'xt') as f:
    f.write('Hello\n')


def verbose_version():
    if not os.path.exists('somefile'):
        with open('somefile', 'wt') as f:
            f.write('Hello\n')
    else:
        print('File already exists!')
