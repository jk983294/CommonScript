from operator import attrgetter
from random import random

sorted([3, 2, 5 ,4, 7, 1])                                          # [1, 2, 3, 4, 5, 7]
sorted(('Zane', 'Bob', 'Janet'))                                    # ['Bob', 'Janet', 'Zane']
sorted({1:'a', 2:'b', 3:'c'})                                       # [1, 2, 3]

# reverse sort
sorted([3, 2, 5 ,4, 7, 1], reverse = True)                          # [7, 5, 4, 3, 2, 1]

# sort object
class Person(object):
    def __init__(self, name, age):
        self.name = name
        self.age = age
    def __repr__(self):
        return "<name: %s, age: %s>" % (self.name, self.age)

def byName_key(person):
    return person.name

jack = Person('Jack', 19)
adam = Person('Adam', 43)
becky = Person('Becky', 11)
people = [jack, adam, becky]

sorted(people)                                                      # [<name: Adam, age: 43>, <name: Jack, age: 19>, <name: Becky, age: 11>]
sorted(people, key = byName_key)                                    # [<name: Adam, age: 43>, <name: Becky, age: 11>, <name: Jack, age: 19>]

# using attrgetter
getName = attrgetter('name')
getName(jack)                                                       # 'Jack'
sorted(people, key = attrgetter('name'))                            # [<name: Adam, age: 43>, <name: Becky, age: 11>, <name: Jack, age: 19>]


# shuffle
def randomOrder_key(element):
    return random()
sorted(people, key = randomOrder_key)
