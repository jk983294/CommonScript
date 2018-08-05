Dim a As Variant
date1 = Date                                                ' current date
date2 = CDate("Jan 01 2020")                                ' 1/01/2020
date3 = CDate("Feb 02 2021")                                ' 2/02/2021
date4 = DateSerial(2013, 5, 10)
' add
' d - day of the year
' m - month of the year
' y - year of the year
' yyyy - year
' w - weekday
' ww - week
' q - quarter
' h - hour
' n - minute
' s - second
b = DateAdd("yyyy", 1, date2)                               ' 1/01/2021
diff = DateDiff("yyyy", date2, date3)                       ' 1 difference between two specified time intervals

' get part
quarter = DatePart("q", date2)                              ' 1 specific part of the given date
day1 = Day("2013-06-30")                                    ' 30
month1 = Month("2013-06-30")                                ' 6
year1 = Year("2013-06-30")                                  ' 2013
weekday1 = Weekday("2018-08-04", 2)                         ' 6

' format
format0 = FormatDateTime(date4)                             ' 2013/05/10
format1 = FormatDateTime(date4, 1)                          ' 2013年05月10日
format2 = FormatDateTime(date4, 2)                          ' 2013/05/10
format3 = FormatDateTime(date4, 3)                          ' 0:00:00 am only time part 12 hour
format4 = FormatDateTime(date4, 4)                          ' 0:00 24 hour

mn1 = MonthName(1, True)                                    ' Jan
mn2 = MonthName(1, False)                                   ' January
wkdn1 = WeekdayName(1, True)                                ' Mon
wkdn2 = WeekdayName(1, False)                               ' Monday

' check if date
bool1 = IsDate("Nov 03, 1950")                              ' true
bool2 = IsDate(#1/31/2020#)                                 ' true
MsgBox "result is " & wkdn1
