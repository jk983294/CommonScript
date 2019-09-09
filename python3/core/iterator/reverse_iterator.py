# iterator reverse order
for item in reversed(range(5)):
    print(item, " ", end='')
print()


class Countdown:
    def __init__(self, start):
        self.start = start

    # Forward iterator
    def __iter__(self):
        n = self.start
        while n > 0:
            yield n
            n -= 1

    # Reverse iterator
    def __reversed__(self):
        n = 1
        while n <= self.start:
            yield n
            n += 1


for rr in reversed(Countdown(3)):
    print(rr)                           # 1 2 3

for rr in Countdown(3):
    print(rr)                           # 3 2 1
