# x mode, if file exist, then skip it, otherwise write it with w mode
with open('somefile', 'xt') as f:
    f.write('Hello\n')