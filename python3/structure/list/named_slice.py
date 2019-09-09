record = '....................100 .......513.25 ..........'
SHARES = slice(20, 23)
PRICE = slice(31, 37)
shares_str = record[SHARES]
price_str = record[PRICE]
cost = int(shares_str) * float(price_str)

print(shares_str, price_str, cost)                  # 100 513.25 51325.0


a = slice(5, 50, 2)
print(a.start)                                      # 5
print(a.stop)                                       # 50
print(a.step)                                       # 2

s = 'HelloWorld'
print(a.indices(len(s)))                            # (5, 10, 2) new slice within index boundary
for i in range(*a.indices(len(s))):
    print(s[i], end='')                             # Wrd
