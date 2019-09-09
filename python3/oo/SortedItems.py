import collections.abc
import bisect


class SortedItems(collections.abc.Sequence):
    def __init__(self, initial=None):
        self._items = sorted(initial) if initial is not None else []

    # required sequence methods
    def __getitem__(self, index):
        return self._items[index]

    def __len__(self):
        return len(self._items)

    # method for adding an item in the right location
    def add(self, item):
        bisect.insort(self._items, item)


items = SortedItems([5, 1, 3])
print(list(items))                  # [1, 3, 5]
print(items[0], items[-1])          # 1 5
items.add(2)
print(list(items))                  # [1, 2, 3, 5]
