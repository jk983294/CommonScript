from operator import itemgetter
from operator import attrgetter

rows = [
    {'fname': 'Brian', 'lname': 'Jones', 'uid': 1003},
    {'fname': 'David', 'lname': 'Beazley', 'uid': 1002},
    {'fname': 'John', 'lname': 'Cleese', 'uid': 1001},
    {'fname': 'Big', 'lname': 'Jones', 'uid': 1004}
]

print(min(rows, key=itemgetter('uid')))             # {'fname': 'John', 'lname': 'Cleese', 'uid': 1001}
print(max(rows, key=itemgetter('uid')))             # {'fname': 'Big', 'lname': 'Jones', 'uid': 1004}


# also can be used in object
class User:
    def __init__(self, user_id):
        self.user_id = user_id

    def __repr__(self):
        return 'User({})'.format(self.user_id)


users = [User(23), User(3), User(99)]
print(min(users, key=attrgetter('user_id')))                # User(3)
print(max(users, key=attrgetter('user_id')))                # User(99)
