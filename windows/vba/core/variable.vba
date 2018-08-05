' Const <<constant_name>> As <<constant_type>> = <<constant_value>>
Const MyInteger As Integer = 42
Const myDate As Date = #2/2/2020#
Const myDay As String = "Sunday"

' Dim <<variable_name>> As <<variable_type>>

Dim password As String
password = "Admin#1"

Dim num As Integer
num = 1234

Dim BirthDay As Date
BirthDay = DateValue("30 / 10 / 2020")

' Data Types
' Byte                                  0 to 255
' Integer                               -32,768 to 32,767
' Long                                  -2,147,483,648 to 2,147,483,648
' Single                                -3.402823E+38 to -1.401298E-45 for negative values
'                                       1.401298E-45 to 3.402823E+38 for positive values
' Double                                -1.79769313486232e+308 to -4.94065645841247E-324 for negative values
'                                       4.94065645841247E-324 to 1.79769313486232e+308 for positive values
' Currency                              -922,337,203,685,477.5808 to 922,337,203,685,477.5807
' Decimal                               +/- 79,228,162,514,264,337,593,543,950,335 if no decimal is use
'                                       +/- 7.9228162514264337593543950335 (28 decimal places)
' String (fixed length)                 1 to 65,400 characters
' String (variable length)              0 to 2 billion characters
' Date                                  January 1, 100 to December 31, 9999
' Boolean                               True or False
' Object                                Any embedded object
' Variant (numeric)                     Any value as large as double
' Variant (text)                        Same as variable-length string
