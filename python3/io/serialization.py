import pickle
import datetime
from datetime import date

"""
dumps/loads             to/from bytes
dump/load               to/from file
"""

pickle.dumps([1, 2, 3, "A", "B", "C"])

now = date.today()
new_date = now + datetime.timedelta(days=6)
s = pickle.dumps(new_date)
print(s)                        # b'\x80\x03cdatetime\ndate\nq\x00C\x04\x07\xe2\n\x0bq\x01\x85q\x02Rq\x03.'
data = pickle.loads(s)
print(data)                     # 2018-10-11

f = open("/tmp/mydata.txt", "wb")
pickle.dump(new_date, f)
pickle.dump('hello', f)
pickle.dump({'Apple', 'Pear', 'Banana'}, f)
f.close()

f = open("/tmp/mydata.txt", "rb")
print(pickle.load(f))
print(pickle.load(f))
print(pickle.load(f))
f.close()
