def myfun():
    return 1, 2, 3


a, b, c = myfun()
print(a, b, c)                  # 1 2 3
a = myfun()
print(a)                        # (1, 2, 3)
