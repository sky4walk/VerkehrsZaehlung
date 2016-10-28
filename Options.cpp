// Options.cpp : implementation file
//

#include "stdafx.h"
#include "dvat.h"
#include "Options.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptions dialog
// (C) by Andre Betz 2001
// andre.betz@gmx.de


COptions::COptions(CWnd* pParent /*=NULL*/)
	: CDialog(COptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptions)
	m_Schranke_x = 0;
	m_Schranke_y = 0;
	m_Schranke_dy = 0;
	m_Schranke_dx = 0;
	m_Toleranz = 0;
	m_Debug = FALSE;
	m_Distanz = 0.0;
	m_Spreiz = FALSE;
	m_Laplace = FALSE;
	m_Sobel = FALSE;
	m_Blur = FALSE;
	m_AutoTrain = FALSE;
	//}}AFX_DATA_INIT
}

void COptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptions)
	DDX_Text(pDX, IDC_SCHRANKE_X, m_Schranke_x);
	DDX_Text(pDX, IDC_SCHRANKE_Y, m_Schranke_y);
	DDX_Text(pDX, IDC_SCHRANKE_DY, m_Schranke_dy);
	DDX_Text(pDX, IDC_SCHRANKE_DX, m_Schranke_dx);
	DDX_Text(pDX, IDC_TOLERANZ, m_Toleranz);
	DDV_MinMaxUInt(pDX, m_Toleranz, 0, 10);
	DDX_Check(pDX, IDC_DEBUG, m_Debug);
	DDX_Text(pDX, IDC_DIST, m_Distanz);
	DDX_Check(pDX, IDC_SPREIZ, m_Spreiz);
	DDX_Check(pDX, IDC_LAPLACE, m_Laplace);
	DDX_Check(pDX, IDC_SOBEL, m_Sobel);
	DDX_Check(pDX, IDC_BLUR, m_Blur);
	DDX_Check(pDX, IDC_TRAIN, m_AutoTrain);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptions, CDialog)
	//{{AFX_MSG_MAP(COptions)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptions message handlers
