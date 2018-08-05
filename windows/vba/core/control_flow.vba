If x > y Then
    MsgBox "X is Greater than Y"
ElseIf y > x Then
    Msgbox "Y is Greater than X"
Else
    Msgbox "X and Y are EQUAL"
End If


Select Case MyVar
    Case 1
        MsgBox "The Number is the Least Composite Number"
    Case 2
        MsgBox "The Number is the only Even Prime Number"
    Case 3
        MsgBox "The Number is the Least Odd Prime Number"
    Case Else
        MsgBox "Unknown Number"
End Select


a = 10
For i = 0 To a Step 2
    MsgBox "The value is i is : " & i
Next

fruits = Array("apple", "orange", "cherries")
Dim fruitnames As Variant
For Each item In fruits
    MsgBox "The value is " & item
Next


Dim counter :  counter = 10
While counter < 15
    counter = counter + 1
    msgbox "The Current Value of the counter is : " & counter
Wend


Do While i < 5
    i = i + 1
    msgbox "The value of i is : " & i
Loop


i = 10
Do
    i = i + 1
    MsgBox "The value of i is : " & i
Loop While i < 3


Do Until i>15                                   ' condition is False, then loop will be executed
    i = i + 1
    msgbox ("The value of i is : " & i)
Loop

Do
    i = i + 1
    msgbox "The value of i is : " & i
Loop Until i<15


For i = 0 To a Step 2
    MsgBox ("The value is i is : " & i)
    If i = 4 Then
        i = i * 10                              ' this is executed only if i=4
        MsgBox ("The value is i is : " & i)
        Exit For 'Exited when i=4
    End If
Next


i = 0
Do While i <= 100
    If i > 10 Then
        Exit Do                                 ' loop Exits if i>10
    End If
    MsgBox ("The Value of i is : " & i)
    i = i + 2
Loop
