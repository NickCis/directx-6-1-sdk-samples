/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       stretch.cpp
 *
 *  stretch with multimonitor support
 *
 ***************************************************************************/

#define NAME "Stretch"
#define TITLE "Stretch"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include "resource.h"
#include "ddutil.h"
#include "ddmm.h"

#define SIZEX   64
#define SIZEY   64
char *szBitmap = "DONUT";

HWND            hwnd;
DWORD           UpdateDelay = 100;

LPDIRECTDRAW4           lpDD;           // DirectDraw object
LPDIRECTDRAWSURFACE4    lpDDSPrimary;   // DirectDraw primary surface
LPDIRECTDRAWSURFACE4    lpDDSOne;       // Offscreen surface 1
LPDIRECTDRAWCLIPPER     lpClipper;      // clipper for primary
LPDIRECTDRAWPALETTE     lpDDPal;        // DirectDraw palette
BOOL                    bActive;        // is application active?

/* multimon stuff
*/
int     MyDevice;
char    MyDeviceName[128];
RECT    MyDeviceRect;

BOOL ddInit(HWND);

/*
 * restoreAll
 *
 * restore all lost objects
 */
BOOL restoreAll( void )
{
    return lpDDSPrimary->Restore() == DD_OK &&
	   lpDDSOne->Restore()     == DD_OK &&
	   DDReLoadBitmap(lpDDSOne, szBitmap) == DD_OK;

} /* restoreAll */

/*
 * updateFrame
 * 
 * Decide what needs to be blitted next, wait for flip to complete,
 * then flip the buffers.
 */
void updateFrame( void )
{
    static DWORD        lastTickCount = 0;
    static int          currentFrame = 0;
    static BOOL         haveBackground = FALSE;
    DWORD               thisTickCount;
    RECT                rcRect;
    RECT                destRect;
    HRESULT             ddrval;
    POINT               pt;

    thisTickCount = GetTickCount();
    if((thisTickCount - lastTickCount) <= UpdateDelay)
    {
	return;
    }

    // Move to next frame;
    lastTickCount = thisTickCount;
    currentFrame++;
    if(currentFrame > 59)
    {
	currentFrame = 0;
    }

    // Blit the stuff for the next frame
    rcRect.left   = currentFrame%10*64;
    rcRect.top    = currentFrame/10*64;
    rcRect.right  = currentFrame%10*64 + 64;
    rcRect.bottom = currentFrame/10*64 + 64;

    GetClientRect( hwnd, &destRect );
    if (destRect.right  < 64) destRect.right = 64;
    if (destRect.bottom < 64)  destRect.bottom = 64;

    pt.x = pt.y = 0;
    ClientToScreen( hwnd, &pt );
    pt.x -= MyDeviceRect.left;
    pt.y -= MyDeviceRect.top;
    OffsetRect(&destRect, pt.x, pt.y);

    while( 1 )
    {
	ddrval = lpDDSPrimary->Blt( &destRect, lpDDSOne, &rcRect, 0, NULL );

	if( ddrval == DD_OK )
	{
	    break;
	}
	if( ddrval == DDERR_SURFACELOST )
	{
	    if(!restoreAll())
	    {
		return;
	    }
	}
	if( ddrval != DDERR_WASSTILLDRAWING )
	{
	    return;
	}
    }
    if(ddrval != DD_OK)
    {
	return;
    }
} /* updateFrame */


/*
 * finiObjects
 *
 * finished with all objects we use; release them
 */
static void finiObjects( BOOL fKillDD )
{
    if( lpDDSPrimary != NULL )
    {
	lpDDSPrimary->Release();
	lpDDSPrimary = NULL;
    }
    if( lpDDSOne != NULL )
    {
	lpDDSOne->Release();
	lpDDSOne = NULL;
    }
    if( lpDDPal != NULL )
    {
	lpDDPal->Release();
	lpDDPal = NULL;
    }
    if( fKillDD && lpDD != NULL )
    {
	lpDD->Release();
	lpDD = NULL;
    }
} /* finiObjects */

long FAR PASCAL WindowProc( HWND hWnd, UINT message, 
			    WPARAM wParam, LPARAM lParam )
{
    RECT  rc;

    switch( message )
    {
    case WM_ACTIVATEAPP:
	bActive = wParam;
	break;

    case WM_DISPLAYCHANGE:
	ddInit(hwnd);
	break;

    case WM_SIZE:
    case WM_MOVE:
	if (MyDevice != DirectDrawDeviceFromWindow(hwnd,NULL,NULL))
	{
	    ddInit(hwnd);
	}
	break;

    case WM_PALETTECHANGED:
	if ((HWND)wParam == hWnd)
	    break;
	// fall through to WM_QUERYNEWPALETTE
    case WM_QUERYNEWPALETTE:
	// install our palette here
	if (lpDDPal)
	{
	    lpDDSPrimary->SetPalette(lpDDPal);
	}
	// reload the bitmap into the surface because the palette
	// has changed..
	DDReLoadBitmap(lpDDSOne, szBitmap);
	break;


    case WM_CREATE:
	break;

    case WM_GETMINMAXINFO:
	((MINMAXINFO*)lParam)->ptMinTrackSize.x = SIZEX;
	((MINMAXINFO*)lParam)->ptMinTrackSize.y = SIZEY;
	return 0;

    case WM_KEYDOWN:
	switch( wParam )
	{
	case VK_ESCAPE:
	case VK_F12:
	    PostMessage(hWnd, WM_CLOSE, 0, 0);
	    break;
	}
	break;

    case WM_DESTROY:
	finiObjects(TRUE);
	PostQuitMessage( 0 );
	break;

    case WM_KEYUP:
	if (wParam >= '1' && wParam <= '9')
	{
	    SetRect(&rc, 0, 0, SIZEX*(wParam-'0'), SIZEY*(wParam-'0'));
	    goto size_me;
	}
	break;

    case WM_COMMAND: 
	switch(LOWORD(wParam))
	{
	    case ID_ROTATION_STOP:          
		UpdateDelay = 0x7fffffff;
		break;
	    case ID_ROTATION_SLOW:          
		UpdateDelay = 200;
		break;
	    case ID_ROTATION_FAST:          
		UpdateDelay = 100;
		break;
	    case ID_FILE_EXIT:      
		PostMessage( hWnd, WM_CLOSE, 0, 0L );
		break;
		    
	    case ID_SIZE_1X1: SetRect(&rc, 0, 0, SIZEX*1, SIZEY*1); goto size_me;
	    case ID_SIZE_2X1: SetRect(&rc, 0, 0, SIZEX*2, SIZEY*1); goto size_me;
	    case ID_SIZE_3X1: SetRect(&rc, 0, 0, SIZEX*3, SIZEY*1); goto size_me;
	    case ID_SIZE_1X2: SetRect(&rc, 0, 0, SIZEX*1, SIZEY*2); goto size_me;
	    case ID_SIZE_2X2: SetRect(&rc, 0, 0, SIZEX*2, SIZEY*2); goto size_me;
	    case ID_SIZE_3X2: SetRect(&rc, 0, 0, SIZEX*3, SIZEY*2); goto size_me;
	    case ID_SIZE_1X3: SetRect(&rc, 0, 0, SIZEX*1, SIZEY*3); goto size_me;
	    case ID_SIZE_2X3: SetRect(&rc, 0, 0, SIZEX*2, SIZEY*3); goto size_me;
	    case ID_SIZE_3X3: SetRect(&rc, 0, 0, SIZEX*3, SIZEY*3); goto size_me;
size_me:
		AdjustWindowRectEx(&rc, GetWindowLong(hWnd, GWL_STYLE),
		    GetMenu(hWnd) != NULL, GetWindowLong(hWnd, GWL_EXSTYLE));
		SetWindowPos(hWnd, NULL, 0, 0, rc.right-rc.left, rc.bottom-rc.top,
		    SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);
		break;
	    } 
	    break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);

} /* WindowProc */

/*
 * This function is called if the initialization function fails
 */
BOOL initFail( HWND hwnd )
{
    finiObjects(TRUE);
    MessageBox( hwnd, "DirectDraw Init FAILED", TITLE, MB_OK );
    DestroyWindow( hwnd );
    return FALSE;

} /* initFail */

/*
 * ddInit
 */
BOOL ddInit( HWND hwnd )
{
    DDSURFACEDESC2      ddsd;
    HRESULT             ddrval;
    char                ach[128];
    LPDIRECTDRAW        pDD;

    /*
     * clean up our mess
     */
    finiObjects(TRUE);

    MyDevice = DirectDrawDeviceFromWindow(hwnd,MyDeviceName,&MyDeviceRect);

    if (MyDeviceName[0] == 0) lstrcpy(MyDeviceName, "(none)");
    wsprintf(ach, "%s - %s", TITLE, MyDeviceName);
    SetWindowText(hwnd, ach);

    /*
     * create the main DirectDraw object
     */
    pDD = DirectDrawCreateFromWindow(hwnd);

    if( pDD == NULL )
    {
	return initFail(hwnd);
    }

    // Fetch DirectDraw4 interface
    ddrval = pDD->QueryInterface(IID_IDirectDraw4, (LPVOID *) & lpDD);
    if (ddrval != DD_OK)
        return initFail(hwnd);

    ddrval = lpDD->SetCooperativeLevel( hwnd, DDSCL_NORMAL );

    // Create the primary surface
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

    ddrval = lpDD->CreateSurface( &ddsd, &lpDDSPrimary, NULL );
    if( ddrval != DD_OK )
    {
	return initFail(hwnd);
    }

    // create a clipper for the primary surface
    ddrval = lpDD->CreateClipper( 0, &lpClipper, NULL );
    if( ddrval != DD_OK )
    {
	return initFail(hwnd);
    }

    ddrval = lpClipper->SetHWnd( 0, hwnd );
    if( ddrval != DD_OK )
    {
	return initFail(hwnd);
    }

    ddrval = lpDDSPrimary->SetClipper( lpClipper );
    if( ddrval != DD_OK )
    {
	return initFail(hwnd);
    }

    // load our palette
    lpDDPal = DDLoadPalette(lpDD, szBitmap);

    // make sure to set the palette before loading bitmaps.
    if (lpDDPal)
	lpDDSPrimary->SetPalette(lpDDPal);

    // load our bitmap
    lpDDSOne = DDLoadBitmap(lpDD, szBitmap, 0, 0);

    if( lpDDSOne == NULL )
    {
	return initFail(hwnd);
    }

    return TRUE;
} /* doInit */

/*
 * doInit - do work required for every instance of the application:
 *                create the window, initialize data
 */
static BOOL doInit( HINSTANCE hInstance, int nCmdShow )
{
    WNDCLASS            wc;

    /*
     * set up and register window class
     */
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( hInstance, MAKEINTRESOURCE(IDI_MAIN_ICON));
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName = NULL; // MAKEINTRESOURCE(IDR_MENU);
    wc.lpszClassName = NAME;
    RegisterClass( &wc );
    
    /*
     * create a window
     */
    hwnd = CreateWindowEx(
	0,
	NAME,
	TITLE,
	WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME,
	CW_USEDEFAULT,
	CW_USEDEFAULT,
	128,
	128,
	NULL,
	NULL,
	hInstance,
	NULL );

    if( !hwnd )
    {
	return FALSE;
    }

    PostMessage(hwnd, WM_COMMAND, ID_SIZE_3X3, 0);

    ShowWindow( hwnd, nCmdShow );
    UpdateWindow( hwnd );

    /*
     * create the direct draw objects
     */
    ddInit(hwnd);

    return TRUE;

} /* doInit */

/*
 * WinMain - initialization, message loop
 */
int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow)
{
    MSG         msg;

    if( !doInit( hInstance, nCmdShow ) )
    {
	return FALSE;
    }

    while( 1 )
    {
	if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
	{
	    if( !GetMessage( &msg, NULL, 0, 0 ) )
		return msg.wParam;
	    TranslateMessage(&msg); 
	    DispatchMessage(&msg);
	}
	else
	{
	    updateFrame();
	}
    }
} /* WinMain */


