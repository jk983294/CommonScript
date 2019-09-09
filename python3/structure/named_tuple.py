from collections import namedtuple


Subscriber = namedtuple('Subscriber', ['addr', 'joined'])
sub = Subscriber('jonesy@example.com', '2012-10-19')
print(sub)                          # Subscriber(addr='jonesy@example.com', joined='2012-10-19')
print(sub.addr, sub.joined)         # jonesy@example.com 2012-10-19

print(len(sub))                     # 2
addr, joined = sub
print(addr, joined)                 # jonesy@example.com 2012-10-19


# make function more readable
Stock = namedtuple('Stock', ['name', 'shares', 'price'])


def compute_cost(records):
    total = 0.0
    for rec in records:
        s = Stock(*rec)     # convert normal tuple to named tuple to increase readability
        total += s.shares * s.price
    return total


# named tuple cannot be changed, use _replace to create a new one
s = Stock('ACME', 100, 123.45)
s = s._replace(shares=75)
print(s)                    # Stock(name='ACME', shares=75, price=123.45)


# Create a prototype instance
stock_prototype = Stock('', 0, 0.0)


# Function to convert a dictionary to a Stock
def dict_to_stock(s):
    return stock_prototype._replace(**s)


a = {'name': 'ACME', 'shares': 100}
print(dict_to_stock(a))     # Stock(name='ACME', shares=100, price=0.0)

