time1 = Now()                           ' 04/08/2018 3:04:09 PM
time2 = Time()                          ' 3:29:15 PM
time3 = TimeSerial(20, 1, 2)            ' 8:01:02 PM
timer1 = Timer()                        ' 56753.4 the number of seconds since 00:00 AM

' convert string to time object
time4 = TimeValue("2:30:58")            ' 2:30:58 AM

' get part
h1 = Hour("3:13:45 PM")                 ' 15
h2 = Hour("23:13:45")                   ' 23
m1 = Minute("3:13:45 PM")               ' 13
m2 = Minute("23:13:45")                 ' 13
s1 = Second("3:13:45 PM")               ' 45
s2 = Second("23:13:45")                 ' 45
