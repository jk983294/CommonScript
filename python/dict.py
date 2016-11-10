# give default value for an entry if not exist
port = dict.get('port', 3306)

# defaultdict
import collections as coll

dict_set = coll.defaultdict(set)                            # value is {}
dict_int = coll.defaultdict(int)                            # value is 0
dict_list = coll.defaultdict(list)                          # value is []

# count
with open('/etc/passwd') as f:
    for line in f:
        for word in line.strip().split(':'):
            dict_int[word] += 1

# image word_counts is coll.defaultdict(int), it will update count
word_counts = Counter()
with open('/etc/passwd') as f:
    for line in f:
        word_counts.update(line.strip().split(':'))
# print out most common cases
for key, val in (word_counts.most_common(3)):
        print(key, ':', val)