import weakref


class CachedSpamManager:
    def __init__(self):
        self._cache = weakref.WeakValueDictionary()

    def get_spam(self, name):
        if name not in self._cache:
            s = Spam._new(name)
            self._cache[name] = s
        else:
            s = self._cache[name]
        return s

    def clear(self):
            self._cache.clear()


class Spam:
    def __init__(self, *args, **kwargs):
        raise RuntimeError("Can't instantiate directly")

    @classmethod
    def _new(cls, name):
        inst = cls.__new__(cls)
        inst.name = name
        return inst


manager = CachedSpamManager()
a = manager.get_spam('foo')
b = manager.get_spam('foo')
print(a is b)                           # True
