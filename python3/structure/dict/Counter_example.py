from collections import Counter

c = Counter("An apple a day keeps the doctor")
c.update(" away")

print(c["w"])                                               # 1
print(c["a"])                                               # 5
print(c.most_common(3))                                     # [(' ', 7), ('a', 5), ('e', 4)]
c.most_common()                                             # [(' ', 7), ('a', 5), ('e', 4), ('p', 3), ('d', 2), ('o', 2), ('y', 2), ('t', 2), ('A', 1), ('c', 1), ('h', 1), ('k', 1), ('l', 1), ('n', 1), ('s', 1), ('r', 1), ('w', 1)]


# other type
Counter(['a', 'b', 'c', 'a', 'b', 'b'])                     # Counter({'b': 3, 'a': 2, 'c': 1})
Counter({'a': 2, 'b': 3, 'c': 1})                           # Counter({'b': 3, 'a': 2, 'c': 1})
Counter(a=2, b=3, c=1)                                      # Counter({'b': 3, 'a': 2, 'c': 1})


# example of word
cnt = Counter()
for word in ['red', 'blue', 'red', 'green', 'blue', 'blue']:
    cnt[word] += 1
print(cnt)                                                  # Counter({'blue': 3, 'red': 2, 'green': 1})

# union
a = Counter(['red', 'blue', 'red'])
b = Counter(['green', 'blue', 'blue'])
c = a + b
print(c)                                                    # Counter({'blue': 3, 'red': 2, 'green': 1})
