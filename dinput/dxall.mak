SAMPLES = \
        src\FFDonuts \
        src\Scrawl \
        src\MouseNon \
        src\MouseExc \
        src\KeybdImm \
        src\KeybdBuf \
        src\JoyFFeed \
        src\JoystImm


!IFDEF clean
do=-i clean
DOING=Clean
!ELSE

!IFDEF nodebug
do=nodebug=1
DOING=Release
!ELSE
DOING=Debug
!ENDIF
!ENDIF

$(SAMPLES): $(@R)\makefile
        @cd $@
        @echo *** DirectX\$@ $(DOING)***
        @echo *** DirectX\$@ $(DOING)*** >>..\DirectX.tmp
        @nmake $(do) >>..\DirectX.tmp
        @cd ..\..
