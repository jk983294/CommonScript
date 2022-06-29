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


def next_choice(max_choice_count, choice):
    size = len(max_choice_count)
    for i in range(size):
        idx = size - 1 - i
        if choice[idx] != max_choice_count[idx] - 1:
            choice[idx] += 1
            fill_size = size - 1 - idx
            if fill_size > 0:
                for j in range(fill_size):
                    choice[idx + 1 + j] = 0
            return True
    return False


def get_all_choices(max_choice_count):
    ret_ = []
    choice = [0] * len(max_choice_count)
    while True:
        ret_.append(copy.deepcopy(choice))
        status = next_choice(max_choice_count, choice)
        if not status:
            break
    return ret_


ret = get_all_choices([3, 1, 2])
print(ret)
