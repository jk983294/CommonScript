#!/opt/anaconda3/bin/python
import pyinotify


class EventHandler(pyinotify.ProcessEvent):
    def process_IN_CREATE(self, event):
        print("create:", event.pathname)

    def process_IN_DELETE(self, event):
        print("delete:", event.pathname)

    def process_IN_CLOSE_WRITE(self, event):
        print("close write:", event.pathname)

    def process_IN_MOVED_TO(self, event):
        print("move:", event.pathname)


wm = pyinotify.WatchManager()
mask = pyinotify.IN_DELETE | pyinotify.IN_CREATE | pyinotify.IN_CLOSE_WRITE | pyinotify.IN_MOVED_TO    # watched events
handler = EventHandler()
notifier = pyinotify.Notifier(wm, handler)
wdd = wm.add_watch('/tmp', mask, rec=True)
notifier.loop()
