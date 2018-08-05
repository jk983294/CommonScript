str1 = "string"                                 ' Only Alphabets
str2 = "132.45"                                 ' Only Numbers
str3 = "!@#$;*"                                 ' Only Special Characters
str4 = "Asc23@#"                                ' Has all the above


Var = "Microsoft VBScript"
' the first occurrence position of one string within another string, from left to right
InStr(Var, "VB")                                ' 11
InStr(1, Var, "s")                              ' 6
' the first occurrence position of one string within another string, from right to left
InStrRev(var, "s", 10)                          ' 6
LCase(var)                                      ' "microsoft vbscript"
UCase(var)                                      ' "MICROSOFT VBSCRIPT"
' substr
Left(var, 2)                                    ' "Mi"
Right(var, 2)                                   ' "pt"
Mid(var, 2)                                     ' "icrosoft VBScript"
Mid(var, 2, 5)                                  ' "icros"
' replace
Replace(var,"VB","vb")                          ' "Microsoft vbScript"
Replace(var,"o", "#", 1)                        ' "Micr#s#ft VBScript"
Replace(var,"o", "#", 1, 1)                     ' "Micr#soft VBScript"
' reverse
StrReverse("123.45")                            ' "54.321"
' compare
StrComp("a", "a")                               ' 0
StrComp("a", "b")                               ' -1
StrComp("b", "a")                               ' 1
' beautify
LTrim(var)
RTrim(var)
Trim(var)
' misc
Len(String)                                     ' 18
"Microsoft" & Space(2) & "VBScript"             ' "Microsoft  VBScript"
String(3, "$")                                  ' "$$$"
