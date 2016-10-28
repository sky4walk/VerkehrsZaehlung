// (C) 2001 by 
// Andre Betz andre.betz@gmx.de

// Viewer.cpp : implementation file
// zeigt Bilder über DirectX am Bildschirm

#include "stdafx.h"
#include "Viewer.h"
#include "ddutil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewer

IMPLEMENT_DYNCREATE(CViewer, CFrameWnd)


CViewer::CViewer()
{
	m_pDDSBack = NULL;
	m_x = m_y = 0;
	m_strFile.Empty();

	VERIFY(DirectDrawCreateEx(NULL, (VOID**)&m_pDD, IID_IDirectDraw7, NULL) == DD_OK);
}

CViewer::~CViewer()
{
	m_pDDSBack->Release();
	m_pDDSPrimary->Release();
	m_pDD->Release();
}


void CViewer::Create(CString strFile)
{
	m_strFile = strFile;

	CFrameWnd::Create(NULL, "Viewer");

	ShowWindow(SW_SHOW);	
}

void CViewer::Create(int x, int y)
{
	m_x = x;
	m_y = y;

	CFrameWnd::Create(NULL,"Video");

	ShowWindow(SW_SHOW);	
}

BEGIN_MESSAGE_MAP(CViewer, CFrameWnd)
	//{{AFX_MSG_MAP(CViewer)
	ON_WM_CREATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewer message handlers


int CViewer::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	VERIFY( m_pDD->SetCooperativeLevel( GetSafeHwnd(), DDSCL_NORMAL)== DD_OK );

    DDSURFACEDESC2      ddsd;

    // Create the primary surface
    ZeroMemory(&ddsd,sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
    VERIFY(m_pDD->CreateSurface(&ddsd, &m_pDDSPrimary, NULL) == DD_OK);

    LPDIRECTDRAWCLIPPER pClipper;
    // Create a clipper object since this is for a Windowed render
    VERIFY(m_pDD->CreateClipper(0, &pClipper, NULL) == DD_OK);

    // Associate the clipper with the window
    pClipper->SetHWnd(0, GetSafeHwnd() );
    m_pDDSPrimary->SetClipper(pClipper);
    pClipper->Release();
    pClipper = NULL;

//	CRect rect;
//	GetClientRect(&rect);

	if(m_strFile.IsEmpty())
	{

		// Get the backbuffer. For fullscreen mode, the backbuffer was created
		// along with the primary, but windowed mode still needs to create one.
		ddsd.dwFlags        = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
		ddsd.dwWidth        = m_x;
		ddsd.dwHeight       = m_y;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
		VERIFY(m_pDD->CreateSurface(&ddsd, &m_pDDSBack, NULL) == DD_OK);

		DDBLTFX fx;
		fx.dwSize = sizeof(fx);
		fx.dwFillColor = 255;

		VERIFY(m_pDDSBack->Blt(NULL, NULL, NULL, DDBLT_COLORFILL, &fx) == DD_OK);                     

		VERIFY( m_pDDSBack->Lock(NULL, &ddsd,  
			DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT | DDLOCK_NOSYSLOCK, NULL ) == DD_OK );                   

		BYTE* p = (BYTE*)ddsd.lpSurface;
		DWORD bpp = ddsd.ddpfPixelFormat.dwRGBBitCount >> 3;
		DWORD pitch = ddsd.lPitch;

		m_pDDSBack->Unlock(NULL);

		CRect cr(0, 0, m_x+4, m_y+4);
		//GetClientRect(&cr);
		ClientToScreen(&cr);
//		AdjustWindowRect(&cr, WS_CAPTION|WS_BORDER|WS_THICKFRAME|WS_SYSMENU, false);
		AdjustWindowRect(&cr, WS_CAPTION|WS_BORDER|WS_THICKFRAME|WS_SYSMENU, 0);
		SetWindowPos(&wndNoTopMost, cr.left, cr.top, cr.Width(), cr.Height(),
			SWP_NOCOPYBITS|SWP_NOZORDER);
	}
	else
	{
		LoadBitmap(m_strFile);
	}

	ShowWindow(SW_SHOW);

	return 0;
}

void CViewer::Draw()
{
	Unlock();

	CRect rect(0, 0, m_x, m_y);
	GetClientRect(&rect);
	ClientToScreen(&rect);

    //VERIFY(
		m_pDDSPrimary->Blt(&rect, m_pDDSBack,
                              NULL, DDBLT_ASYNC,
                              NULL);// == DD_OK);
}



void CViewer::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	Draw();
	
	// Do not call CFrameWnd::OnPaint() for painting messages
}


void CViewer::LoadBitmap(CString strFile)
{
	if(m_pDDSBack)
	{
		m_pDDSBack->Release();
	}

	m_pDDSBack = DDLoadBitmap(m_pDD, strFile, 0, 0);

	DDSURFACEDESC2 sd;
	sd.dwSize = sizeof(sd);
	VERIFY(m_pDDSBack->GetSurfaceDesc(&sd) == DD_OK);
	m_x = sd.dwWidth;
	m_y = sd.dwHeight;
	m_Pitch = sd.lPitch;
	m_nBPP = sd.ddpfPixelFormat.dwRGBBitCount;
	m_nImgSize = sd.dwHeight * sd.lPitch;

	CRect cr(0, 0, m_x+4, m_y+4);
	//GetClientRect(&cr);
	ClientToScreen(&cr);
//	AdjustWindowRect(&cr, WS_CAPTION|WS_BORDER|WS_THICKFRAME|WS_SYSMENU, false);
	AdjustWindowRect(&cr, WS_CAPTION|WS_BORDER|WS_THICKFRAME|WS_SYSMENU, 0);
	SetWindowPos(&wndNoTopMost, cr.left, cr.top, cr.Width(), cr.Height(),
		SWP_NOCOPYBITS|SWP_NOZORDER);

	Draw();
}


BYTE* CViewer::Lock()
{
	DDSURFACEDESC2 sd;
	sd.dwSize = sizeof(sd);
	if(m_pDDSBack->Lock(NULL, &sd,
		DDLOCK_WAIT|DDLOCK_SURFACEMEMORYPTR|DDLOCK_NOSYSLOCK, NULL)
		!= DD_OK)
	{
//		MessageBeep(0xffffffff);
	}
	m_nBPP = sd.ddpfPixelFormat.dwRGBBitCount;
    m_Pitch = sd.lPitch;
	return (BYTE*)sd.lpSurface;
}


void CViewer::Unlock()
{
	if(m_pDDSBack->Unlock(NULL) != DD_OK)
	{
//		MessageBeep(0xffffffff);
	}
}

