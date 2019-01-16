//-----------------------------------------------------------------------------
// File: WinMain.cpp
//
// Desc: Main file for tutorials. This step shows the minimum code to get a
//       Direct3D app up and running. The output is simply the rendering of one
//       triangle.
//
// Copyright (c) 1998 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#define STRICT
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <d3d.h>
#include "resource.h"




//-----------------------------------------------------------------------------
// Local variables for the DirectDraw and Direct3D interface.
//
// Note: A real programmer would not use global variables for these objects,
// and use encapsulation instead. As it turns out, after initialization, any
// Direct3D app can make do with only a LPDIRECT3DDEVICE3 parameter, and deduct
// all other interfaces from that.
//-----------------------------------------------------------------------------
static LPDIRECTDRAW         g_pDD1           = NULL;
static LPDIRECTDRAW4        g_pDD4           = NULL;
static LPDIRECTDRAWSURFACE4 g_pddsPrimary    = NULL;
static LPDIRECTDRAWSURFACE4 g_pddsBackBuffer = NULL;
static LPDIRECT3D3          g_pD3D           = NULL;
static LPDIRECT3DDEVICE3    g_pd3dDevice     = NULL;
static LPDIRECT3DVIEWPORT3  g_pvViewport     = NULL;
static RECT                 g_rcScreenRect;
static RECT                 g_rcViewportRect;




//-----------------------------------------------------------------------------
// Local variables for the Windows portion of the app
//-----------------------------------------------------------------------------
static BOOL g_bActive  = FALSE; // Whether the app is active (not minimized)
static BOOL g_bReady   = FALSE; // Whether the app is ready to render frames



//-----------------------------------------------------------------------------
// Local function-prototypes
//-----------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
HRESULT Initialize3DEnvironment( HWND );
HRESULT Cleanup3DEnvironment();
HRESULT Render3DEnvironment();
VOID    OnMove( INT, INT );
HRESULT ShowFrame();
HRESULT RestoreSurfaces();




//-----------------------------------------------------------------------------
// External function-prototypes
//-----------------------------------------------------------------------------
VOID    App_DeleteDeviceObjects( LPDIRECT3DDEVICE3, LPDIRECT3DVIEWPORT3 );
HRESULT App_InitDeviceObjects( LPDIRECT3DDEVICE3, LPDIRECT3DVIEWPORT3 );
HRESULT App_FrameMove( LPDIRECT3DDEVICE3, FLOAT );
HRESULT App_Render( LPDIRECT3DDEVICE3, LPDIRECT3DVIEWPORT3, D3DRECT* );




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Entry point to the program. Initializes everything, and goes into a
//       message-processing loop. Idle time is used to render the scene.
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
	// Register the window class
    WNDCLASS wndClass = { CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, hInst,
                          LoadIcon( hInst, MAKEINTRESOURCE(IDI_MAIN_ICON)),
                          LoadCursor(NULL, IDC_ARROW), 
                          (HBRUSH)GetStockObject(WHITE_BRUSH), NULL,
                          TEXT("Render Window") };
    RegisterClass( &wndClass );

    // Create our main window
    HWND hWnd = CreateWindow( TEXT("Render Window"),
		                      TEXT("D3D Tutorial: Drawing One Triangle"),
                              WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                              CW_USEDEFAULT, 300, 300, 0L, 0L, hInst, 0L );
    ShowWindow( hWnd, SW_SHOWNORMAL );
    UpdateWindow( hWnd );

    // Load keyboard accelerators
    HACCEL hAccel = LoadAccelerators( hInst, MAKEINTRESOURCE(IDR_MAIN_ACCEL) );

	// Initialize the app specifics. This is where all the DirectDraw/Direct3D
	// initialization happens, so see this function for the real purpose of
	// this tutorial
	if( FAILED( Initialize3DEnvironment( hWnd ) ) )
        return 0;

    // Now we're ready to recieve and process Windows messages.
	BOOL bGotMsg;
	MSG  msg;
	PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );
	g_bReady = TRUE;

    while( WM_QUIT != msg.message  )
    {
		// Use PeekMessage() if the app is active, so we can use idle time to
		// render the scene. Else, use GetMessage() to avoid eating CPU time.
		if( g_bActive )
			bGotMsg = PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE );
		else
			bGotMsg = GetMessage( &msg, NULL, 0U, 0U );

		if( bGotMsg )
        {
			// Translate and dispatch the message
            if( 0 == TranslateAccelerator( hWnd, hAccel, &msg ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
        }
		else
		{
			// Render a frame during idle time (no messages are waiting)
			if( g_bActive && g_bReady )
				Render3DEnvironment();
		}
    }
	return msg.wParam;
}




//-----------------------------------------------------------------------------
// Name: WndProc()
// Desc: This is the basic Windows-programming function that processes
//       Windows messages. We need to handle window movement, painting,
//       and destruction.
//-----------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    switch( uMsg )
    {
        case WM_PAINT:
			// If we get WM_PAINT messages, it usually means our window was
			// covered up, so we need to refresh it by re-showing the contents
			// of the current frame.
			ShowFrame();
            break;

        case WM_MOVE:
			// Move messages need to be tracked to update the screen rects
			// used for blitting the backbuffer to the primary.
            if( g_bActive && g_bReady )
				OnMove( (SHORT)LOWORD(lParam), (SHORT)HIWORD(lParam) );
            break;

        case WM_SIZE:
            // Check to see if we are losing or gaining our window. Set the
			// active flag to match.
            if( SIZE_MAXHIDE==wParam || SIZE_MINIMIZED==wParam )
                g_bActive = FALSE;
			else g_bActive = TRUE;

            // A new window size will require a new backbuffer size. The
			// easiest way to achieve this is to release and re-create
			// everything. Note: if the window gets too big, we may run out
			// of video memory and need to exit. This simple app exits
			// without displaying error messages, but a real app would behave
			// itself much better.
            if( g_bActive && g_bReady )
			{
				g_bReady = FALSE;
				if( FAILED( Cleanup3DEnvironment() ) )
					DestroyWindow( hWnd );
				if( FAILED( Initialize3DEnvironment( hWnd ) ) )
					DestroyWindow( hWnd );
				g_bReady = TRUE;
			}
            break;

		case WM_GETMINMAXINFO:
			// Prevent the window from going smaller than some minimum size
			((MINMAXINFO*)lParam)->ptMinTrackSize.x = 100;
			((MINMAXINFO*)lParam)->ptMinTrackSize.y = 100;
			break;

        case WM_CLOSE:
            DestroyWindow( hWnd );
            return 0;
        
        case WM_DESTROY:
            Cleanup3DEnvironment();
            PostQuitMessage(0);
            return 0L;
    }

    return DefWindowProc( hWnd, uMsg, wParam, lParam );
}
            



//-----------------------------------------------------------------------------
// Note: From this point on, the code is DirectX specific support for the app.
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
// Name: Initialize3DEnvironment()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT Initialize3DEnvironment( HWND hWnd )
{
	HRESULT hr;

    //-------------------------------------------------------------------------
	// Step 1: Create DirectDraw and set the coop level
    //-------------------------------------------------------------------------

	// Create the IDirectDraw interface. The first parameter is the GUID,
	// which is allowed to be NULL. If there are more than one DirectDraw
	// drivers on the system, a NULL guid requests the primary driver. For 
	// non-GDI hardware cards like the 3DFX and PowerVR, the guid would need
	// to be explicity specified . (Note: these guids are normally obtained
	// from enumeration, which is convered in a subsequent tutorial.)
	hr = DirectDrawCreate( NULL, &g_pDD1, NULL );
	if( FAILED( hr ) )
		return hr;

	// Get a ptr to an IDirectDraw4 interface. This interface to DirectDraw
	// represents the DX6 version of the API.
	hr = g_pDD1->QueryInterface( IID_IDirectDraw4, (VOID**)&g_pDD4 );
	if( FAILED( hr ) )
		return hr;

    // Set the Windows cooperative level. This is where we tell the system
	// whether wew will be rendering in fullscreen mode or in a window. Note
	// that some hardware (non-GDI) may not be able to render into a window.
	// The flag DDSCL_NORMAL specifies windowed mode. Using fullscreen mode
	// is the topic of a subsequent tutorial. The DDSCL_FPUSETUP flag is a 
	// hint to DirectX to optomize floating points calculations. See the docs
	// for more info on this. Note: this call could fail if another application
	// already controls a fullscreen, exclusive mode.
    hr = g_pDD4->SetCooperativeLevel( hWnd, DDSCL_NORMAL );
	if( FAILED( hr ) )
		return hr;

    //-------------------------------------------------------------------------
	// Step 2: Create DirectDraw surfaces used for rendering
    //-------------------------------------------------------------------------

	// Initialize a surface description structure for the primary surface. The
	// primary surface represents the entire display, with dimensions and a
	// pixel format of the display. Therefore, none of that information needs
	// to be specified in order to create the primary surface.
	DDSURFACEDESC2 ddsd;
	ZeroMemory( &ddsd, sizeof(DDSURFACEDESC2) );
	ddsd.dwSize         = sizeof(DDSURFACEDESC2);
	ddsd.dwFlags        = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

	// Create the primary surface.
	hr = g_pDD4->CreateSurface( &ddsd, &g_pddsPrimary, NULL );
	if( FAILED( hr ) )
		return hr;

	// Setup a surface description to create a backbuffer. This is an
	// offscreen plain surface with dimensions equal to our window size.
	// The DDSCAPS_3DDEVICE is needed so we can later query this surface
	// for an IDirect3DDevice interface.
	ddsd.dwFlags        = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;

	// Set the dimensions of the backbuffer. Note that if our window changes
	// size, we need to destroy this surface and create a new one.
	GetClientRect( hWnd, &g_rcScreenRect );
	GetClientRect( hWnd, &g_rcViewportRect );
	ClientToScreen( hWnd, (POINT*)&g_rcScreenRect.left );
	ClientToScreen( hWnd, (POINT*)&g_rcScreenRect.right );
	ddsd.dwWidth  = g_rcScreenRect.right - g_rcScreenRect.left;
	ddsd.dwHeight = g_rcScreenRect.bottom - g_rcScreenRect.top;

	// Create the backbuffer. The most likely reason for failure is running
	// out of video memory. (A more sophisticated app should handle this.)
	hr = g_pDD4->CreateSurface( &ddsd, &g_pddsBackBuffer, NULL );
	if( FAILED( hr ) )
		return hr;

	// Note: if using a z-buffer, the zbuffer surface creation would go around
	// here. However, z-buffer usage is the topic of a subsequent tutorial.

	// Create a clipper object which handles all our clipping for cases when
	// our window is partially obscured by other windows. This is not needed
	// for apps running in fullscreen mode.
	LPDIRECTDRAWCLIPPER pcClipper;
	hr = g_pDD4->CreateClipper( 0, &pcClipper, NULL );
	if( FAILED( hr ) )
		return hr;

	// Associate the clipper with our window. Note that, afterwards, the
	// clipper is internally referenced by the primary surface, so it is safe
	// to release our local reference to it.
	pcClipper->SetHWnd( 0, hWnd );
	g_pddsPrimary->SetClipper( pcClipper );
	pcClipper->Release();

    //-------------------------------------------------------------------------
	// Step 3: Create the Direct3D interfaces
    //-------------------------------------------------------------------------

    // Query DirectDraw for access to Direct3D
    g_pDD4->QueryInterface( IID_IDirect3D3, (VOID**)&g_pD3D );
    if( FAILED( hr) )
		return hr;

	// Before creating the device, check that we are NOT in a palettized
	// display. That case will cause CreateDevice() to fail, since this simple 
	// tutorial does not bother with palettes.
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	g_pDD4->GetDisplayMode( &ddsd );
	if( ddsd.ddpfPixelFormat.dwRGBBitCount <= 8 )
		return DDERR_INVALIDMODE;

	// Create the device. The GUID is hardcoded for now, but should come from
	// device enumeration, which is the topic of a future tutorial. The device
	// is created off of our back buffer, which becomes the render target for
	// the newly created device.
    hr = g_pD3D->CreateDevice( IID_IDirect3DHALDevice, g_pddsBackBuffer,
                               &g_pd3dDevice, NULL );
	if( FAILED( hr ) )
	{
		// This call could fail for many reasons. The most likely cause is
		// that we specifically requested a hardware device, without knowing
		// whether there is even a 3D card installed in the system. Another
		// possibility is the hardware is incompatible with the current display
		// mode (once again, the correct implementation would use enumeration
		// to check that). In any case, let's simply try again with the RGB
		// software rasterizer.
	    hr = g_pD3D->CreateDevice( IID_IDirect3DRGBDevice, g_pddsBackBuffer,
                                   &g_pd3dDevice, NULL );
		if( FAILED( hr ) )
			return hr;
	}

    //-------------------------------------------------------------------------
	// Step 4: Create the viewport
    //-------------------------------------------------------------------------

    // Set up the viewport data parameters
    D3DVIEWPORT2 vdData;
    ZeroMemory( &vdData, sizeof(D3DVIEWPORT2) );
    vdData.dwSize       = sizeof(D3DVIEWPORT2);
	vdData.dwWidth      = g_rcScreenRect.right - g_rcScreenRect.left;
	vdData.dwHeight     = g_rcScreenRect.bottom - g_rcScreenRect.top;
    vdData.dvClipX      = -1.0f;
    vdData.dvClipWidth  = 2.0f;
    vdData.dvClipY      = 1.0f;
    vdData.dvClipHeight = 2.0f;
    vdData.dvMaxZ       = 1.0f;

    // Create the viewport
    hr = g_pD3D->CreateViewport( &g_pvViewport, NULL );
	if( FAILED( hr ) )
		return hr;

    // Associate the viewport with the D3DDEVICE object
    g_pd3dDevice->AddViewport( g_pvViewport );

    // Set the parameters to the new viewport
    g_pvViewport->SetViewport2( &vdData );

    // Set the viewport as current for the device
    g_pd3dDevice->SetCurrentViewport( g_pvViewport );

    //-------------------------------------------------------------------------
	// Step 5: We're done and ready to set up our scene
    //-------------------------------------------------------------------------

	return App_InitDeviceObjects( g_pd3dDevice, g_pvViewport );
}




//-----------------------------------------------------------------------------
// Name: Cleanup3DEnvironment()
// Desc: Releases all the resources used by the app. Note the check for
//       reference counts when releasing the D3DDevice and DDraw objects. If
//       these ref counts are non-zero, then something was not cleaned up
//       correctly.
//-----------------------------------------------------------------------------
HRESULT Cleanup3DEnvironment()
{
	// Cleanup any objects created for the scene
	App_DeleteDeviceObjects( g_pd3dDevice, g_pvViewport );

	// Release the DDraw and D3D objects used by the app
    if( g_pvViewport )     g_pvViewport->Release();
	if( g_pD3D )           g_pD3D->Release();
	if( g_pddsBackBuffer ) g_pddsBackBuffer->Release();
	if( g_pddsPrimary )    g_pddsPrimary->Release();
	if( g_pDD4 )           g_pDD4->Release();

    // Do a safe check for releasing the D3DDEVICE. RefCount should be zero.
    if( g_pd3dDevice )
        if( 0 < g_pd3dDevice->Release() )
			return E_FAIL;

	// Do a safe check for releasing DDRAW. RefCount should be zero.
    if( g_pDD1 )
        if( 0 < g_pDD1->Release() )
			return E_FAIL;

    g_pvViewport     = NULL;
	g_pd3dDevice     = NULL;
	g_pD3D           = NULL;
	g_pddsBackBuffer = NULL;
	g_pddsPrimary    = NULL;
	g_pDD4           = NULL;
	g_pDD1           = NULL;

	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Render3DEnvironment()
// Desc: Draws the scene. There are three steps here:
//       (1) Animate the scene
//       (2) Render the scene
//       (3) Show the frame (copy backbuffer contents to the primary).
//-----------------------------------------------------------------------------
HRESULT Render3DEnvironment()
{
	// Call the app specific function to framemove (animate) the scene
    App_FrameMove( g_pd3dDevice, ((FLOAT)clock())/CLOCKS_PER_SEC );

    // Call the app specific function to render the scene
    App_Render( g_pd3dDevice, g_pvViewport, (D3DRECT*)&g_rcViewportRect );
    
    // Show the frame on the primary surface. Note: this is the best place to
	// check for "lost" surfaces. Surfaces can be lost if something caused
	// them to temporary lose their video memory. "Lost" surfaces simply
	// need to be restored before continuing.
    if( DDERR_SURFACELOST == ShowFrame() )
		RestoreSurfaces();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: ShowFrame()
// Desc: Show the frame on the primary surface
//-----------------------------------------------------------------------------
HRESULT ShowFrame()
{
	if( NULL == g_pddsPrimary )
		return E_FAIL;

    // We are in windowed mode, so perform a blit from the backbuffer to the
	// correct position on the primary surface
    return g_pddsPrimary->Blt( &g_rcScreenRect, g_pddsBackBuffer, 
                               &g_rcViewportRect, DDBLT_WAIT, NULL );
}




//-----------------------------------------------------------------------------
// Name: RestoreSurfaces()
// Desc: Checks for lost surfaces and restores them if lost.
//-----------------------------------------------------------------------------
HRESULT RestoreSurfaces()
{
    // Check/restore the primary surface
    if( g_pddsPrimary )
        if( g_pddsPrimary->IsLost() )
            g_pddsPrimary->Restore();
    
    // Check/restore the back buffer
    if( g_pddsBackBuffer )
        if( g_pddsBackBuffer->IsLost() )
            g_pddsBackBuffer->Restore();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: OnMove()
// Desc: Moves the screen rect for windowed renderers
//-----------------------------------------------------------------------------
VOID OnMove( INT x, INT y )
{
	DWORD dwWidth  = g_rcScreenRect.right - g_rcScreenRect.left;
	DWORD dwHeight = g_rcScreenRect.bottom - g_rcScreenRect.top;
    SetRect( &g_rcScreenRect, x, y, x + dwWidth, y + dwHeight );
}




