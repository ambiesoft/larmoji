; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
LastClass=CChildView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "larmoji.h"
LastPage=0

ClassCount=7
Class1=CLarmojiApp
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=6
Resource1=IDD_DIALOG_INPUT (Japanese)
Class2=CChildView
Class5=CMainToolBar
Class6=CFontNameComboBox
Resource2=IDR_MAINFRAME
Class7=CInputDialog
Resource3=IDD_ABOUTBOX
Resource4=IDR_MAINFRAME (Japanese)
Resource5=IDD_ABOUTBOX (Japanese)
Resource6=IDD_DIALOG_INPUT

[CLS:CLarmojiApp]
Type=0
HeaderFile=larmoji.h
ImplementationFile=larmoji.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=W
BaseClass=CWnd 
VirtualFilter=WC
LastObject=ID_EDIT_COPY

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=W
LastObject=ID_EDIT_PASTE
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=larmoji.cpp
ImplementationFile=larmoji.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_APP_EXIT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=IDM_MENU_INPUTSTRING
Command6=IDM_FONT_NEXT
Command7=IDM_FONT_PREV
Command8=ID_VIEW_TOOLBAR
Command9=ID_VIEW_STATUS_BAR
Command10=IDM_WATCH_CLIPBOARD
Command11=IDM_WINDOW_ALWAYSTOP
Command12=ID_APP_ABOUT
CommandCount=12

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=IDM_FONT_NEXT
Command10=IDM_FONT_PREV
Command11=ID_EDIT_CUT
Command12=ID_EDIT_UNDO
CommandCount=12

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_EDIT_PASTE
Command3=IDM_WATCH_CLIPBOARD
Command4=IDM_WINDOW_ALWAYSTOP
Command5=IDP_FONTNAME
Command6=IDM_FONT_PREV
Command7=IDM_FONT_NEXT
Command8=IDM_MENU_INPUTSTRING
CommandCount=8

[CLS:CMainToolBar]
Type=0
HeaderFile=MainToolBar.h
ImplementationFile=MainToolBar.cpp
BaseClass=CToolBarCtrl
Filter=W

[CLS:CFontNameComboBox]
Type=0
HeaderFile=FontNameComboBox.h
ImplementationFile=FontNameComboBox.cpp
BaseClass=CComboBoxEx
Filter=W
VirtualFilter=cWC
LastObject=CFontNameComboBox

[DLG:IDD_DIALOG_INPUT]
Type=1
Class=CInputDialog
ControlCount=3
Control1=IDC_EDIT_TEXT,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[CLS:CInputDialog]
Type=0
HeaderFile=InputDialog.h
ImplementationFile=InputDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_TEXT

[TB:IDR_MAINFRAME (Japanese)]
Type=1
Command1=ID_FILE_NEW
Command2=ID_EDIT_PASTE
Command3=IDM_WATCH_CLIPBOARD
Command4=IDM_WINDOW_ALWAYSTOP
Command5=IDP_FONTNAME
Command6=IDM_FONT_PREV
Command7=IDM_FONT_NEXT
Command8=IDM_MENU_INPUTSTRING
CommandCount=8

[MNU:IDR_MAINFRAME (Japanese)]
Type=1
Command1=ID_FILE_NEW
Command2=ID_APP_EXIT
Command3=ID_EDIT_PASTE
Command4=IDM_MENU_INPUTSTRING
Command5=IDM_FONT_NEXT
Command6=IDM_FONT_PREV
Command7=ID_VIEW_TOOLBAR
Command8=ID_VIEW_STATUS_BAR
Command9=IDM_WATCH_CLIPBOARD
Command10=IDM_WINDOW_ALWAYSTOP
Command11=ID_APP_ABOUT
CommandCount=11

[ACL:IDR_MAINFRAME (Japanese)]
Type=1
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=IDM_FONT_NEXT
Command10=IDM_FONT_PREV
Command11=ID_EDIT_CUT
Command12=ID_EDIT_UNDO
CommandCount=12

[DLG:IDD_ABOUTBOX (Japanese)]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DIALOG_INPUT (Japanese)]
Type=1
ControlCount=3
Control1=IDC_EDIT_TEXT,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

