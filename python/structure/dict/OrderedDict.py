from collections import OrderedDict

mydict = OrderedDict()
mydict["first"] = 33
mydict["second"] = 87
mydict["third"] = 99
mydict["fourth"] = 1010

for key, value in mydict.iteritems():
    print key, value

key, value = mydict.popitem()               # last item ('fourth', 1010), OrderedDict([('first', 33), ('second', 87), ('third', 99)])
