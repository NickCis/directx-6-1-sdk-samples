# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=compress - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to compress - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "compress - Win32 Release" && "$(CFG)" !=\
 "compress - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "compress.mak" CFG="compress - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "compress - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "compress - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "compress - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "compress - Win32 Release"

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

ALL : "$(OUTDIR)\compress.exe"

CLEAN : 
	-@erase "$(INTDIR)\Compress.obj"
	-@erase "$(INTDIR)\WinMain.obj"
	-@erase "$(INTDIR)\WinMain.res"
	-@erase "$(OUTDIR)\compress.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)/compress.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/WinMain.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/compress.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 advapi32.lib dxguid.lib ddraw.lib ..\..\lib\d3dframe.lib kernel32.lib user32.lib gdi32.lib winmm.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=advapi32.lib dxguid.lib ddraw.lib ..\..\lib\d3dframe.lib\
 kernel32.lib user32.lib gdi32.lib winmm.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/compress.pdb" /machine:I386\
 /out:"$(OUTDIR)/compress.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Compress.obj" \
	"$(INTDIR)\WinMain.obj" \
	"$(INTDIR)\WinMain.res"

"$(OUTDIR)\compress.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "compress - Win32 Debug"

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

ALL : "$(OUTDIR)\compress.exe"

CLEAN : 
	-@erase "$(INTDIR)\Compress.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\WinMain.obj"
	-@erase "$(INTDIR)\WinMain.res"
	-@erase "$(OUTDIR)\compress.exe"
	-@erase "$(OUTDIR)\compress.ilk"
	-@erase "$(OUTDIR)\compress.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)/compress.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/WinMain.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/compress.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 advapi32.lib dxguid.lib ddraw.lib ..\..\lib\d3dframe.lib kernel32.lib user32.lib gdi32.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=advapi32.lib dxguid.lib ddraw.lib ..\..\lib\d3dframe.lib\
 kernel32.lib user32.lib gdi32.lib winmm.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/compress.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/compress.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Compress.obj" \
	"$(INTDIR)\WinMain.obj" \
	"$(INTDIR)\WinMain.res"

"$(OUTDIR)\compress.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "compress - Win32 Release"
# Name "compress - Win32 Debug"

!IF  "$(CFG)" == "compress - Win32 Release"

!ELSEIF  "$(CFG)" == "compress - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Compress.cpp
DEP_CPP_COMPR=\
	"..\..\..\..\..\include\d3dcaps.h"\
	"..\..\..\..\..\include\d3dtypes.h"\
	"..\..\..\..\..\include\d3dvec.inl"\
	"..\..\include\D3DMath.h"\
	"..\..\include\D3DUtil.h"\
	{$(INCLUDE)}"\d3d.h"\
	

"$(INTDIR)\Compress.obj" : $(SOURCE) $(DEP_CPP_COMPR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\resource.h

!IF  "$(CFG)" == "compress - Win32 Release"

!ELSEIF  "$(CFG)" == "compress - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WinMain.cpp
DEP_CPP_WINMA=\
	"..\..\..\..\..\include\d3dcaps.h"\
	"..\..\..\..\..\include\d3dtypes.h"\
	"..\..\..\..\..\include\d3dvec.inl"\
	"..\..\include\D3DEnum.h"\
	"..\..\include\D3DFrame.h"\
	"..\..\include\D3DUtil.h"\
	{$(INCLUDE)}"\d3d.h"\
	

"$(INTDIR)\WinMain.obj" : $(SOURCE) $(DEP_CPP_WINMA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\WinMain.rc
DEP_RSC_WINMAI=\
	".\directx.ico"\
	

"$(INTDIR)\WinMain.res" : $(SOURCE) $(DEP_RSC_WINMAI) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
