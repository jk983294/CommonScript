' using FSO, need to navigate to Tools → References and check "Microsoft Scripting RunTime" enabled
Function fn_write_to_text()
    Dim FilePath As String
    Dim CellData As String
    Dim LastCol As Long
    Dim LastRow As Long

    Dim fso As FileSystemObject
    Set fso = New FileSystemObject
    Dim stream As TextStream

    LastCol = ActiveSheet.UsedRange.Columns.Count
    LastRow = ActiveSheet.UsedRange.Rows.Count
    Set stream = fso.OpenTextFile("E:\result.txt", ForWriting, True)

    CellData = ""
    For i = 1 To LastRow
        For j = 1 To LastCol
            CellData = Trim(ActiveCell(i, j).Value)
            stream.WriteLine "The Value at location (" & i & "," & j & ")" & CellData
        Next j
    Next i

    stream.Close
    MsgBox ("Job Done")
End Function

' do not use FSO'
Function fn_write_to_text1()
    Dim FilePath As String
    Dim CellData As String
    Dim LastCol As Long
    Dim LastRow As Long

    LastCol = ActiveSheet.UsedRange.Columns.Count
    LastRow = ActiveSheet.UsedRange.Rows.Count

    FilePath = "E:\result1.txt"
    Open FilePath For Output As #2

    CellData = ""
    For i = 1 To LastRow
        For j = 1 To LastCol
            CellData = "The Value at location (" & i & "," & j & ")" & Trim(ActiveCell(i, j).Value)
            Write #2, CellData
        Next j
    Next i

    Close #2
    MsgBox ("Job Done")
End Function
