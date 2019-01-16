# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=flare - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to flare - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "flare - Win32 Release" && "$(CFG)" != "flare - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "flare.mak" CFG="flare - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "flare - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "flare - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "flare - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "flare - Win32 Release"

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

ALL : "$(OUTDIR)\flare.exe"

CLEAN : 
	-@erase "$(INTDIR)\flare.obj"
	-@erase "$(INTDIR)\winmain.obj"
	-@erase "$(INTDIR)\winmain.res"
	-@erase "$(OUTDIR)\flare.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)/flare.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/winmain.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/flare.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ddraw.lib winmm.lib dxguid.lib ..\..\lib\d3dframe.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=ddraw.lib winmm.lib dxguid.lib ..\..\lib\d3dframe.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/flare.pdb" /machine:I386\
 /out:"$(OUTDIR)/flare.exe" 
LINK32_OBJS= \
	"$(INTDIR)\flare.obj" \
	"$(INTDIR)\winmain.obj" \
	"$(INTDIR)\winmain.res"

"$(OUTDIR)\flare.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "flare - Win32 Debug"

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

ALL : "$(OUTDIR)\flare.exe"

CLEAN : 
	-@erase "$(INTDIR)\flare.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\winmain.obj"
	-@erase "$(INTDIR)\winmain.res"
	-@erase "$(OUTDIR)\flare.exe"
	-@erase "$(OUTDIR)\flare.ilk"
	-@erase "$(OUTDIR)\flare.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)/flare.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/winmain.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/flare.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 ddraw.lib winmm.lib dxguid.lib ..\..\lib\d3dframe.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=ddraw.lib winmm.lib dxguid.lib ..\..\lib\d3dframe.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/flare.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/flare.exe" 
LINK32_OBJS= \
	"$(INTDIR)\flare.obj" \
	"$(INTDIR)\winmain.obj" \
	"$(INTDIR)\winmain.res"

"$(OUTDIR)\flare.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "flare - Win32 Release"
# Name "flare - Win32 Debug"

!IF  "$(CFG)" == "flare - Win32 Release"

!ELSEIF  "$(CFG)" == "flare - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\flare.cpp
DEP_CPP_FLARE=\
	"..\..\..\..\..\mssdk\include\d3dcaps.h"\
	"..\..\..\..\..\mssdk\include\d3dtypes.h"\
	"..\..\..\..\..\mssdk\include\d3dvec.inl"\
	"..\..\include\D3DTextr.h"\
	"..\..\include\D3DUtil.h"\
	{$(INCLUDE)}"\d3d.h"\
	

"$(INTDIR)\flare.obj" : $(SOURCE) $(DEP_CPP_FLARE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\resource.h

!IF  "$(CFG)" == "flare - Win32 Release"

!ELSEIF  "$(CFG)" == "flare - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\winmain.cpp
DEP_CPP_WINMA=\
	"..\..\..\..\..\mssdk\include\d3dcaps.h"\
	"..\..\..\..\..\mssdk\include\d3dtypes.h"\
	"..\..\..\..\..\mssdk\include\d3dvec.inl"\
	"..\..\include\D3DEnum.h"\
	"..\..\include\D3DFrame.h"\
	"..\..\include\D3DUtil.h"\
	{$(INCLUDE)}"\d3d.h"\
	

"$(INTDIR)\winmain.obj" : $(SOURCE) $(DEP_CPP_WINMA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\winmain.rc
DEP_RSC_WINMAI=\
	".\DirectX.ico"\
	

"$(INTDIR)\winmain.res" : $(SOURCE) $(DEP_RSC_WINMAI) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
