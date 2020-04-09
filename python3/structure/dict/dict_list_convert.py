#!/usr/bin/python3

dic = {"Orange": 110, "Apple": 240}

l = sorted(dic.items(), key=lambda x: x[0], reverse=True)
print(l)

l1 = [('Orange', 110), ('Apple', 240)]  # list of tuple
dic1 = dict(l1)
print(dic1)

l1_ = [['Orange', 110], ['Apple', 240]]  # list of list
dic1_ = dict(l1_)
print(dic1_)

l2 = ['Orange', 'Apple']
l3 = [110, 240]
dic2 = dict(zip(l2, l3))
print(dic2)
