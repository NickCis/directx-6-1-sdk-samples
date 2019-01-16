/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:		debug.h
 *  Content:	debug header
 *
 ***************************************************************************/
#ifndef _DEBUG_H
#define _DEBUG_H

#ifdef DEBUG

	#define DEBUG_MODULE_NAME   "DSPSTRM"  // key name and prefix for output
    
    void FAR CDECL dprintf(UINT uDbgLevel, LPSTR szFmt, ...);

    #define D(x)        {x;}
    // The DPFx macro turns into a dprintf call if compiling for debug
    #define DPF         dprintf
    #define DPF3        dprintf

	void AssertFail(char [], char [], int, char[]);
	#define Assert(f) ((f) ? (void)NULL : (void)AssertFail(#f, __FILE__, __LINE__,NULL))
#else
    #define D(x)
    // The Borland CBuilder compiler can't parse a DPF() so we need to define
    // several version of the DPF macro to determine how many parameters are
    // used in the call, so we can ignore them for a retail build.
    #define DPF(a,b)
    #define DPF3(a,b,c)

	#define Assert(f) (void)NULL		// Macro that does nothing
#endif



#endif




