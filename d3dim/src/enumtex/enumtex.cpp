//-----------------------------------------------------------------------------
// Name: EnumTex.cpp
//
// Desc: Simple command-line app to show how to enumerate texture formats.
//
// Copyright (c) 1998 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#define  INITGUID
#include <d3d.h>
#include <string.h>
#include <stdio.h>




//-----------------------------------------------------------------------------
// Global variables for storing enumerated texture formats
//-----------------------------------------------------------------------------
#define ENUMTEXERR_BADALPHABITCOUNT   0x80000001
#define ENUMTEXERR_BADALPHAPIXELSFLAG 0x80000002
#define ENUMTEXERR_BADBITCOUNT        0x80000003
#define ENUMTEXERR_BADALPHAFLAGS      0x80000004
#define ENUMTEXERR_BADFOURCCBITCOUNT  0x80000005
#define ENUMTEXERR_BADFOURCCFLAGS     0x80000006
#define ENUMTEXERR_UNKNOWNFORMAT      0x80000007

#define MAX_NUM_FORMATS 64
DDPIXELFORMAT g_ddpfTextureFormatList[MAX_NUM_FORMATS];
DWORD         g_dwNumTextureFormats = 0;




//-----------------------------------------------------------------------------
// Name: TextureEnumerationCallback()
// Desc: Callback used by the texture enumeration process. Builds a global
//       list of texture formats.
//-----------------------------------------------------------------------------
HRESULT CALLBACK TextureEnumerationCallback( DDPIXELFORMAT* pddpf, VOID* )
{
    g_ddpfTextureFormatList[g_dwNumTextureFormats++] = (*pddpf);

    return DDENUMRET_OK;
}




//-----------------------------------------------------------------------------
// Name: BuildTextureFormatList()
// Desc: Creates a D3DDevice, and uses it to enumerate all available texture
//       formats for that device.
//-----------------------------------------------------------------------------
HRESULT BuildTextureFormatList( GUID deviceGUID )
{
    // Local variables for DirectX objects
    HRESULT              hr;
    LPDIRECTDRAW         pDD1        = NULL;
    LPDIRECTDRAW4        pDD         = NULL;
    LPDIRECT3D3          pD3D        = NULL;
    LPDIRECTDRAWSURFACE4 pddsSurface = NULL;
    LPDIRECT3DDEVICE3    pd3dDevice  = NULL;
    DDSURFACEDESC2       ddsd;

    // Structure for creating a surface
    ZeroMemory( &ddsd, sizeof(ddsd) );
    ddsd.dwSize         = sizeof( ddsd );
    ddsd.dwFlags        = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_3DDEVICE;

    // Create the DirectDraw object
    hr = DirectDrawCreate( NULL, &pDD1, NULL );
    if( FAILED( hr ) )
    {
        printf( "Could not create DirectDraw!\n" );
        return hr;
    }

    // Create the DirectDraw4 object
    hr = pDD1->QueryInterface( IID_IDirectDraw4, (VOID**)&pDD );
    pDD1->Release();
    if( FAILED( hr ) )
    {
        printf( "Could not create a DirectDraw4 interface!\n" );
        return hr;
    }

    // Set the cooperative level
    hr = pDD->SetCooperativeLevel( NULL, DDSCL_NORMAL );
    if( FAILED( hr ) )
    {
        printf( "Could not set the DirectDraw cooperative level!\n" );
        return hr;
    }

    // Create the Direct3D object
    hr = pDD->QueryInterface( IID_IDirect3D3, (VOID**)&pD3D );
    if( FAILED( hr ) )
    {
        pDD->Release();
        printf( "Could not create a Direct3D interface!\n" );
        return hr;
    }

    // Create a DirectDraw surface
    hr = pDD->CreateSurface( &ddsd, &pddsSurface, NULL );
    if( FAILED( hr ) )
    {
        pD3D->Release();
        pDD->Release();
        printf( "Could not create a DirectDraw surface!\n" );
        return hr;
    }

    // Create a Direct3D device
    hr = pD3D->CreateDevice( deviceGUID, pddsSurface, &pd3dDevice, NULL );
    if( FAILED( hr ) )
    {
        pddsSurface->Release();
        pD3D->Release();
        pDD->Release();
        printf( "Could not create a Direct3DDevice! Try changing your color depth to 16-bit.\n" );
        return hr;
    }

    // Enumerate the device's texture formats
    hr = pd3dDevice->EnumTextureFormats( TextureEnumerationCallback, NULL );
    if( FAILED( hr ) )
    {
        pd3dDevice->Release();
        pddsSurface->Release();
        pD3D->Release();
        pDD->Release();
        printf( "Could not enumerate texture formats!\n" );
        return hr;
    }

    // Release objects and return successfully
    pd3dDevice->Release();
    pddsSurface->Release();
    pD3D->Release();
    pDD->Release();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: main()
// Desc: Entrance point for console-based aps
//-----------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
    // Select a device
    GUID deviceGUID = IID_IDirect3DHALDevice;
    if( argc > 1 )
    {
        if( 0 == strcmp( argv[1], "-HAL" ) || 0 == strcmp( argv[1], "-hal" ) )
            deviceGUID = IID_IDirect3DHALDevice;
        if( 0 == strcmp( argv[1], "-RGB" ) || 0 == strcmp( argv[1], "-rgb" ))
            deviceGUID = IID_IDirect3DRGBDevice;
        if( 0 == strcmp( argv[1], "-REF" ) || 0 == strcmp( argv[1], "-ref" ) )
            deviceGUID = IID_IDirect3DRefDevice;
    }

    // Use DirectDraw/Direct3D to build a list of a device's supported texture
    // formats.
    if( FAILED( BuildTextureFormatList( deviceGUID ) ) )
        return 0;

    // Loop through all supported formats, outputting info about each one.
    for( DWORD i=0; i<g_dwNumTextureFormats; i++ )
    {
        DWORD dwError         = 0;
        DWORD dwFlags         = g_ddpfTextureFormatList[i].dwFlags;
        DWORD dwFourCC        = g_ddpfTextureFormatList[i].dwFourCC;
        DWORD dwTotalBitCount = g_ddpfTextureFormatList[i].dwRGBBitCount;
        DWORD dwAlphaBitCount = 0;
        DWORD dwRedBitCount   = 0;
        DWORD dwGreenBitCount = 0;
        DWORD dwBlueBitCount  = 0;
        DWORD mask;

        // Count number of bits for each color component
        for( mask = g_ddpfTextureFormatList[i].dwRGBAlphaBitMask; mask; mask>>=1 )
            dwAlphaBitCount += ( mask & 0x1 );
        for( mask = g_ddpfTextureFormatList[i].dwRBitMask; mask; mask>>=1 )
            dwRedBitCount += ( mask & 0x1 );
        for( mask = g_ddpfTextureFormatList[i].dwGBitMask; mask; mask>>=1 )
            dwGreenBitCount += ( mask & 0x1 );
        for( mask = g_ddpfTextureFormatList[i].dwBBitMask; mask; mask>>=1 )
            dwBlueBitCount += ( mask & 0x1 );

        // Check for invalid formats
        if( ( dwFlags & DDPF_ALPHAPIXELS ) && ( dwAlphaBitCount == 0 ) )
            dwError = ENUMTEXERR_BADALPHABITCOUNT;
        if( !( dwFlags & DDPF_ALPHAPIXELS ) && ( dwAlphaBitCount != 0 ) )
            dwError = ENUMTEXERR_BADALPHAPIXELSFLAG;
        if( !(dwFlags & DDPF_FOURCC ) && dwTotalBitCount == 0 )
            dwError = ENUMTEXERR_BADBITCOUNT;

        // Output info about the current texture format.
        printf( "Format %2d: ", i+1 );

        if( dwFlags & DDPF_ALPHA )
        {
            // Alpha-only formats
            if( ( dwFlags & DDPF_ALPHA ) && ( dwFlags != DDPF_ALPHA ) )
                dwError = ENUMTEXERR_BADALPHAFLAGS;

            printf( "%d-bit, alpha-only format.\n", dwTotalBitCount );

            if( !dwError )
            {
                // Note: If you want this format, accept it here
            }
        }
        else if( dwFlags & DDPF_BUMPLUMINANCE )
        {
            // Bumpmap formats
            printf( "%d-bit, bump luminance format.\n", dwTotalBitCount );

            if( !dwError )
            {
                // Note: If you want this format, accept it here
            }
        }
        else if( dwFlags & DDPF_BUMPDUDV )
        {
            // More bumpmap formats
            printf( "%d-bit, bump format.\n", dwTotalBitCount );

            if( !dwError )
            {
                // Note: If you want this format, accept it here
            }
        }
        else if( dwFlags & DDPF_LUMINANCE )
        {
            // Luminance formats. Check whether format also has alpha.
            if( dwAlphaBitCount )
                printf( "%d-bit luminance, %d-bit alpha format.\n",
                        dwTotalBitCount-dwAlphaBitCount, dwAlphaBitCount );
            else
                printf( "%d-bit luminance format.\n", dwTotalBitCount );

            if( !dwError )
            {
                // Note: If you want this format, accept it here
            }
        }
        else if( dwFlags & DDPF_FOURCC )
        {
            // FourCC formats. Check for a valid format.
            if( dwTotalBitCount!=0 || dwRedBitCount!=0 || dwGreenBitCount!=0 ||
                dwBlueBitCount!=0 || dwAlphaBitCount!= 0 )
                dwError = ENUMTEXERR_BADFOURCCBITCOUNT;
            if( ( dwFlags & DDPF_FOURCC ) && ( dwFlags != DDPF_FOURCC ) )
                dwError = ENUMTEXERR_BADFOURCCFLAGS;
                            
            // Also check whether it is a DXT format.
            if( ( dwFourCC == FOURCC_DXT1 ) || ( dwFourCC == FOURCC_DXT2 ) ||
                ( dwFourCC == FOURCC_DXT3 ) || ( dwFourCC == FOURCC_DXT4 ) ||
                ( dwFourCC == FOURCC_DXT5 ) )
                printf( "DXTn " );
            
            printf( "FourCC (%c%c%c%c), format.\n", dwFourCC&0xff,
                    ((dwFourCC>>8)&0xff), ((dwFourCC>>16)&0xff),
                    ((dwFourCC>>24)&0xff) );

            if( !dwError )
            {
                // Note: If you want this format, accept it here
            }
        }
        else if( dwFlags & (DDPF_PALETTEINDEXED1|DDPF_PALETTEINDEXED2|
                            DDPF_PALETTEINDEXED4|DDPF_PALETTEINDEXED8) )
        {
            // Palettized formats
            if( dwAlphaBitCount )
                printf( "%d-bit palettized format with %d-bit alpha.\n",
                        dwTotalBitCount - dwAlphaBitCount, dwAlphaBitCount );
            else
                printf( "%d-bit palettized format.\n", dwTotalBitCount );

            if( !dwError )
            {
                // Note: If you want this format, accept it here
            }
        }
        else if( dwFlags & DDPF_RGB )
        {
            // RGB formats
            if( dwAlphaBitCount )
                printf( "%d%d%d%d ARGB (%d-bit) format.\n", dwAlphaBitCount,
                        dwRedBitCount, dwGreenBitCount, dwBlueBitCount,
                        dwTotalBitCount );
            else
                printf( "%d%d%d RGB (%d-bit) format.\n", dwRedBitCount,
                        dwGreenBitCount, dwBlueBitCount, dwTotalBitCount );

            if( !dwError )
            {
                // Note: If you want this format, accept it here
            }
        }
        else
        {
            // Unknown formats
            dwError = ENUMTEXERR_UNKNOWNFORMAT;

            printf( "%d-bit unknown format.\n", dwTotalBitCount );

            // Note: Never accept an unknown format
        }

        // Print out error message
        if( dwError == ENUMTEXERR_BADALPHABITCOUNT )
            printf( "*** Error: DDPF_ALPHAPIXELS flag set with zero alpha mask!\n" );
        if( dwError == ENUMTEXERR_BADALPHAPIXELSFLAG )
            printf( "*** Error: Alpha bit mask set without DDPF_ALPHAPIXELS flag set!\n" );
        if( dwError == ENUMTEXERR_BADBITCOUNT )
            printf( "*** Error: Format has zero bit count!\n" );
        if( dwError == ENUMTEXERR_BADALPHAFLAGS )
            printf( "*** Error: Other flags illegally combined with DDPF_ALPHA!\n" );
        if( dwError == ENUMTEXERR_BADFOURCCBITCOUNT )
            printf( "*** Error: FourCC code has non-zero bitcount.\n" );
        if( dwError == ENUMTEXERR_BADFOURCCFLAGS )
            printf( "*** Error: Other flags illegally combined with DDPF_FOURCC!\n" );
        if( dwError == ENUMTEXERR_UNKNOWNFORMAT )
            printf( "*** Warning: Unkown format!\n" );
    }

    // Exit program
    return 0;
}




