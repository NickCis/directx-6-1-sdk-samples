# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=rmenum - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to rmenum - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "rmenum - Win32 Release" && "$(CFG)" != "rmenum - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "rmenum.mak" CFG="rmenum - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "rmenum - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "rmenum - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "rmenum - Win32 Release"

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

ALL : "$(OUTDIR)\rmenum.exe"

CLEAN : 
	-@erase "$(INTDIR)\rmenum.obj"
	-@erase "$(INTDIR)\rmenum.res"
	-@erase "$(INTDIR)\rmerror.obj"
	-@erase "$(OUTDIR)\rmenum.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/rmenum.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/rmenum.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/rmenum.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ddraw.lib d3drm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=ddraw.lib d3drm.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/rmenum.pdb" /machine:I386 /out:"$(OUTDIR)/rmenum.exe" 
LINK32_OBJS= \
	"$(INTDIR)\rmenum.obj" \
	"$(INTDIR)\rmenum.res" \
	"$(INTDIR)\rmerror.obj"

"$(OUTDIR)\rmenum.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "rmenum - Win32 Debug"

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

ALL : "$(OUTDIR)\rmenum.exe"

CLEAN : 
	-@erase "$(INTDIR)\rmenum.obj"
	-@erase "$(INTDIR)\rmenum.res"
	-@erase "$(INTDIR)\rmerror.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\rmenum.exe"
	-@erase "$(OUTDIR)\rmenum.ilk"
	-@erase "$(OUTDIR)\rmenum.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/rmenum.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/rmenum.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/rmenum.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 ddraw.lib d3drm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=ddraw.lib d3drm.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/rmenum.pdb" /debug /machine:I386 /out:"$(OUTDIR)/rmenum.exe" 
LINK32_OBJS= \
	"$(INTDIR)\rmenum.obj" \
	"$(INTDIR)\rmenum.res" \
	"$(INTDIR)\rmerror.obj"

"$(OUTDIR)\rmenum.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "rmenum - Win32 Release"
# Name "rmenum - Win32 Debug"

!IF  "$(CFG)" == "rmenum - Win32 Release"

!ELSEIF  "$(CFG)" == "rmenum - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\rmenum.cpp
DEP_CPP_RMENU=\
	"..\..\..\..\..\INCLUDE\d3dcaps.h"\
	"..\..\..\..\..\INCLUDE\d3drmdef.h"\
	"..\..\..\..\..\INCLUDE\d3drmobj.h"\
	"..\..\..\..\..\INCLUDE\d3dtypes.h"\
	"..\..\..\..\..\INCLUDE\d3dvec.inl"\
	".\rmenum.h"\
	".\rmerror.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	

"$(INTDIR)\rmenum.obj" : $(SOURCE) $(DEP_CPP_RMENU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\rmenum.h

!IF  "$(CFG)" == "rmenum - Win32 Release"

!ELSEIF  "$(CFG)" == "rmenum - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\rmenum.rc
DEP_RSC_RMENUM=\
	".\d3d.ico"\
	".\rmenum.h"\
	

"$(INTDIR)\rmenum.res" : $(SOURCE) $(DEP_RSC_RMENUM) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\rmerror.c
DEP_CPP_RMERR=\
	"..\..\..\..\..\INCLUDE\d3dcaps.h"\
	"..\..\..\..\..\INCLUDE\d3drmdef.h"\
	"..\..\..\..\..\INCLUDE\d3drmobj.h"\
	"..\..\..\..\..\INCLUDE\d3dtypes.h"\
	"..\..\..\..\..\INCLUDE\d3dvec.inl"\
	".\rmerror.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3drm.h"\
	{$(INCLUDE)}"\d3drmwin.h"\
	

"$(INTDIR)\rmerror.obj" : $(SOURCE) $(DEP_CPP_RMERR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\rmerror.h

!IF  "$(CFG)" == "rmenum - Win32 Release"

!ELSEIF  "$(CFG)" == "rmenum - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
