def manual_iter(a):
    li = a.__iter__()
    try:
        while True:
            print(next(li))
    except StopIteration:
        pass


a = [1, 2]
manual_iter(a)
