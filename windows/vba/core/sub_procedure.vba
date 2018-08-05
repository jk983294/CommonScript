' sub do not return a value
' sub can be called without call keyword
' you cannot make a direct call to a sub procedure from the excel worksheet, it can be called from function

Sub Area(x As Double, y As Double)
   MsgBox x * y
End Sub

Function findArea(Length As Double, Width As Variant)
   area Length, Width               ' To Calculate Area 'area' sub proc is called
End Function
