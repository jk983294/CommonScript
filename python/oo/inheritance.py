class Parent:
    parentAttr = 100
    def __init__(self):
        print "Calling parent constructor"
    def parentMethod(self):
        print 'Calling parent method'
    def setAttr(self, attr):
        Parent.parentAttr = attr
    def getAttr(self):
        print "Parent attribute :", Parent.parentAttr
    def myMethod(self):
        print 'Calling parent method'

class Child(Parent):
    def __init__(self):
        Parent.__init__(self)
        print "Calling child constructor"
    def childMethod(self):
        print 'Calling child method'
    def myMethod(self):                                     # override parent method
        print 'Calling child method'

p = Parent()
c = Child()                                                 # instance of child
c.childMethod()                                             # child calls its method
c.parentMethod()                                            # calls parent's method
c.setAttr(200)                                              # again call parent's method
c.getAttr()                                                 # again call parent's method

print issubclass(Child, Parent)
print isinstance(c, Child)
