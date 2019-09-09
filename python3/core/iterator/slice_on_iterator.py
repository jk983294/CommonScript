import itertools


def display_iterator_content(o, stop_value=None):
    for i in o:
        if stop_value is not None and i > stop_value:
            break
        print(i, end='')
    print()


display_iterator_content(itertools.islice('ABCDEFG', 2))                                    # A B
display_iterator_content(itertools.islice('ABCDEFG', 2, 4))                                 # C D
display_iterator_content(itertools.islice('ABCDEFG', 2, None))                              # C D E F G
display_iterator_content(itertools.islice('ABCDEFG', 0, None, 2))                           # A C E G


# slice on generator
def count(n):
    while True:
        yield n
        n += 1


for x in itertools.islice(count(0), 10, 12):
    print(x)                                                                                # 10 11
