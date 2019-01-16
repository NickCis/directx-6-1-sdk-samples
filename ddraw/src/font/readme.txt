//-----------------------------------------------------------------------------
// 
// Sample Name: Font Sample
// 
// Copyright (c) 1998 Microsoft Corporation. All rights reserved.
// 
//-----------------------------------------------------------------------------


Description
===========
  This sample program shows how to directly lock and access video memory, using
  text generated from a GDI font.  There are much better ways to draw text into
  a DirectDrawSurface, and the only point of this sample is to show exactly how
  to lock and access the video memory directly.


Path
====
  Source: Mssdk\Samples\Multimedia\DDraw\Src\Font

  Executable: Mssdk\Samples\Multimedia\DDraw\Bin

User's Guide
============
  The program repeatedly updates a text string in the Arial font and moves it 
  randomly about the screen. No user input is required. Quit by closing the 
  window.

Programming Notes
=================
  The program creates a font in a memory device context and a DIB section, and 
  uses them to get access to the pixels once GDI has drawn them. The text 
  bitmap is then put on the primary surface with a straight memory copy. It 
  could easily be moved instead to an off-screen surface which could then be 
  blitted as needed, transparently or not. 

