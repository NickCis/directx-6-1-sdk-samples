//-----------------------------------------------------------------------------
// File: debug.c
//
// Desc: Support code for debugging
//
//
// Copyright (C) 1995-1996 Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------

#ifdef DEBUG
#include <windows.h>
#include <windowsx.h>
#include <stdarg.h>
#include <wchar.h>
#include "debug.h"


//-----------------------------------------------------------------------------
// External variables
//-----------------------------------------------------------------------------
extern HWND hWndMain;
extern char szAppName[];




//-----------------------------------------------------------------------------
// Name: DbgVPrintF()
// Desc:
//-----------------------------------------------------------------------------
void FAR CDECL DbgVPrintF( LPSTR szFormat, va_list va )
{
    char                ach[255];
    BOOL                fDebugBreak = FALSE;
    BOOL                fPrefix     = TRUE;
    BOOL                fCRLF       = TRUE;

    ach[0] = '\0';

	while(1)
    {
        switch (*szFormat)
        {
            case '!':
                fDebugBreak = TRUE;
                szFormat++;
                continue;

            case '`':
                fPrefix = FALSE;
                szFormat++;
                continue;

            case '~':
                fCRLF = FALSE;
                szFormat++;
                continue;
        }

        break;
    }

    if (fDebugBreak)
    {
        ach[0] = '\007';
        ach[1] = '\0';
    }

    if (fPrefix)
    {
        lstrcatA(ach, DEBUG_MODULE_NAME ": ");
    }

    wvsprintfA(ach + lstrlenA(ach), szFormat, va);

    if (fCRLF)
    {
        lstrcatA(ach, "\r\n");
    }

    OutputDebugStringA(ach);

    if (fDebugBreak)
    {
        DebugBreak();
    }
}




//-----------------------------------------------------------------------------
// Name: dprintf()
// Desc:
//-----------------------------------------------------------------------------
void FAR CDECL dprintf( UINT uDbgLevel, LPSTR szFormat, ... )
{
    va_list va;

    va_start(va, szFormat);
    DbgVPrintF(szFormat, va);
    va_end(va);
}




//-----------------------------------------------------------------------------
// Name: AssertFail()
// Desc:
//-----------------------------------------------------------------------------
VOID AssertFail(char szErr[], char szFileName[], int nLine, char szMessage[])
{
	char szT[256];

	if (szMessage != NULL)
		wsprintf(szT, "Assert(%s);\nFile %s, line %d.  %s", szErr, szFileName, nLine, szMessage);
	else 
		wsprintf(szT, "Assert(%s);\nFile %s, line %d.", szErr, szFileName, nLine);
	
	switch( MessageBox(hWndMain, szT, szAppName, MB_ABORTRETRYIGNORE | MB_ICONSTOP | MB_APPLMODAL))
	{
		case IDABORT:
			SendMessage(hWndMain, WM_CLOSE, 0, 0);
		case IDRETRY:
			_asm int 3;
			// Fall Through //
		case IDIGNORE:
			break;

	}
}





#endif // #ifdef DEBUG


