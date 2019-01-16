# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=DSStream - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to DSStream - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DSStream - Win32 Release" && "$(CFG)" !=\
 "DSStream - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "DSStream.mak" CFG="DSStream - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DSStream - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DSStream - Win32 Debug" (based on "Win32 (x86) Application")
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
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "DSStream - Win32 Release"

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

ALL : "$(OUTDIR)\DSStream.exe"

CLEAN : 
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\Dsstream.obj"
	-@erase "$(INTDIR)\Dsstream.res"
	-@erase "$(INTDIR)\Dstrenum.obj"
	-@erase "$(INTDIR)\Dstrwave.obj"
	-@erase "$(INTDIR)\notify.obj"
	-@erase "$(OUTDIR)\DSStream.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/DSStream.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Dsstream.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DSStream.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 dsound.lib winmm.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=dsound.lib winmm.lib comctl32.lib kernel32.lib user32.lib\
 gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib\
 oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/DSStream.pdb" /machine:I386\
 /out:"$(OUTDIR)/DSStream.exe" 
LINK32_OBJS= \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\Dsstream.obj" \
	"$(INTDIR)\Dsstream.res" \
	"$(INTDIR)\Dstrenum.obj" \
	"$(INTDIR)\Dstrwave.obj" \
	"$(INTDIR)\notify.obj"

"$(OUTDIR)\DSStream.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DSStream - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DSStream"
# PROP BASE Intermediate_Dir "DSStream"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\DSStream.exe"

CLEAN : 
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\Dsstream.obj"
	-@erase "$(INTDIR)\Dsstream.res"
	-@erase "$(INTDIR)\Dstrenum.obj"
	-@erase "$(INTDIR)\Dstrwave.obj"
	-@erase "$(INTDIR)\notify.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\DSStream.exe"
	-@erase "$(OUTDIR)\DSStream.ilk"
	-@erase "$(OUTDIR)\DSStream.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/DSStream.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Dsstream.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DSStream.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 dsound.lib winmm.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=dsound.lib winmm.lib comctl32.lib kernel32.lib user32.lib\
 gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib\
 oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/DSStream.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/DSStream.exe" 
LINK32_OBJS= \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\Dsstream.obj" \
	"$(INTDIR)\Dsstream.res" \
	"$(INTDIR)\Dstrenum.obj" \
	"$(INTDIR)\Dstrwave.obj" \
	"$(INTDIR)\notify.obj"

"$(OUTDIR)\DSStream.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "DSStream - Win32 Release"
# Name "DSStream - Win32 Debug"

!IF  "$(CFG)" == "DSStream - Win32 Release"

!ELSEIF  "$(CFG)" == "DSStream - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\notify.c
DEP_CPP_NOTIF=\
	".\debug.h"\
	".\dsstream.h"\
	

"$(INTDIR)\notify.obj" : $(SOURCE) $(DEP_CPP_NOTIF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dsstream.c
DEP_CPP_DSSTR=\
	".\debug.h"\
	".\dsstream.h"\
	

"$(INTDIR)\Dsstream.obj" : $(SOURCE) $(DEP_CPP_DSSTR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dsstream.rc
DEP_RSC_DSSTRE=\
	".\icon2.ico"\
	".\icon3.ico"\
	

"$(INTDIR)\Dsstream.res" : $(SOURCE) $(DEP_RSC_DSSTRE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dstrenum.c
DEP_CPP_DSTRE=\
	".\debug.h"\
	".\dsstream.h"\
	

"$(INTDIR)\Dstrenum.obj" : $(SOURCE) $(DEP_CPP_DSTRE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dstrwave.c
DEP_CPP_DSTRW=\
	".\debug.h"\
	".\dsstream.h"\
	

"$(INTDIR)\Dstrwave.obj" : $(SOURCE) $(DEP_CPP_DSTRW) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\debug.c
DEP_CPP_DEBUG=\
	".\debug.h"\
	

"$(INTDIR)\debug.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
