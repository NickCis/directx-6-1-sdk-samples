# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=ffdonuts - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to ffdonuts - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ffdonuts - Win32 Release" && "$(CFG)" !=\
 "ffdonuts - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "ffdonuts.mak" CFG="ffdonuts - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ffdonuts - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ffdonuts - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "ffdonuts - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "ffdonuts - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\ffdonuts.exe"

CLEAN : 
	-@erase "$(INTDIR)\ddutil.obj"
	-@erase "$(INTDIR)\Dsutil.obj"
	-@erase "$(INTDIR)\ffdonuts.obj"
	-@erase "$(INTDIR)\ffdonuts.res"
	-@erase "$(INTDIR)\input.obj"
	-@erase "$(OUTDIR)\ffdonuts.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/ffdonuts.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ffdonuts.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ffdonuts.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 dsound.lib ddraw.lib dinput.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=dsound.lib ddraw.lib dinput.lib winmm.lib kernel32.lib user32.lib\
 gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib\
 oleaut32.lib uuid.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/ffdonuts.pdb" /machine:I386 /out:"$(OUTDIR)/ffdonuts.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ddutil.obj" \
	"$(INTDIR)\Dsutil.obj" \
	"$(INTDIR)\ffdonuts.obj" \
	"$(INTDIR)\ffdonuts.res" \
	"$(INTDIR)\input.obj"

"$(OUTDIR)\ffdonuts.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ffdonuts - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\ffdonuts.exe"

CLEAN : 
	-@erase "$(INTDIR)\ddutil.obj"
	-@erase "$(INTDIR)\Dsutil.obj"
	-@erase "$(INTDIR)\ffdonuts.obj"
	-@erase "$(INTDIR)\ffdonuts.res"
	-@erase "$(INTDIR)\input.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\ffdonuts.exe"
	-@erase "$(OUTDIR)\ffdonuts.ilk"
	-@erase "$(OUTDIR)\ffdonuts.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/ffdonuts.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ffdonuts.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ffdonuts.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 dsound.lib ddraw.lib dinput.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=dsound.lib ddraw.lib dinput.lib winmm.lib kernel32.lib user32.lib\
 gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib\
 oleaut32.lib uuid.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/ffdonuts.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/ffdonuts.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ddutil.obj" \
	"$(INTDIR)\Dsutil.obj" \
	"$(INTDIR)\ffdonuts.obj" \
	"$(INTDIR)\ffdonuts.res" \
	"$(INTDIR)\input.obj"

"$(OUTDIR)\ffdonuts.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "ffdonuts - Win32 Release"
# Name "ffdonuts - Win32 Debug"

!IF  "$(CFG)" == "ffdonuts - Win32 Release"

!ELSEIF  "$(CFG)" == "ffdonuts - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ddutil.cpp
DEP_CPP_DDUTI=\
	".\ddutil.h"\
	

"$(INTDIR)\ddutil.obj" : $(SOURCE) $(DEP_CPP_DDUTI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ddutil.h

!IF  "$(CFG)" == "ffdonuts - Win32 Release"

!ELSEIF  "$(CFG)" == "ffdonuts - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ffdonuts.c
DEP_CPP_FFDON=\
	".\ddutil.h"\
	".\dsutil.h"\
	".\ffdonuts.h"\
	".\input.h"\
	".\resource.h"\
	{$(INCLUDE)}"\dinput.h"\
	

"$(INTDIR)\ffdonuts.obj" : $(SOURCE) $(DEP_CPP_FFDON) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ffdonuts.h

!IF  "$(CFG)" == "ffdonuts - Win32 Release"

!ELSEIF  "$(CFG)" == "ffdonuts - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ffdonuts.rc
DEP_RSC_FFDONU=\
	".\bangbang.wav"\
	".\bounce.wav"\
	".\c_bang.wav"\
	".\d_bang.wav"\
	".\donuts.bmp"\
	".\donuts.ico"\
	".\gunfire.wav"\
	".\hum.wav"\
	".\level.wav"\
	".\p_bang.wav"\
	".\resource.h"\
	".\rev.wav"\
	".\s_bang.wav"\
	".\shield.wav"\
	".\skid.wav"\
	".\SPLASH.BMP"\
	

"$(INTDIR)\ffdonuts.res" : $(SOURCE) $(DEP_RSC_FFDONU) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\input.c
DEP_CPP_INPUT=\
	".\input.h"\
	".\resource.h"\
	{$(INCLUDE)}"\dinput.h"\
	

"$(INTDIR)\input.obj" : $(SOURCE) $(DEP_CPP_INPUT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\input.h

!IF  "$(CFG)" == "ffdonuts - Win32 Release"

!ELSEIF  "$(CFG)" == "ffdonuts - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\resource.h

!IF  "$(CFG)" == "ffdonuts - Win32 Release"

!ELSEIF  "$(CFG)" == "ffdonuts - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dsutil.c
DEP_CPP_DSUTI=\
	".\dsutil.h"\
	

"$(INTDIR)\Dsutil.obj" : $(SOURCE) $(DEP_CPP_DSUTI) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
