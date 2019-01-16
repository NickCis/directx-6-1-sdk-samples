//-----------------------------------------------------------------------------
// File: Bend.cpp
//
// Desc: Example code showing how to do a skinning effect. The code
//       does a linear interplation on two meshes of an ellipsoid,
//       resulting in a visual "bending" effect, with smooth skin.
//
//       Note: This code uses the D3D Framework helper library.
//
//
// Copyright (c) 1997-1998 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#define STRICT
#define D3D_OVERLOADS
#include <math.h>
#include "D3DTextr.h"
#include "D3DUtil.h"
#include "D3DMath.h"


//-----------------------------------------------------------------------------
// Declare the application globals for use in WinMain.cpp
//-----------------------------------------------------------------------------
TCHAR* g_strAppTitle       = TEXT( "Bend: Surface Skinning Example" );
BOOL   g_bAppUseZBuffer    = TRUE;    // Create/use a z-buffering
BOOL   g_bAppUseBackBuffer = TRUE;    // Create/use a back buffer




//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------
#define ELLIPSE_NUMRINGS    20
#define ELLIPSE_NUMSECTIONS 20
#define ELLIPSE_X_LENGTH    1.5f
#define ELLIPSE_Y_LENGTH    4.5f
#define ELLIPSE_Z_LENGTH    1.5f

LPDIRECT3DMATERIAL3 g_pmtrlObjectMtrl     = NULL;
LPDIRECT3DLIGHT     g_pLight              = NULL;
D3DVERTEX* g_pvModelVertices1 = NULL;            //object's vertices
D3DVERTEX* g_pvModelVertices2 = NULL;            //object's vertices
D3DVERTEX* g_pvRenderVertices = NULL;            //object's vertices
DWORD      g_dwNumVertices;




//-----------------------------------------------------------------------------
// Function prototypes and global (or static) variables
//-----------------------------------------------------------------------------
VOID    AppPause( BOOL );
VOID    RotateVertexInX( FLOAT, DWORD, D3DVERTEX*, D3DVERTEX* );
VOID    BlendObjects( DWORD, D3DVERTEX*, D3DVERTEX*, D3DVERTEX* );
VOID    GenerateEllipse( DWORD, DWORD, FLOAT, FLOAT, FLOAT,
                         D3DVERTEX**, DWORD* );




//-----------------------------------------------------------------------------
// Name: App_OneTimeSceneInit()
// Desc: Called during initial app startup, this function performs all the
//       permanent initialization.
//-----------------------------------------------------------------------------
HRESULT App_OneTimeSceneInit( HWND hWnd )
{
    // Generate the object data
    GenerateEllipse( ELLIPSE_NUMRINGS, ELLIPSE_NUMSECTIONS, 
                    ELLIPSE_X_LENGTH, ELLIPSE_Y_LENGTH, ELLIPSE_Z_LENGTH, 
                    &g_pvRenderVertices, &g_dwNumVertices );
    RotateVertexInX( (FLOAT)(g_PI/2), g_dwNumVertices, g_pvRenderVertices,
                     g_pvRenderVertices );

    // Make two copies of the object (for modification of the vertices)
    g_pvModelVertices1 = new D3DVERTEX[g_dwNumVertices];
    g_pvModelVertices2 = new D3DVERTEX[g_dwNumVertices];

    for( DWORD i=0; i<g_dwNumVertices; i++ )
    {
        g_pvModelVertices1[i] = g_pvRenderVertices[i];
        g_pvModelVertices2[i] = g_pvRenderVertices[i];
    }

    // Create textures
    D3DTextr_CreateTexture( "Banana.bmp" );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: App_FrameMove()
// Desc: Called once per frame, the call is the entry point for animating
//       the scene.
//-----------------------------------------------------------------------------
HRESULT App_FrameMove( LPDIRECT3DDEVICE3 pd3dDevice, FLOAT fTimeKey )
{
    // Compute the bend and rotate angles for this frame
    static FLOAT fTime = 0.0f;
    FLOAT fRotateAngle = (FLOAT)( fTime / 7 );
    FLOAT fBendAngle   = (FLOAT)( (sin(fTime)+1.0f)*0.6f );
    fTime += .05f;

    // Setup the world spin matrix
    D3DMATRIX matWorldSpin;
    D3DUtil_SetRotateYMatrix( matWorldSpin, fRotateAngle );
    pd3dDevice->SetTransform( D3DTRANSFORMSTATE_WORLD, &matWorldSpin );

    // Bend two copies of the object in different directions and 
    // merge (blend) them into one set of vertex data.
    RotateVertexInX( fBendAngle, g_dwNumVertices, g_pvModelVertices2,
                     g_pvModelVertices1 );
    BlendObjects( g_dwNumVertices, g_pvModelVertices1, g_pvModelVertices2,
                  g_pvRenderVertices );

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
    pvViewport->Clear2( 1UL, prcViewRect, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
                        0x000000ff, 1.0f, 0L );

    // Begin the scene 
    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
        //Display the object
        pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, D3DFVF_VERTEX,
                                   g_pvRenderVertices, g_dwNumVertices, NULL );

        // End the scene.
        pd3dDevice->EndScene();
    }

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

    // Get a ptr to the ID3D object to create materials and/or lights. Note:
    // the Release() call just serves to decrease the ref count.
    LPDIRECT3D3 pD3D;
    if( FAILED( pd3dDevice->GetDirect3D( &pD3D ) ) )
        return E_FAIL;
    pD3D->Release();

    HRESULT           hr;
    D3DMATERIAL       mtrl;
    D3DMATERIALHANDLE hmtrl;
    
    // Create and set up the object material
    if( FAILED( hr = pD3D->CreateMaterial( &g_pmtrlObjectMtrl, NULL ) ) )
        return E_FAIL;

    D3DUtil_InitMaterial( mtrl, 1.0f, 1.0f, 1.0f );
    mtrl.power = 40.0f;
    g_pmtrlObjectMtrl->SetMaterial( &mtrl );
    g_pmtrlObjectMtrl->GetHandle( pd3dDevice, &hmtrl );
    pd3dDevice->SetLightState(  D3DLIGHTSTATE_MATERIAL, hmtrl );
    pd3dDevice->SetLightState(  D3DLIGHTSTATE_AMBIENT,  0x40404040 );

    D3DTextr_RestoreAllTextures( pd3dDevice );
    pd3dDevice->SetTexture( 0, D3DTextr_GetTexture("Banana.bmp") );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_MINFILTER, D3DTFN_LINEAR );
    pd3dDevice->SetTextureStageState( 0, D3DTSS_MAGFILTER, D3DTFG_LINEAR );
    pd3dDevice->SetRenderState( D3DRENDERSTATE_DITHERENABLE, TRUE );
    pd3dDevice->SetRenderState( D3DRENDERSTATE_SPECULARENABLE, TRUE );

    // Set the transform matrices
    D3DVECTOR vEyePt    = D3DVECTOR( 0, 0, -6.5 );
    D3DVECTOR vLookatPt = D3DVECTOR( 0, 0,   0  );
    D3DVECTOR vUpVec    = D3DVECTOR( 0, 1,   0  );
    D3DMATRIX matWorld, matView, matProj;

    D3DUtil_SetIdentityMatrix( matWorld );
    D3DUtil_SetViewMatrix( matView, vEyePt, vLookatPt, vUpVec );
    D3DUtil_SetProjectionMatrix( matProj, 1.57f, 1.0f, 1.0f, 100.0f );

    pd3dDevice->SetTransform( D3DTRANSFORMSTATE_WORLD,      &matWorld );
    pd3dDevice->SetTransform( D3DTRANSFORMSTATE_VIEW,       &matView );
    pd3dDevice->SetTransform( D3DTRANSFORMSTATE_PROJECTION, &matProj );

    pd3dDevice->SetRenderState( D3DRENDERSTATE_ZENABLE, 1 );

    // Set up the light
    if( FAILED( hr = pD3D->CreateLight( &g_pLight, NULL ) ) )
        return E_FAIL;
    
    D3DLIGHT light;
    D3DUtil_InitLight( light, D3DLIGHT_POINT, 0.0, 0.0, -12.0 );
    light.dcvColor.r = D3DVAL(0.9);
    light.dcvColor.g = D3DVAL(0.9);
    light.dcvColor.b = D3DVAL(0.9);
    light.dvAttenuation0 = 1.0f;
    g_pLight->SetLight( &light );
    pvViewport->AddLight( g_pLight );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: App_DeleteDeviceObjects()
// Desc: Called when the app is exitting, or the device is being changed,
//       this function deletes any device dependant objects.
//-----------------------------------------------------------------------------
VOID App_DeleteDeviceObjects( LPDIRECT3DDEVICE3 pd3dDevice, 
                              LPDIRECT3DVIEWPORT3 pvViewport)
{
    D3DTextr_InvalidateAllTextures();

    SAFE_RELEASE( g_pLight );
    SAFE_RELEASE( g_pmtrlObjectMtrl );
}




//-----------------------------------------------------------------------------
// Name: App_FinalCleanup()
// Desc: Called before the app exits, this function gives the app the chance
//       to cleanup after itself.
//-----------------------------------------------------------------------------
HRESULT App_FinalCleanup( LPDIRECT3DDEVICE3 pd3dDevice, 
                          LPDIRECT3DVIEWPORT3 pvViewport)
{
    App_DeleteDeviceObjects( pd3dDevice, pvViewport );
    
    SAFE_DELETE( g_pvModelVertices1 );
    SAFE_DELETE( g_pvModelVertices2 );
    SAFE_DELETE( g_pvRenderVertices );

    return S_OK;
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
// Name: RotateVertexInX()
// Desc: Rotates an array of vertices by an amount theta about the x-axis.
//-----------------------------------------------------------------------------
VOID RotateVertexInX( FLOAT fTheta, DWORD dwCount,
                      D3DVERTEX* pvInVertices, D3DVERTEX* pvOutVertices )
{
    FLOAT fSin = (FLOAT)sin(fTheta); 
    FLOAT fCos = (FLOAT)cos(fTheta);
    
    for( DWORD i=0; i<dwCount; i++ )
    {
        FLOAT y = pvInVertices[i].y;
        FLOAT z = pvInVertices[i].z;
        pvOutVertices[i].y = fCos*y + fSin*z;
        pvOutVertices[i].z = -fSin*y + fCos*z;

        FLOAT ny = pvInVertices[i].ny;
        FLOAT nz = pvInVertices[i].nz;
        pvOutVertices[i].ny = fCos*ny + fSin*nz;
        pvOutVertices[i].nz = -fSin*ny + fCos*nz;
    }
}



//----------------------------------------------------------------------------
// Name: GenerateEllipse()
// Desc: Generates the vertices for a ellipse
//----------------------------------------------------------------------------
VOID GenerateEllipse( DWORD dwNumRings, DWORD dwNumSegments,
                      FLOAT fXScale, FLOAT fYScale, FLOAT fZScale,
                      D3DVERTEX** ppVertices, DWORD* pdwNumVertices )
{
    // Allocate space for the sphere
    D3DVERTEX* v    = new D3DVERTEX[2 * dwNumRings * (dwNumSegments+1)];
    *pdwNumVertices = 2 * dwNumRings * (dwNumSegments+1);
    *ppVertices     = v;

    // Establish constants used in sphere generation
    FLOAT fDeltaRingAngle = ( g_PI / dwNumRings );
    FLOAT fDeltaSegAngle  = ( 2.0f * g_PI / dwNumSegments );

    // Generate the group of rings for the sphere
    for( DWORD ring = 0; ring < dwNumRings; ring++ )
    {    
        FLOAT r0 = (FLOAT)sin( (ring+0) * fDeltaRingAngle );
        FLOAT r1 = (FLOAT)sin( (ring+1) * fDeltaRingAngle );
        FLOAT y0 = (FLOAT)cos( (ring+0) * fDeltaRingAngle );
        FLOAT y1 = (FLOAT)cos( (ring+1) * fDeltaRingAngle );

        // Generate the group of segments for the current ring
        for( DWORD seg = 0; seg < (dwNumSegments+1); seg++ )
        {
            FLOAT x0 =  r0 * (FLOAT)sin( seg * fDeltaSegAngle );
            FLOAT z0 =  r0 * (FLOAT)cos( seg * fDeltaSegAngle );
            FLOAT x1 =  r1 * (FLOAT)sin( seg * fDeltaSegAngle );
            FLOAT z1 =  r1 * (FLOAT)cos( seg * fDeltaSegAngle );

            // Add two vertices to the strip which makes up the sphere
            *v++ = D3DVERTEX( D3DVECTOR(fXScale*x0,fYScale*y0,fZScale*z0),
                              D3DVECTOR(x0,y0,z0), -((FLOAT)seg)/dwNumSegments,
                              (ring+0) / (FLOAT)dwNumRings );

            *v++ = D3DVERTEX( D3DVECTOR(fXScale*x1,fYScale*y1,fZScale*z1),
                              D3DVECTOR(x1,y1,z1), -((FLOAT)seg)/dwNumSegments,
                              (ring+1) / (FLOAT)dwNumRings );
        }
    }
}




//-----------------------------------------------------------------------------
// Name: BlendObjects()
// Desc: Merges two sets of vertices together
//-----------------------------------------------------------------------------
VOID BlendObjects( DWORD dwCount, D3DVERTEX* pvInputVertices1, 
                   D3DVERTEX* pvInputVertices2,
                   D3DVERTEX* pvOutputVertices )
{
    #define LERP(m,x0,x1)       ((x0) + (m)*((x1)-(x0)))
    
    D3DVERTEX* p1 = pvInputVertices1;
    D3DVERTEX* p2 = pvInputVertices2;
    D3DVERTEX* p3 = pvOutputVertices;

    for( DWORD i=0; i<dwCount; i++ )
    {
        FLOAT m;
        FLOAT a = ( p2->z + ELLIPSE_Y_LENGTH ) / ( 2*ELLIPSE_Y_LENGTH );

        if( a >= 0.75f )
            m = 0.0f;
        else if( a >= 0.5f )
        {
            FLOAT x = 4*(0.75f-a);
            m = (x*x)*0.5f;
        }
        else if( a >= 0.25f )
        {
            FLOAT x = 4*(a-0.25f);
            m = 1.0f-(x*x)*0.5f;
        }
        else
            m = 1.0f;

        p3->x = LERP( m, p1->x, p2->x );
        p3->y = LERP( m, p1->y, p2->y );
        p3->z = LERP( m, p1->z, p2->z );

        p1++; p2++; p3++;
    }
}




