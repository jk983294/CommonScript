import time
import datetime
from datetime import date

ticks = time.time()
print "Number of ticks since 12:00am, January 1, 1970:", ticks

localtime = time.localtime(ticks)
print "Local current time :", localtime

# format time
print time.time()                                                           # 1481865671.26
print time.asctime(localtime)                                               # Thu Dec 15 22:28:58 2016
print time.ctime()                                                          # Fri Dec 16 00:17:46 2016
print time.gmtime()                                                         # time.struct_time(tm_year=2016, tm_mon=12, tm_mday=16, tm_hour=5, tm_min=17, tm_sec=46, tm_wday=4, tm_yday=351, tm_isdst=0)
print time.localtime()                                                      # time.struct_time(tm_year=2016, tm_mon=12, tm_mday=16, tm_hour=0, tm_min=17, tm_sec=46, tm_wday=4, tm_yday=351, tm_isdst=0)
print time.mktime((2009, 2, 17, 17, 3, 38, 1, 48, 0))                       # 1234908218.0
print time.strftime("%b %d %Y %H:%M:%S", time.localtime())                  # Dec 16 2016 00:17:46
print time.strftime("%b %d %Y %H:%M:%S", time.gmtime())                     # Dec 16 2016 05:17:50
print time.strptime("Dec 16 2016 00:17:46", "%b %d %Y %H:%M:%S")            # time.struct_time(tm_year=2016, tm_mon=12, tm_mday=16, tm_hour=0, tm_min=17, tm_sec=46, tm_wday=4, tm_yday=351, tm_isdst=-1)

# measure process time
t0 = time.clock()
time.sleep(2)
t1 = time.clock()
print t1 - t0, "seconds process time"

# measure wall time
t0 = time.time()
time.sleep(2)
t1 = time.time()
print t1 - t0, "seconds wall time"

# datetime
now = date.today()
print now                                                                   # 2017-01-09
newDate = now + datetime.timedelta(days=6)                                  # 2017-01-15
print now.month                                                             # 1
birthday = date(1978, 12, 26)
age = now - birthday
print age.days                                                              # 13894
