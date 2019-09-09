# lambda
sum_func = lambda arg1, arg2: arg1 + arg2
print("Value of total : ", sum_func(10, 20))

names = ['David H', 'Brian a', 'Raymond m', 'Ned c']
print(sorted(names, key=lambda name: name.split()[-1].lower()))     # ['Brian a', 'Ned c', 'David H', 'Raymond m']
