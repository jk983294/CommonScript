import weakref


class MyObject(object):
    def __init__(self):
        pass

    def killed_callback(self):
        print("I am killed")


o = MyObject()
r = weakref.ref(o)
o2 = r()
print(o is o2)

del o, o2
print(r())

o = r()
if o is None:
    # referent has been garbage collected
    print("Object has been de-allocated")
else:
    print("Object is still live!")


def callback():
    print("CALLBACK")


obj = MyObject()
weakref.finalize(obj, callback)
del obj

print("test end")
