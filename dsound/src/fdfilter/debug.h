/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:		debug.h
 *  Content:	debug header
 *
 ***************************************************************************/
#ifndef __DEBUG_INCLUDED__
#define __DEBUG_INCLUDED__
#ifdef __cplusplus
extern "C"
{
#endif

LPSTR TranslateDSError( HRESULT );

//
//
//
//
#if defined(DEBUG) || defined(_DEBUG)
    #define DEBUG_SECTION       "Debug"     // section name for 
    #define DEBUG_MODULE_NAME   "FDFILTER"    // key name and prefix for output
    #define DEBUG_MAX_LINE_LEN  255         // max line length (bytes!)
#endif


//
//  based code makes since only in win 16 (to try and keep stuff out of
//  [fixed] data segments, etc)...
//
#ifndef BCODE
#ifdef _WIN32
    #define BCODE
#else
    #define BCODE           _based(_segname("_CODE"))
#endif
#endif




//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;
//
//
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ;

#if defined(DEBUG) || defined(_DEBUG)
    BOOL WINAPI DbgEnable(BOOL fEnable);
    UINT WINAPI DbgGetLevel(void);
    UINT WINAPI DbgSetLevel(UINT uLevel);
    UINT WINAPI DbgInitialize(BOOL fEnable);
    void WINAPI _Assert( char * szFile, int iLine );
    void WINAPI DbgDumpWFX( int, PWAVEFORMATEX );

    void FAR CDECL dprintf(UINT uDbgLevel, LPSTR szFmt, ...);

    #define D(x)        {x;}
    // The DPFx macro turns into a dprintf call if compiling for debug
    #define DPF         dprintf
    #define DPF3        dprintf
    #define DPF4        dprintf
    #define DPF5        dprintf
    #define DPI(sz)     {static char BCODE ach[] = sz; OutputDebugStr(ach);}
    #define DPWFX	DbgDumpWFX
    #define ASSERT(x)   if( !(x) )  _Assert( __FILE__, __LINE__)
#else
    #define DbgEnable(x)        FALSE
    #define DbgGetLevel()       0
    #define DbgSetLevel(x)      0
    #define DbgInitialize(x)    0
    #define DbgDumpWFX(x,y)	0

    #ifdef _MSC_VER
    #pragma warning(disable:4002)
    #endif

    #define D(x)
    // The Borland CBuilder compiler can't parse a DPF() so we need to define
    // several version of the DPF macro to determine how many parameters are
    // used in the call, so we can ignore them for a retail build.
    #define DPF(a,b)
    #define DPF3(a,b,c)
    #define DPF4(a,b,c,d)
    #define DPF5(a,b,c,d,e)
    #define DPI(sz)
    #define DPWFX(a,b)
    #define ASSERT(x)
#endif

#if defined(DEBUG) || defined(_DEBUG)
#define ASSERT_HWND( h )    ASSERT( IsWindow((h)) )
#else
#define ASSERT_HWND( h )    ASSERT( NULL != (h) )
#endif

#ifdef __cplusplus
}
#endif
#endif  // __DEBUG_INCLUDED__


