Function OnErrorDemo()
    On Error GoTo ErrorHandler      ' Enable error-handling routine.
    Dim x, y, z As Integer
    x = 50
    y = 0
    z = x / y                       ' Divide by ZERO Error Raises
    z = x * y

    ErrorHandler:                   ' Error-handling routine.
        Select Case Err.Number      ' Evaluate error number.
            Case 10                 ' Divide by zero error
                MsgBox ("You attempted to divide by zero!")
             Case Else
                MsgBox "UNKNOWN ERROR  - Error# " & Err.Number & " : " & Err.Description
        End Select
        Resume Next
End Function
