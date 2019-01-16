//-----------------------------------------------------------------------------
// 
// Sample Name: FSWindow
// 
// Copyright (c) 1998 Microsoft Corporation. All rights reserved.
// 
//-----------------------------------------------------------------------------

Description
===========
  This sample shows how you can bring up a dialog box, or any other type of
  window, while your application is running in DirectDraw's full-screen
  exclusive mode. Even devices that are non-GDI are detected and supported by
  creating a bitmap out of their window contents and then BLTing that to the
  device.

Path
====
  Source: Mssdk\Samples\Multimedia\DDraw\Src\FSWindow

  Executable: Mssdk\Samples\Multimedia\DDraw\Bin

User's Guide
============
  If you have more than one device, the sample starts by displaying a dialog
  box so that you can select which device to run the sample on. It then
  switches to full-screen exclusive mode and displays a dialog box and the
  mouse cursor.

  Click on the Cancel or OK button to close the dialog and hide the mouse
  cursor.  Press F1 to bring the dialog and cursor back.  Press Esc to exit
  the program when the dialog is no longer displayed.

Programming Notes
=================
  Most of the important code is in the Fswindow.cpp file.

  The sample uses just the dynamic content mode, which constantly refreshes the
  dialog box to show which controls have focus, text in the edit field, and so
  on. The static content mode consumes less CPU time and would be good for
  pop-up windows that display help messages, for example.

  It is important to understand that the "content" window can be any type of
  window. It could be an HTML Help window, or a window with a rich edit control
  to display formatted text. The window does not need to have a square clipping
  region; it could have a complex clipping region that fits the shape of the
  window you want to display.

