proj=DSPStrm

!if "$(nodebug)" == "1"
OBJ_DIR = Retail
!else
OBJ_DIR = Debug
!endif

!include "$(DXSDKROOT)\include\dxsdk.inc"

mycflags=

OBJ_LIST = $(OBJ_DIR)\dsstream.obj $(OBJ_DIR)\dstrenum.obj $(OBJ_DIR)\dstrtime.obj $(OBJ_DIR)\dstrwave.obj\
        $(OBJ_DIR)\debug.obj

all: mkdir $(OBJ_DIR)\$(proj).exe

$(OBJ_DIR)\dsstream.obj:  dsstream.c
    $(cc) $(cdebug) $(cflags) $(mycflags) $(outobj)$(OBJ_DIR)\dsstream.obj dsstream.c

$(OBJ_DIR)\dstrenum.obj:  dstrenum.c
    $(cc) $(cdebug) $(cflags) $(mycflags) $(outobj)$(OBJ_DIR)\dstrenum.obj dstrenum.c

$(OBJ_DIR)\dstrtime.obj:  dstrtime.c
    $(cc) $(cdebug) $(cflags) $(mycflags) $(outobj)$(OBJ_DIR)\dstrtime.obj dstrtime.c

$(OBJ_DIR)\dstrwave.obj:  dstrwave.c
    $(cc) $(cdebug) $(cflags) $(mycflags) $(outobj)$(OBJ_DIR)\dstrwave.obj dstrwave.c

$(OBJ_DIR)\debug.obj:  debug.c
    $(cc) $(cdebug) $(cflags) $(mycflags) $(outobj)$(OBJ_DIR)\debug.obj debug.c

$(OBJ_DIR)\$(proj).res: dsstream.rc resource.h
   $(rc) $(rcflags) $(OBJ_DIR)\$(proj).res dsstream.rc

$(OBJ_DIR)\$(proj).exe: $(OBJ_LIST) $(OBJ_DIR)\$(proj).res
    $(link) $(linkdebug) $(linkflags) $(OBJ_LIST) $(borobjs) $(commas) $(outexe)$(OBJ_DIR)\$(proj).exe $(commas) $(commas) $(deflibs) ddraw.lib dsound.lib $(commas) $(commas) $(OBJ_DIR)\$(proj).res

mkdir:
    @if not exist $(OBJ_DIR)\NUL md $(OBJ_DIR)
    
# Rules for cleaning out those old files
clean:
    -@echo y | del Retail
    -@echo y | del Debug
    -@rd Retail
    -@rd Debug
