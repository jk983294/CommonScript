' Worksheet Events
' right-click on the sheet tab and choosing 'view code'
' user can select each one of those worksheets and choose "WorkSheet" from the drop down to get the list of all supported Worksheet events
' supported
Private Sub Worksheet_Activate()
Private Sub Worksheet_BeforeDoubleClick(ByVal Target As Range, Cancel As Boolean)
Private Sub Worksheet_BeforeRightClick(ByVal Target As Range, Cancel As Boolean)
Private Sub Worksheet_Calculate()
Private Sub Worksheet_Change(ByVal Target As Range)
Private Sub Worksheet_Deactivate()
Private Sub Worksheet_FollowHyperlink(ByVal Target As Hyperlink)
Private Sub Worksheet_SelectionChange(ByVal Target As Range)

' example
Private Sub Worksheet_BeforeDoubleClick(ByVal Target As Range, Cancel As Boolean)
   MsgBox "Before Double Click"
End Sub


' Workbook Events
' selecting the 'ThisWorkbook' in VBAProject and selecting 'workbook' from the drop-down
Private Sub Workbook_AddinUninstall()
Private Sub Workbook_BeforeClose(Cancel As Boolean)
Private Sub Workbook_BeforePrint(Cancel As Boolean)
Private Sub Workbook_BeforeSave(ByVal SaveAsUI As Boolean, Cancel As Boolean)
Private Sub Workbook_Deactivate()
Private Sub Workbook_NewSheet(ByVal Sh As Object)
Private Sub Workbook_Open()
Private Sub Workbook_SheetActivate(ByVal Sh As Object)
Private Sub Workbook_SheetBeforeDoubleClick(ByVal Sh As Object, ByVal Target As Range, Cancel As Boolean)
Private Sub Workbook_SheetBeforeRightClick(ByVal Sh As Object, ByVal Target As Range, Cancel As Boolean)
Private Sub Workbook_SheetCalculate(ByVal Sh As Object)
Private Sub Workbook_SheetChange(ByVal Sh As Object, ByVal Target As Range)
Private Sub Workbook_SheetDeactivate(ByVal Sh As Object)
Private Sub Workbook_SheetFollowHyperlink(ByVal Sh As Object, ByVal Target As Hyperlink)
Private Sub Workbook_SheetSelectionChange(ByVal Sh As Object, ByVal Target As Range)
Private Sub Workbook_WindowActivate(ByVal Wn As Window)
Private Sub Workbook_WindowDeactivate(ByVal Wn As Window)
Private Sub Workbook_WindowResize(ByVal Wn As Window)

' example
Private Sub Workbook_NewSheet(ByVal Sh As Object)
   MsgBox "New Sheet Created Successfully"
End Sub
