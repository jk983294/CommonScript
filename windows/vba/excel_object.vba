' Application Objects
' Application-wide settings and options.
' Methods that return top-level objects, such as ActiveCell, ActiveSheet...
Set xlapp = CreateObject("Excel.Sheet")
xlapp.Application.Workbooks.Open "C:\test.xls"
Application.Windows("test.xls").Activate
Application.ActiveCell.Font.Bold = True

' Workbook Objects
Workbooks.Close                                                             ' close workbooks
Workbooks.Add                                                               ' Add an empty work book
Workbooks.Open FileName:="Test.xls", ReadOnly:=True                         ' open a workbook
Workbooks("Test.xls").Worksheets("Sheet1").Activate                         ' activate workbooks

' Worksheet Objects
Worksheets(1).Visible = False                                               ' make it invisible
Worksheets("Sheet1").Protect password:=strPassword, scenarios:=True         ' protect an worksheet

' Range Objects
' it represent a cell, a row, a column, or a selection of cells containing one or more continuous blocks of cells
Worksheets("Sheet1").Range("A5").Value = "5235"                             ' put a value in the cell A5
Worksheets("Sheet1").Range("A1:A4").Value = 5                               ' put a value in range of cells
