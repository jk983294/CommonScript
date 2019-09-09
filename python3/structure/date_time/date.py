import datetime
from datetime import date

# time range
a = datetime.timedelta(days=2, hours=6)
b = datetime.timedelta(hours=4.5)
c = a + b
print(c.days, c.seconds, c.seconds / 3600, c.total_seconds() / 3600)            # 2 37800 10.5 58.5

# datetime
now = date.today()
print(now)                                                                      # 2017-01-09
newDate = now + datetime.timedelta(days=6)                                      # 2017-01-15
print(now.year)
print(now.month)                                                                # 1
print(now.day)
birthday = date(1978, 12, 26)
age = now - birthday
print(age.days)                                                                 # 13894
print(datetime.datetime.strptime('2012-09-20', '%Y-%m-%d'))                     # 2012-09-20 00:00:00


# below function faster 7 times than strptime
def parse_ymd(s):
    year_s, mon_s, day_s = s.split('-')
    return datetime.datetime(int(year_s), int(mon_s), int(day_s))


print(parse_ymd('2012-09-20'))                                                  # 2012-09-20 00:00:00
