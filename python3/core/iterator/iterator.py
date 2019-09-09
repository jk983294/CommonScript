import itertools


def display_iterator_content(o, stop_value=None):
    for i in o:
        if stop_value is not None and i > stop_value:
            break
        print(i, end='')
    print()


# itertools module
display_iterator_content(itertools.count(10), 15)                                           # 10 11 12 13 14 15
display_iterator_content(itertools.count(2.5, 0.5), 5)                                      # 2.5 3.0 3.5 4.0 4.5 5.0
display_iterator_content(itertools.cycle('ABCD'), 'C')                                      # A B C D A B C D ...
display_iterator_content(itertools.repeat(10, 3))                                           # 10 10 10
# common use for repeat is to supply a stream of constant values to map or zip, [0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
display_iterator_content(list(map(pow, range(10), itertools.repeat(2))))
display_iterator_content(itertools.compress('ABCDEF', [1, 0, 1, 0, 1, 1]))                  # A C E F

# drop first elements if condition met
display_iterator_content(itertools.dropwhile(lambda x: x < 5, [1, 4, 6, 4, 1]))             # 6 4 1
# only take first elements if condition met
display_iterator_content(itertools.takewhile(lambda x: x < 5, [1, 4, 6, 4, 1]))             # 1 4

display_iterator_content(filter(lambda x: x % 2, range(10)))                                # 1 3 5 7 9
display_iterator_content(itertools.filterfalse(lambda x: x % 2, range(10)))                 # 0 2 4 6 8
display_iterator_content(map(pow, (2, 2, 2), (2, 3, 4)))                                    # 4 8 16
display_iterator_content(itertools.starmap(pow, [(2, 2), (2, 3), (2, 4)]))                  # 4 8 16
display_iterator_content(zip('ABCD', 'xy'))                                                 # ('A', 'x') ('B', 'y')
# ('A', 'x') ('B', 'y') ('C', '-') ('D', '-')
display_iterator_content(itertools.zip_longest('ABCD', 'xy', fillvalue='-'))
display_iterator_content(itertools.product('ABCD', 'xy'))                                   # Ax Ay Bx By Cx Cy Dx Dy
# AA AB AC AD BA BB BC BD CA CB CC CD DA DB DC DD
display_iterator_content(itertools.product('ABCD', repeat=2))

