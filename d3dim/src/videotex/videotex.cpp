//-----------------------------------------------------------------------------
// File: VideoTex.cpp
//
// Desc: Example code showing how to do use an AVI file as a texture map. This
//       sample draws a cube with an AVI texture mapped to each of its faces.
//       Ideally, the texture would be created with the DDSCAPS2_HINTDYNAMIC
//       flag set.
//
//       Note: This code uses the D3D Framework helper library.
//
//
// Copyright (c) 1998 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#define STRICT
#define D3D_OVERLOADS
#include <time.h>
#include <stdio.h>
#include <windows.h>
#include <vfw.h>
#include "D3DTextr.h"
#include "D3DUtil.h"
#include "D3DMath.h"




//-----------------------------------------------------------------------------
// Declare the application globals for use in WinMain.cpp
//-----------------------------------------------------------------------------
TCHAR* g_strAppTitle       = TEXT("VideoTex sample app");
BOOL   g_bAppUseZBuffer    = FALSE;
BOOL   g_bAppUseBackBuffer = TRUE;




//-----------------------------------------------------------------------------
// Function prototypes and global (or static) variables
//-----------------------------------------------------------------------------
HRESULT App_InitDeviceObjects( LPDIRECT3DDEVICE3, LPDIRECT3DVIEWPORT3 );
VOID    App_DeleteDeviceObjects( LPDIRECT3DDEVICE3, LPDIRECT3DVIEWPORT3 );
HRESULT UpdateVideoTexture( LPDIRECT3DTEXTURE2, AVISTREAMINFO*, PGETFRAME );
HRESULT CreateDynamicTexture( LPDIRECTDRAWSURFACE4, LPDIRECT3DTEXTURE2* );

#define NUM_CUBE_VERTICES (4*6)
#define NUM_CUBE_INDICES  (6*6)
D3DVERTEX          g_pVertices[NUM_CUBE_VERTICES];
WORD               g_pIndices[NUM_CUBE_INDICES];

LPDIRECT3DTEXTURE2 g_ptexVideoTexture = NULL;

PAVISTREAM         g_paviStream;    // The AVI stream
PGETFRAME          g_pgfFrame;      // Ptr in the stream to get the next frame
AVISTREAMINFO      g_psiStreamInfo; // Info about the AVI stream




//-----------------------------------------------------------------------------
// Name: CreateCube()
// Desc: Sets up the vertices for a cube.
//-----------------------------------------------------------------------------
HRESULT CreateCube( D3DVERTEX* pVertices, WORD* pIndices )
{
    // Define the normals for the cube
    D3DVECTOR n0( 0.0f, 0.0f,-1.0f ); // Front face
    D3DVECTOR n1( 0.0f, 0.0f, 1.0f ); // Back face
    D3DVECTOR n2( 0.0f,-1.0f, 0.0f ); // Top face
    D3DVECTOR n3( 0.0f, 1.0f, 0.0f ); // Bottom face
    D3DVECTOR n4(-1.0f, 0.0f, 0.0f ); // Right face
    D3DVECTOR n5( 1.0f, 0.0f, 0.0f ); // Left face

    // Set up the vertices for the cube. Note: to prevent tiling problems,
    // the u/v coords are knocked slightly inwards.

    // Front face
    *pVertices++ = D3DVERTEX( D3DVECTOR(-1.0f, 1.0f,-1.0f), n0, 0.01f, 0.99f );
    *pVertices++ = D3DVERTEX( D3DVECTOR( 1.0f, 1.0f,-1.0f), n0, 0.99f, 0.99f );
    *pVertices++ = D3DVERTEX( D3DVECTOR( 1.0f,-1.0f,-1.0f), n0, 0.99f, 0.01f );
    *pVertices++ = D3DVERTEX( D3DVECTOR(-1.0f,-1.0f,-1.0f), n0, 0.01f, 0.01f );

    // Back face
    *pVertices++ = D3DVERTEX( D3DVECTOR(-1.0f, 1.0f, 1.0f), n1, 0.99f, 0.99f );
    *pVertices++ = D3DVERTEX( D3DVECTOR(-1.0f,-1.0f, 1.0f), n1, 0.99f, 0.01f );
    *pVertices++ = D3DVERTEX( D3DVECTOR( 1.0f,-1.0f, 1.0f), n1, 0.01f, 0.01f );
    *pVertices++ = D3DVERTEX( D3DVECTOR( 1.0f, 1.0f, 1.0f), n1, 0.01f, 0.99f );

    // Top face
    *pVertices++ = D3DVERTEX( D3DVECTOR(-1.0f, 1.0f, 1.0f), n2, 0.01f, 0.99f );
    *pVertices++ = D3DVERTEX( D3DVECTOR( 1.0f, 1.0f, 1.0f), n2, 0.99f, 0.99f );
    *pVertices++ = D3DVERTEX( D3DVECTOR( 1.0f, 1.0f,-1.0f), n2, 0.99f, 0.01f );
    *pVertices++ = D3DVERTEX( D3DVECTOR(-1.0f, 1.0f,-1.0f), n2, 0.01f, 0.01f );

    // Bottom face
    *pVertices++ = D3DVERTEX( D3DVECTOR(-1.0f,-1.0f, 1.0f), n3, 0.01f, 0.99f );
    *pVertices++ = D3DVERTEX( D3DVECTOR(-1.0f,-1.0f,-1.0f), n3, 0.01f, 0.01f );
    *pVertices++ = D3DVERTEX( D3DVECTOR( 1.0f,-1.0f,-1.0f), n3, 0.99f, 0.01f );
    *pVertices++ = D3DVERTEX( D3DVECTOR( 1.0f,-1.0f, 1.0f), n3, 0.99f, 0.99f );

    // Right face
    *pVertices++ = D3DVERTEX( D3DVECTOR( 1.0f, 1.0f,-1.0f), n4, 0.01f, 0.99f );
    *pVertices++ = D3DVERTEX( D3DVECTOR( 1.0f, 1.0f, 1.0f), n4, 0.99f, 0.99f );
    *pVertices++ = D3DVERTEX( D3DVECTOR( 1.0f,-1.0f, 1.0f), n4, 0.99f, 0.01f );
    *pVertices++ = D3DVERTEX( D3DVECTOR( 1.0f,-1.0f,-1.0f), n4, 0.01f, 0.01f );

    // Left face
    *pVertices++ = D3DVERTEX( D3DVECTOR(-1.0f, 1.0f,-1.0f), n5, 0.99f, 0.99f );
    *pVertices++ = D3DVERTEX( D3DVECTOR(-1.0f,-1.0f,-1.0f), n5, 0.99f, 0.01f );
    *pVertices++ = D3DVERTEX( D3DVECTOR(-1.0f,-1.0f, 1.0f), n5, 0.01f, 0.01f );
    *pVertices++ = D3DVERTEX( D3DVECTOR(-1.0f, 1.0f, 1.0f), n5, 0.01f, 0.99f );

    // Set up the indices for the cube
    *pIndices++ =  0+0;   *pIndices++ =  0+1;   *pIndices++ =  0+2;
    *pIndices++ =  0+2;   *pIndices++ =  0+3;   *pIndices++ =  0+0;
    *pIndices++ =  4+0;   *pIndices++ =  4+1;   *pIndices++ =  4+2;
    *pIndices++ =  4+2;   *pIndices++ =  4+3;   *pIndices++ =  4+0;
    *pIndices++ =  8+0;   *pIndices++ =  8+1;   *pIndices++ =  8+2;
    *pIndices++ =  8+2;   *pIndices++ =  8+3;   *pIndices++ =  8+0;
    *pIndices++ = 12+0;   *pIndices++ = 12+1;   *pIndices++ = 12+2;
    *pIndices++ = 12+2;   *pIndices++ = 12+3;   *pIndices++ = 12+0;
    *pIndices++ = 16+0;   *pIndices++ = 16+1;   *pIndices++ = 16+2;
    *pIndices++ = 16+2;   *pIndices++ = 16+3;   *pIndices++ = 16+0;
    *pIndices++ = 20+0;   *pIndices++ = 20+1;   *pIndices++ = 20+2;
    *pIndices++ = 20+2;   *pIndices++ = 20+3;   *pIndices++ = 20+0;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: App_OneTimeSceneInit()
// Desc: Called during initial app startup, this function performs all the
//       permanent initialization.
//-----------------------------------------------------------------------------
HRESULT App_OneTimeSceneInit( HWND hWnd )
{
    HRESULT hr;

    // Generate the cube data
    CreateCube( g_pVertices, g_pIndices );

    // Create a 128x128x16 dummy texture that will be used to create the
	// dynamic video texture.
    if( FAILED( hr = D3DTextr_CreateTexture( "videotex.bmp" ) ) )
    {
        MessageBox( hWnd, "Can't find VideoTex.bmp file.", g_strAppTitle,
                    MB_ICONERROR|MB_OK );
        return E_FAIL;
    }

    // Initialize the AVI library
    AVIFileInit();

    // Open our AVI file
    if( FAILED( hr = AVIStreamOpenFromFile( &g_paviStream, "skiing.avi",
                                            streamtypeVIDEO, 0, OF_READ,
                                            NULL ) ) )
    {
        // If the AVI was not found, let's check the system registry for an
        // alternate path.
        HKEY key;
        LONG result = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
                                    TEXT("Software\\Microsoft\\DirectX"),
                                    0, KEY_READ, &key );
        if( ERROR_SUCCESS == result )
        {
            TCHAR strFullPath[512];
            TCHAR strPath[512];
            DWORD type, size = 512;
            result = RegQueryValueEx( key, TEXT("DX6SDK Samples Path"), NULL,
                                      &type, (BYTE*)strPath, &size );
            RegCloseKey( key );

            if( ERROR_SUCCESS == result )
            {
                sprintf( strFullPath, TEXT("%s\\D3DIM\\Media\\%s"), strPath,
                           "skiing.avi");
                hr = AVIStreamOpenFromFile( &g_paviStream, strFullPath,
                                            streamtypeVIDEO, 0, OF_READ, NULL );
            }
        }

        // If the AVI was still not found, return failure.
        if( FAILED( hr ) )
        {
            MessageBox( hWnd, "Can't find Skiing.avi file.", g_strAppTitle,
                        MB_ICONERROR|MB_OK );
            return E_FAIL;
        }
    }

    // Load the video stream
    if( NULL == ( g_pgfFrame = AVIStreamGetFrameOpen( g_paviStream, NULL ) ) )
        return E_FAIL;

    // Get the stream info
    if( FAILED( hr = AVIStreamInfo( g_paviStream, &g_psiStreamInfo,
                                    sizeof(AVISTREAMINFO) ) ) )
        return E_FAIL;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: App_FrameMove()
// Desc: Called once per frame, the call is the entry point for animating
//       the scene.
//-----------------------------------------------------------------------------
HRESULT App_FrameMove( LPDIRECT3DDEVICE3 pd3dDevice, FLOAT fTimeKey )
{
	// Rotate the cube
	D3DMATRIX matRotate;
	D3DUtil_SetRotateYMatrix( matRotate, fTimeKey );
    pd3dDevice->SetTransform( D3DTRANSFORMSTATE_WORLD, &matRotate );

    // Update the AVI frame in the texture
    UpdateVideoTexture( g_ptexVideoTexture, &g_psiStreamInfo, g_pgfFrame );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: App_Render()
// Desc: Called once per frame, the call is the entry point for 3d
//       rendering. This function sets up render states, clears the
//       viewport, and renders the scene.
//-----------------------------------------------------------------------------
HRESULT App_Render( LPDIRECT3DDEVICE3 pd3dDevice,
                    LPDIRECT3DVIEWPORT3 pvViewport, D3DRECT* prcViewRect )
{
    //Clear the viewport
    pvViewport->Clear2( 1UL, prcViewRect, D3DCLEAR_TARGET, 0x000000ff,
		                1.0f, 0L );

    // Begin the scene
    if( FAILED( pd3dDevice->BeginScene() ) )
        return S_OK; // Don't return a "fatal" error

    // Draw the cube
    pd3dDevice->SetTexture( 0, g_ptexVideoTexture );

	pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, D3DFVF_VERTEX,
                                      g_pVertices, NUM_CUBE_VERTICES,
                                      g_pIndices,  NUM_CUBE_INDICES, 0 );

	// End the scene.
    pd3dDevice->EndScene();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: App_InitDeviceObjects()
// Desc: Initialize scene objects.
//-----------------------------------------------------------------------------
HRESULT App_InitDeviceObjects( LPDIRECT3DDEVICE3 pd3dDevice,
                               LPDIRECT3DVIEWPORT3 pvViewport )
{
    // Check parameters
    if( NULL==pd3dDevice || NULL==pvViewport )
        return E_INVALIDARG;

	// Restore the app's textures
    D3DTextr_RestoreAllTextures( pd3dDevice );

    // Set up the dynamic video texture, which is created from a dummy
	// (static) texture, but with the DDSCAPS2_HINTDYNAMIC flag set.
	if( FAILED( CreateDynamicTexture( D3DTextr_GetSurface("videotex.bmp"), 
									  &g_ptexVideoTexture ) ) )
		return E_FAIL;

	// Set the device state's for rendering
    pd3dDevice->SetRenderState( D3DRENDERSTATE_TEXTUREPERSPECTIVE , TRUE );
    pd3dDevice->SetRenderState( D3DRENDERSTATE_DITHERENABLE, TRUE );
    pd3dDevice->SetRenderState( D3DRENDERSTATE_SPECULARENABLE, TRUE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_MINFILTER, D3DTFN_LINEAR );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_MAGFILTER, D3DTFG_LINEAR );
    
    // Get the viewport dimensions (used for the projection matrix)
    D3DVIEWPORT2 vp;
    vp.dwSize = sizeof(D3DVIEWPORT2);
    pvViewport->GetViewport2(&vp);
    FLOAT fAspect = ((FLOAT)vp.dwHeight) / vp.dwWidth;

    // Set the world, view, and projection matrices
    D3DMATRIX matWorld, matView, matProj;
    D3DVECTOR vEyePt    = D3DVECTOR( 0.0f, 2.0f, -3.0f );
    D3DVECTOR vLookatPt = D3DVECTOR( 0.0f, 0.0f,  0.0f );
    D3DVECTOR vUpVec    = D3DVECTOR( 0.0f, 1.0f,  0.0f );
    D3DUtil_SetIdentityMatrix( matWorld );
    D3DUtil_SetViewMatrix( matView, vEyePt, vLookatPt, vUpVec );
    D3DUtil_SetProjectionMatrix( matProj, g_PI/4, fAspect, 1.0f, 100.0f );
    pd3dDevice->SetTransform( D3DTRANSFORMSTATE_WORLD,      &matWorld );
    pd3dDevice->SetTransform( D3DTRANSFORMSTATE_VIEW,       &matView );
    pd3dDevice->SetTransform( D3DTRANSFORMSTATE_PROJECTION, &matProj );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: App_FinalCleanup()
// Desc: Called before the app exits, this function gives the app the chance
//       to cleanup after itself.
//-----------------------------------------------------------------------------
HRESULT App_FinalCleanup( LPDIRECT3DDEVICE3 pd3dDevice,
                          LPDIRECT3DVIEWPORT3 pvViewport )
{
    App_DeleteDeviceObjects( pd3dDevice, pvViewport );

    // Release the AVI file stream, and close the AVI library
    AVIStreamRelease( g_paviStream );
    AVIFileExit();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: App_DeleteDeviceObjects()
// Desc: Called when the app is exitting, or the device is being changed,
//       this function deletes any device dependant objects.
//-----------------------------------------------------------------------------
VOID App_DeleteDeviceObjects( LPDIRECT3DDEVICE3 pd3dDevice,
                              LPDIRECT3DVIEWPORT3 pvViewport )
{
    D3DTextr_InvalidateAllTextures();
    
    SAFE_RELEASE( g_ptexVideoTexture );
}




//----------------------------------------------------------------------------
// Name: App_RestoreSurfaces
// Desc: Restores any previously lost surfaces. Must do this for all surfaces
//       (including textures) that the app created.
//----------------------------------------------------------------------------
HRESULT App_RestoreSurfaces()
{
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: App_ConfirmDevice()
// Desc: Called during device intialization, this code checks the device
//       for some minimum set of capabilities
//-----------------------------------------------------------------------------
HRESULT App_ConfirmDevice( DDCAPS* pddDriverCaps,
                           D3DDEVICEDESC* pd3dDeviceDesc )
{
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CreateDynamicTexture()
// Desc: This function creates a surface and texture using the
//       DDSCAPS2_HINTDYNAMIC flag. The rest of the surface attributes are
//       copied from the (non-dynamic) dummy surface.
//-----------------------------------------------------------------------------
HRESULT CreateDynamicTexture( LPDIRECTDRAWSURFACE4 pddsStaticSurface,
							  LPDIRECT3DTEXTURE2* pptexDynamicTexture )
{
	LPDIRECTDRAWSURFACE4 pddsDynamicSurface;
	LPDIRECTDRAW4        pDD;
	DDSURFACEDESC2       ddsd;
	HRESULT              hr;

	// Get the static surface description
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	pddsStaticSurface->GetSurfaceDesc( &ddsd );

	// Set the caps bits for the dynamic texture's surface
	ddsd.ddsCaps.dwCaps  &= ~(DDSCAPS_SYSTEMMEMORY|DDSCAPS_VIDEOMEMORY);
	ddsd.ddsCaps.dwCaps2 &= ~(DDSCAPS2_HINTSTATIC|DDSCAPS2_OPAQUE);
	ddsd.ddsCaps.dwCaps2 |= DDSCAPS2_HINTDYNAMIC;

	// Get a ptr to DDraw (to create the dynamic surface)
	if( SUCCEEDED( hr = pddsStaticSurface->GetDDInterface( (VOID**)&pDD ) ) )
	{
		// Create the video texture surface
		if( SUCCEEDED( hr = pDD->CreateSurface( &ddsd, &pddsDynamicSurface,
			                                    NULL ) ) )
		{
			// Finally, create the video texture itself
			hr = pddsDynamicSurface->QueryInterface( IID_IDirect3DTexture2, 
				                                 (VOID**)pptexDynamicTexture );
			pddsDynamicSurface->Release();
		}

		pDD->Release();
	}

	return hr;
}




//-----------------------------------------------------------------------------
// Name: UpdateVideoTexture()
// Desc: Called once per frame, updates the texture with the next video frame.
//-----------------------------------------------------------------------------
HRESULT UpdateVideoTexture( LPDIRECT3DTEXTURE2 ptexTexture, 
						    AVISTREAMINFO* psiStreamInfo, PGETFRAME pgfFrame )
{
    // Save the start time of the AVI file
    static FLOAT fAVIStartTime = ((FLOAT)clock())/CLOCKS_PER_SEC;

    // Use the clock to find which frame we should be drawing
    FLOAT fCurrTime     = ((FLOAT)clock())/CLOCKS_PER_SEC;
    FLOAT fElapsedTime  = fCurrTime-fAVIStartTime;
    FLOAT fAVITimeScale = ((FLOAT)psiStreamInfo->dwRate) / psiStreamInfo->dwScale;
    DWORD dwCurrFrame   = (DWORD)( fElapsedTime * fAVITimeScale );

    // If we exceed the AVI length, wrap to the start of the AVI
    if( dwCurrFrame >= psiStreamInfo->dwLength )
    {
        fAVIStartTime = ((FLOAT)clock())/CLOCKS_PER_SEC;
        dwCurrFrame   = psiStreamInfo->dwStart + 1;
    }

    // Get the current frame of the video
    BITMAPINFO* pbmi;
    if( FAILED( pbmi = (LPBITMAPINFO)AVIStreamGetFrame( pgfFrame, dwCurrFrame ) ) )
        return E_FAIL;

    // Get the texture's surface
	LPDIRECTDRAWSURFACE4 pddsTexture = NULL;
	if( FAILED( ptexTexture->QueryInterface( IID_IDirectDrawSurface4, 
		                                     (VOID**)&pddsTexture ) ) )
		return E_FAIL;

    // Lock the surface so we can access it's bits
    DDSURFACEDESC2 ddsd;
    ddsd.dwSize = sizeof(DDSURFACEDESC2);
    pddsTexture->Lock( NULL, &ddsd, DDLOCK_WRITEONLY, NULL );

    // Check the surface's pixel format. Depending on the device and hardware
    // we're using, the system could create either 565 or 555 format 16 bit
    // surfaces. This app fuddles with texture bits, so we need to know what
    // format we're writing the AVI images to.
    BOOL bTextureIs565 = (ddsd.ddpfPixelFormat.dwGBitMask==0x7E0)?TRUE:FALSE;

    // Copy the current frame image to the surface. We recieve the video data
    // as a void pointer to a packed DIB. We have to skip past the header that
    // preceeds the raw video data.
    WORD* pSrc  = (WORD*)( sizeof(BITMAPINFO) + (BYTE*)pbmi );
    WORD* pDest = (WORD*)ddsd.lpSurface;

    // Copy the bits, pixel by pixel. Note that we need to handle the 565 and
    // 555 formats diffrently.
    if( bTextureIs565 )
    {
        for( DWORD i=0; i < 128*128; i++ )
        {
            WORD color = *pSrc++;
            *pDest++ = ((color & 0x1F)|((color & 0xFFE0)<<1));
        }
    }
    else
        memcpy( pDest, pSrc, sizeof(WORD)*128*128 );

    // We're done. Unlock the texture surface and return.
    pddsTexture->Unlock(NULL);
	pddsTexture->Release();

    return S_OK;
}




