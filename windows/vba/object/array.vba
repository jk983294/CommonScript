arr0 = Array("apple", "Orange", "Grapes")
Dim arr1()
Dim arr2(5)                                         ' it actually contains 6 elements from 0 to 5

' resize
ReDim arr1(3)
ReDim Preserve arr1(7)                              ' preserve old array content

' assign
arr2(0) = "0"
arr2(1) = 1
arr2(2) = 100                                       ' Number
arr2(3) = 2.45                                      ' Decimal Number
arr2(4) = #10/7/2013#                               ' Date
arr2(5) = #12:45:00 PM#                             ' Time

' multi-dimensional arrays
Dim arr3(1, 1) As Variant
arr3(0, 0) = 0
arr3(0, 1) = 1
arr3(1, 0) = 2
arr3(1, 1) = 3

' operation
lb1 = LBound(arr0)                                  ' 0
lb2 = LBound(arr3, 1)                               ' 0
lb3 = LBound(arr3, 2)                               ' 0

ub1 = UBound(arr0)                                  ' 2
ub2 = UBound(arr3, 1)                               ' 1
ub3 = UBound(arr3, 2)                               ' 1

splited = Split("Red $ Blue $ Yellow", "$")         ' ["Red","Blue","Yellow"]
joined = Join(splited, "$")                         ' "Red $ Blue $ Yellow"
filtered = Filter(splited, "B")                     ' ["Blue"]

bool1 = IsArray(splited)                            ' True
bool2 = IsArray(joined)                             ' False

' erase
' Fixed numeric array, each element in an array is reset to Zero
' Fixed string array, each element in an array is reset to Zero length " "
' Array of objects, each element in an array is reset to special value Nothing
Erase arr0

' iterate
For i = 0 To UBound(splited)
    MsgBox splited(i)
Next

For Each x In filtered
    MsgBox ("The Filter result: " & x)
Next
