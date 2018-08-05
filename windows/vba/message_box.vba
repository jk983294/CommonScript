Function MessageBoxQuery()
    ' Message Box with just prompt message
    MsgBox ("Welcome")

    ' Message Box with title, yes no and cancel Butttons
    a = MsgBox("Do you like blue color?", 3, "Choose options")
    ' Assume that you press No Button
    MsgBox ("The Value of a is " & a)
End Function
