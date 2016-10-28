#if !defined(AFX_OPTIONS_H__23CAFD32_00C9_4731_8E0E_EBF067DB1E74__INCLUDED_)
#define AFX_OPTIONS_H__23CAFD32_00C9_4731_8E0E_EBF067DB1E74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Options.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptions dialog
// (C) by Andre Betz 2001
// andre.betz@gmx.de

class COptions : public CDialog
{
// Construction
public:
	COptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptions)
	enum { IDD = IDD_OPTIONS };
	UINT	m_Schranke_x;
	UINT	m_Schranke_y;
	UINT	m_Schranke_dy;
	UINT	m_Schranke_dx;
	UINT	m_Toleranz;
	BOOL	m_Debug;
	double	m_Distanz;
	BOOL	m_Spreiz;
	BOOL	m_Laplace;
	BOOL	m_Sobel;
	BOOL	m_Blur;
	BOOL	m_AutoTrain;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptions)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONS_H__23CAFD32_00C9_4731_8E0E_EBF067DB1E74__INCLUDED_)
