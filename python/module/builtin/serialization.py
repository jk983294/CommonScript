import cPickle
import datetime
from datetime import date

cPickle.dumps([1, 2, 3, "A", "B", "C"])

now = date.today()
new_date = now + datetime.timedelta(days=6)
cPickle.dumps(new_date)                                     # "cdatetime\ndate\np1\n(S'\\x07\\xe1\\x01\\x0f'\ntRp2\n."

cPickle.dump(new_date, open("/tmp/mydata.txt", "w"))
cPickle.load(open("/tmp/mydata.txt"))
