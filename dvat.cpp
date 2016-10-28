// (C) 2001 by 
// Andre Betz andre.betz@gmx.de
// dvat.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "dvat.h"
#include "dvatDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDvatApp

BEGIN_MESSAGE_MAP(CDvatApp, CWinApp)
	//{{AFX_MSG_MAP(CDvatApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDvatApp construction

CDvatApp::CDvatApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDvatApp object

CDvatApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDvatApp initialization

BOOL CDvatApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CDvatDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
