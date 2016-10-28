// (C) 2001 by 
// Manfred Lippert mani@mani.de
// Andre Betz andre.betz@gmx.de

#if !defined(AFX_Viewer_H__87C2A3E4_90ED_4A37_A508_9CA15EF80516__INCLUDED_)
#define AFX_Viewer_H__87C2A3E4_90ED_4A37_A508_9CA15EF80516__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Viewer.h : header file
//

#include "ddraw.h"

/////////////////////////////////////////////////////////////////////////////
// CViewer frame



class CViewer : public CFrameWnd
{
	DECLARE_DYNCREATE(CViewer)
protected:

	LPDIRECTDRAW7 m_pDD;
	LPDIRECTDRAWSURFACE7    m_pDDSPrimary;   // DirectDraw primary surface
	CString m_strFile;

// Attributes
public:
	int m_nBPP;
	LPDIRECTDRAWSURFACE7    m_pDDSBack;   // DirectDraw back surface
	int m_Pitch;
	int m_x, m_y;
	int m_nImgSize;
	CWnd* m_pWnd;


// Operations
public:
	void Unlock();
	BYTE* Lock();
	void LoadBitmap(CString strFile);
	CViewer();           // protected constructor used by dynamic creation
	void Create(int x, int y);
	void Create(CString file);
	virtual ~CViewer();
	void Draw();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewer)
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewer)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Viewer_H__87C2A3E4_90ED_4A37_A508_9CA15EF80516__INCLUDED_)
