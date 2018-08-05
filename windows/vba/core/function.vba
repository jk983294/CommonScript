Function findArea(Length As Double, Optional Width As Variant)
   If IsMissing(Width) Then
      findArea = Length * Length
   Else
      findArea = Length * Width
   End If
End Function


Sub test_function()
      MsgBox ("result: " & findArea(1.2))
      MsgBox ("result: " & findArea(1.2, 1.4))
End Sub
