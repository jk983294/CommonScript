import cPickle
import datetime

cPickle.dumps([1, 2, 3, "A", "B", "C"])

newdate = now + datetime.timedelta(days=6)
cPickle.dumps(newdate)                                      # "cdatetime\ndate\np1\n(S'\\x07\\xe1\\x01\\x0f'\ntRp2\n."

cPickle.dump(newdate, open("/tmp/mydata.txt", "w"))
cPickle.load(open("/tmp/mydata.txt"))
