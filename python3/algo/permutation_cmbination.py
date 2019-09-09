import itertools


def display_iterator_content(o, stop_value=None):
    for i in o:
        if stop_value is not None and i > stop_value:
            break
        print(i, end='')
    print()


display_iterator_content(itertools.permutations(range(3), 2))                   # (0, 1)(0, 2)(1, 0)(1, 2)(2, 0)(2, 1)
display_iterator_content(itertools.permutations(range(3)))                      # 012 021 102 120 201 210
display_iterator_content(itertools.combinations(range(3), 2))                   # (0, 1)(0, 2)(1, 2)
# allow item be picked multiply times use combinations_with_replacement
display_iterator_content(itertools.combinations_with_replacement(range(3), 2))  # (0, 0)(0, 1)(0, 2)(1, 1)(1, 2)(2, 2)
