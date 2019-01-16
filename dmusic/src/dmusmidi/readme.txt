DirectMusic MIDI Sample
=======================

Description
-----------
The DirectMusic MIDI sample is a simple MIDI file player.


Path
----
Source: (SDK root)\Samples\Multimedia\Dmusic\Src\DMusMIDI
Executable: (SDK root)\Samples\Multimedia\DMusic\Bin


User's Guide
------------
Load a MIDI file by choosing Open from the File menu. (There is a sample
file in the \Samples\Multimedia\DMusic\Media folder.) You can also load
a file by drag-and-drop. If Autoplay Dropped Files is selected on the
Options menu, a dropped file automatically starts playing.

Once a file is loaded, you can play, pause, or stop it by choosing from
the File menu or the toolbar.

The Options menu provides a choice for adding reverberation to the music,
and several choices for the interface. The time can be displayed in hours,
minutes, and seconds from the start of play, or in music time ticks.

When no music is playing, you can select a port from the Device menu.
Note that to hear music from the "MIDI Out" port, you must have an external
synthesizer attached.


Programming Notes
-----------------
The application demonstrates how to load a MIDI file as a segment, play it,
stop it, and restart it either at the beginning or at the point where it
was stopped. It also shows how to set the reverb property.

The code is written in pure C, so methods are called through pointers to
vtables. For more information, see "Accessing COM Objects by Using C" in
the DirectX help file.
