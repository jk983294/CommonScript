prices = {
    'ACME': 45.23,
    'AAPL': 612.78,
    'IBM': 205.55,
    'HPQ': 37.20,
    'FB': 10.75
}

# zip is iterator, can only used once
min_price = min(zip(prices.values(), prices.keys()))
print(min_price)                                    # (10.75, 'FB')
max_price = max(zip(prices.values(), prices.keys()))
print(max_price)                                    # (612.78, 'AAPL')
prices_sorted = sorted(zip(prices.values(), prices.keys()))

# default min max is applied to key only
print(min(prices))                                  # 'AAPL'
print(max(prices))                                  # 'IBM'

# get min/max value
print(min(prices.values()))                         # 10.75
print(max(prices.values()))                         # 612.78

# get key of min/max value
print(min(prices, key=lambda k: prices[k]))         # 'FB'
print(max(prices, key=lambda k: prices[k]))         # 'AAPL'


