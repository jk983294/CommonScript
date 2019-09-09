p = (4, 5)
x, y = p
print(x, y)         # 4 5

data = ['ACME', 50, 91.1, (2012, 12, 21)]
name, shares, price, date = data
print(name, shares, price, date)                # ACME 50 91.1 (2012, 12, 21)

name, shares, price, (year, mon, day) = data
print(name, shares, price, year, mon, day)      # ACME 50 91.1 2012 12 21

# discard those you don't care with _
_, shares, price, _ = data
print(shares, price)                            # 50 91.1
name, *_, (*_, year) = data
print(name, year)                               # ACME 21

# extract multiply variable with *
data = [1, 2, 3, 4, 5]
x1, *x2, x3 = data
print(x2)                                       # [2, 3, 4]
y1, y2, *y3 = data
print(y3)                                       # [3, 4, 5]
*z1, z2, z3 = data
print(z1)                                       # [1, 2, 3]


records = [
    ('foo', 1, 2),
    ('bar', 'hello'),
    ('foo', 3, 4),
]


def do_foo(x, y):
    print('foo', x, y)


def do_bar(s):
    print('bar', s)


for tag, *args in records:
    if tag == 'foo':
        do_foo(*args)
    elif tag == 'bar':
        do_bar(*args)


# recur
def my_recur_sum(items):
    head, *tail = items
    return head + sum(tail) if tail else head


print(my_recur_sum(data))                       # 15
