def remove_dupe_with_origin_order(items):
    seen = set()
    for item in items:
        if item not in seen:
            yield item
            seen.add(item)


a = [1, 5, 2, 1, 9, 1, 5, 10]
print(list(remove_dupe_with_origin_order(a)))  # [1, 5, 2, 9, 10]

print(list(set(a)))  # don't keep origin order


def remove_dupe_with_origin_order_with_key(items, key=None):
    seen = set()
    for item in items:
        val = item if key is None else key(item)
        if val not in seen:
            yield item
            seen.add(val)


a = [{'x': 1, 'y': 2}, {'x': 1, 'y': 3}, {'x': 1, 'y': 2}, {'x': 2, 'y': 4}]
# [{'x': 1, 'y': 2}, {'x': 1, 'y': 3}, {'x': 2, 'y': 4}]
l = list(remove_dupe_with_origin_order_with_key(a, key=lambda d: (d['x'], d['y'])))
print(l)

# [{'x': 1, 'y': 2}, {'x': 2, 'y': 4}]
print(list(remove_dupe_with_origin_order_with_key(a, key=lambda d: d['x'])))
