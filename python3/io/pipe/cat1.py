import sys

# example: cat cat1.py | python cat1.py
for line in sys.stdin:
    print(line, end='')             # print without new line
