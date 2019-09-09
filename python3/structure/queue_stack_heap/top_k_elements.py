import heapq

"""
if k << n, then use heap nsmallest/nlargest
if k approx == n, then use sorted(items)[:N]/sorted(items)[-N:]
"""

nums = [1, 8, 2, 23, 7, -4, 18, 23, 42, 37, 2]
print(heapq.nlargest(3, nums))                      # [42, 37, 23]
print(heapq.nsmallest(3, nums))                     # [-4, 1, 2]

# handle structure
portfolio = [
    {'name': 'IBM', 'shares': 100, 'price': 91.1},
    {'name': 'AAPL', 'shares': 50, 'price': 543.22},
    {'name': 'FB', 'shares': 200, 'price': 21.09},
    {'name': 'HPQ', 'shares': 35, 'price': 31.75},
    {'name': 'YHOO', 'shares': 45, 'price': 16.35},
    {'name': 'ACME', 'shares': 75, 'price': 115.65}
]
cheap = heapq.nsmallest(1, portfolio, key=lambda s: s['price'])
expensive = heapq.nlargest(1, portfolio, key=lambda s: s['price'])
print(cheap)                                        # [{'price': 16.35, 'shares': 45, 'name': 'YHOO'}]
print(expensive)                                    # [{'price': 543.22, 'shares': 50, 'name': 'AAPL'}]

# heap structure
nums = [1, 8, 2, 23, 7, -4, 18, 23, 42, 37, 2]
heap = list(nums)
heapq.heapify(heap)
while len(heap) > 0:
    print(heapq.heappop(heap), " ", end='')         # -4  1  2  2  7  8  18  23  23  37  42
