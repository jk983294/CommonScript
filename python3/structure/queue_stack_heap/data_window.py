from collections import deque


def get_window_data(data, size):
    window = deque(maxlen=size)
    for item in data:
        window.append(item)
        yield window


for window in get_window_data(range(10), 5):
    print(window)


q = deque()
q.append(1)
q.append(2)
q.append(3)
print(q)                    # deque([1, 2, 3])
q.appendleft(4)
print(q)                    # deque([4, 1, 2, 3])
print(q.pop())              # 3
print(q)                    # deque([4, 1, 2])
print(q.popleft())          # 4
print(q)                    # deque([1, 2])
