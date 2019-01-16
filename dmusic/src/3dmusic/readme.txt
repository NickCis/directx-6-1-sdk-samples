//-----------------------------------------------------------------------------
// 
// Sample Name: 3DMusic Sample
// 
// Copyright © 1998, Microsoft Corp. All Rights Reserved.
//
// GM/GS® Sound Set Copyright ©1996, Roland Corporation U.S.
// 
//-----------------------------------------------------------------------------




Description
===========
  The 3DMusic sample shows how to play a Midi file into a custom DirectSound
  buffer.

Path
====
  Source: Mssdk\Samples\Multimedia\Dmusic\Src\3DMusic

  Executable: Mssdk\Samples\Multimedia\DMusic\Bin

User's Guide
============
  Use the arrow keys to move the music source.
  Use the numeric keypad keys to change the orientation of the listener.
  
  Click File->"Play Stereo Drip" to play random pan drips over the music.
  Click File->Exit to quit the program.

Programming Notes
=================
  The program uses the registry key set up by the DirectX 6.0 SDK setup to
  find the media file path.

  Helper.cpp contains useful functions that set up DirectMusic. These
  functions are called from sound.cpp.

Special Thanks
==============
  This is a modified sample from "Inside DirectX" by Bradley Bargen and Peter Donnelly
  (published by Microsoft Press).
