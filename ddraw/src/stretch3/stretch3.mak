# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=stretch3 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to stretch3 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "stretch3 - Win32 Release" && "$(CFG)" !=\
 "stretch3 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "stretch3.mak" CFG="stretch3 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "stretch3 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "stretch3 - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "stretch3 - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "stretch3 - Win32 Release"

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

ALL : "$(OUTDIR)\stretch3.exe"

CLEAN : 
	-@erase "$(INTDIR)\ddmm.obj"
	-@erase "$(INTDIR)\ddutil2.obj"
	-@erase "$(INTDIR)\stretch.obj"
	-@erase "$(INTDIR)\stretch.res"
	-@erase "$(OUTDIR)\stretch3.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)/stretch3.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/stretch.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/stretch3.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ddraw.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=ddraw.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/stretch3.pdb" /machine:I386 /out:"$(OUTDIR)/stretch3.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ddmm.obj" \
	"$(INTDIR)\ddutil2.obj" \
	"$(INTDIR)\stretch.obj" \
	"$(INTDIR)\stretch.res"

"$(OUTDIR)\stretch3.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "stretch3 - Win32 Debug"

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

ALL : "$(OUTDIR)\stretch3.exe"

CLEAN : 
	-@erase "$(INTDIR)\ddmm.obj"
	-@erase "$(INTDIR)\ddutil2.obj"
	-@erase "$(INTDIR)\stretch.obj"
	-@erase "$(INTDIR)\stretch.res"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\stretch3.exe"
	-@erase "$(OUTDIR)\stretch3.ilk"
	-@erase "$(OUTDIR)\stretch3.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)/stretch3.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/stretch.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/stretch3.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 ddraw.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=ddraw.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/stretch3.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/stretch3.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ddmm.obj" \
	"$(INTDIR)\ddutil2.obj" \
	"$(INTDIR)\stretch.obj" \
	"$(INTDIR)\stretch.res"

"$(OUTDIR)\stretch3.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "stretch3 - Win32 Release"
# Name "stretch3 - Win32 Debug"

!IF  "$(CFG)" == "stretch3 - Win32 Release"

!ELSEIF  "$(CFG)" == "stretch3 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ddmm.cpp
DEP_CPP_DDMM_=\
	"..\..\include\ddmm.h"\
	"..\..\include\multimon.h"\
	

"$(INTDIR)\ddmm.obj" : $(SOURCE) $(DEP_CPP_DDMM_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ddutil2.cpp
DEP_CPP_DDUTI=\
	"..\..\include\ddutil2.h"\
	

"$(INTDIR)\ddutil2.obj" : $(SOURCE) $(DEP_CPP_DDUTI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\resource.h

!IF  "$(CFG)" == "stretch3 - Win32 Release"

!ELSEIF  "$(CFG)" == "stretch3 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\stretch.cpp
DEP_CPP_STRET=\
	"..\..\include\ddmm.h"\
	"..\..\include\ddutil2.h"\
	

"$(INTDIR)\stretch.obj" : $(SOURCE) $(DEP_CPP_STRET) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\stretch.rc
DEP_RSC_STRETC=\
	".\DirectX.ico"\
	".\DONUT.BMP"\
	

"$(INTDIR)\stretch.res" : $(SOURCE) $(DEP_RSC_STRETC) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
