#ifndef __FILEINFO3D_H__
#define __FILEINFO3D_H__

#include "FileInfo.h"

#define CONEVOL_MIN		-10000
#define CONEVOL_MAX		0
#define CONEVOL_SLIDER_FACTOR	100
#define CONEVOL_SLIDER_SHIFT	10000
#define CONEVOL_SLIDER_PAGE	500

#define X_SLIDER_FACTOR		1
#define Y_SLIDER_FACTOR		1
#define Z_SLIDER_FACTOR		1
#define MUTEMAX_SLIDER_FACTOR		1
#define MINDIST_SLIDER_FACTOR		1

#define POS_SLIDER_MIN		-50	// Centimeters
#define POS_SLIDER_MAX		50	// Centimeters
#define POS_SLIDER_SHIFT	50	// Shift so min is 0

#define MUTEMAX_SLIDER_MIN		0	// Centimeters
#define MUTEMAX_SLIDER_MAX		100	// Centimeters
#define MINDIST_SLIDER_MIN		0	// Centimeters
#define MINDIST_SLIDER_MAX		100	// Centimeters

#define FI3D_DEFAULT_INNER_ANGLE    90
#define FI3D_DEFAULT_OUTER_ANGLE    120

typedef struct tag_ht3d
{
	HWND	hDlg;
    HWND    hXSlider, hYSlider, hZSlider;
    HWND    hVxSlider, hVySlider, hVzSlider;
    HWND    hXText, hYText, hZText;
    HWND    hVxText, hVyText, hVzText;
    HWND    hOuterVolText, hOuterVolSlider;
    HWND    hInnerAngleEdit, hInnerAngleSpin;
    HWND    hOuterAngleEdit, hOuterAngleSpin;
    HWND    hMaxDistSlider, hMaxDistText, hMinDistSlider, hMinDistText, hCurDistText;
    HWND    hDisable3D,	hHeadRelative, hNormal;
} HWNDTABLE3D;



class FileInfo3D : public FileInfo
{
friend BOOL CALLBACK FileInfo3DDlgProc( HWND, UINT, WPARAM, LPARAM );

public:
    FileInfo3D( MainWnd *pmw = NULL );
    virtual ~FileInfo3D();

    virtual int NewDirectSoundBuffer( void );

    virtual HRESULT Duplicate( FileInfo * );

    virtual void UpdateUI( void );
    virtual void UpdateFileName( void );

// Useful protected member functions
protected:
    virtual BOOL OnInitDialog( HWND, WPARAM );
    virtual BOOL OnCommand( WPARAM, LPARAM );
    virtual BOOL OnHScroll( WORD, LONG, HWND );
    virtual BOOL OnContextMenu( HWND, int, int );
    virtual void OnDestroy();

    virtual BOOL CreateInterface( HWND );
    virtual void SetSliders( void );

    void HandleOuterVolSliderScroll( WORD, LONG );
    void HandleXSliderScroll( WORD, LONG );
    void HandleYSliderScroll( WORD, LONG );
    void HandleZSliderScroll( WORD, LONG );
    void HandleVxSliderScroll( WORD, LONG );
    void HandleVySliderScroll( WORD, LONG );
    void HandleVzSliderScroll( WORD, LONG );
    void HandleMaxDistSliderScroll( WORD, LONG );
    void HandleMinDistSliderScroll( WORD, LONG );

    BOOL HandleConeInnerEditNotify( WPARAM, LPARAM );
    BOOL HandleConeOuterEditNotify( WPARAM, LPARAM );

    BOOL Handle3DModeNotify( WPARAM, LPARAM );

    BOOL HandleOuterVolContext( WPARAM );
    BOOL HandlePositionContext( WPARAM );
    BOOL HandleVelocityContext( WPARAM );

    void UpdateOuterVolUI( LONG, BOOL );
    void UpdateXSliderUI( LONG, BOOL );
    void UpdateYSliderUI( LONG, BOOL );
    void UpdateZSliderUI( LONG, BOOL );
    void UpdateVxSliderUI( LONG, BOOL );
    void UpdateVySliderUI( LONG, BOOL );
    void UpdateVzSliderUI( LONG, BOOL );
    void UpdateMuteMaxSliderUI( LONG, BOOL );
    void UpdateMinDistSliderUI( LONG, BOOL );
public:
    void UpdateCurrentDistUI( void );
    void UpdatePosAndVelo( void );

protected:
    HWNDTABLE3D	    m_ht3d;
    D3DVECTOR	    m_vPos;
    D3DVECTOR	    m_vVelo;
    D3DVALUE        m_flMaxDistance;
    D3DVALUE        m_flMinDistance;
    DWORD	        m_dwInnerAngle, m_dwOuterAngle;

    LPDIRECTSOUND3DBUFFER   m_pDSB3D;	// DirectSound 3D buffer interface
};


typedef FileInfo3D *	PFILEINFO3D;

BOOL CALLBACK FileInfo3DDlgProc( HWND, UINT, WPARAM, LPARAM );

#endif


