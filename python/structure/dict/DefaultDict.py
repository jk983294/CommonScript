from collections import defaultdict

counter = defaultdict(int)

for letter in "An apple a day keeps the doctor away":
    counter[letter] += 1

print counter
# defaultdict(<type 'int'>, {'A': 1, ' ': 7, 'c': 1, 'e': 4, 'd': 2, 'h': 1, 'k': 1,
# 'l': 1, 'o': 2, 'n': 1, 'p': 3, 's': 1, 'r': 1, 'a': 5, 'w': 1, 'y': 2, 't': 2})
