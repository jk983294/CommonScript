import copy


# copy class
class A:
    pass


a = A()
a.x = 12
b = copy.copy(a)
b.x  # 12
a.x = 24
b.x  # 12

# copy list
new_list = old_list[:]                  # shallow copy
new_list = copy.deepcopy(old_list)      # deep copy

# copy tuple
new_tuple = old_tuple[:]                # shallow copy
new_tuple = copy.deepcopy(old_tuple)    # deep copy
