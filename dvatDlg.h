// dvatDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDvatDlg dialog
// (C) by Andre Betz 2001
// andre.betz@gmx.de
#include "viewer.h"
#include "Matrix.h"
#include "bitmap.h"
#include "globals.h"
#include "Matrix.h"
#include "laplace.h"
#include "houghtrafo.h"
#include "bmpvideo.h"
#include "spreiz.h"
#include "sobel.h"
#include "gauss2.h"
#include "ringpuffer.h"

class CDvatDlg : public CDialog
{
// Construction
public:
	CDvatDlg(CWnd* pParent = NULL);	// standard constructor
	~CDvatDlg();
// Dialog Data
	//{{AFX_DATA(CDvatDlg)
	enum { IDD = IDD_DVAT_DIALOG };
	UINT	m_Count;
	UINT	m_Dist;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDvatDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

protected:
	void ZeigMal(CViewer* pV,Bitmap& bmp,int dx,int dy); 
	Bitmap			bmp1;
	HoughTrafo		ht;
	LaplaceFilter	lapflt;
	SpreizFilter	spflt;
	SobelFilter		sobflt;
	Gauss			gs;
	CHistogram      hist;
	
	CViewer*	pV;
	CVideo*		vid;
	Bitmap Vec2;
	Bitmap Strasse2;
	Vector<unsigned char> Strasse1;
	Vector<unsigned char> Vec1;
	int state;
	int debug;
	int Schranke_x1;
	int Schranke_y1;
	int Schranke_dx;
	int Schranke_dy;
	int interleave;
	int Toleranz;
	double DistWert;
	bool timer;
	int Spreiz;
	int Laplace;
	int Sobel;
	int Blur;
	int Train;
	int AutoTrain;

	FILE *dbgfl;
	HICON m_hIcon;
	int Next();
	// Generated message map functions
	//{{AFX_MSG(CDvatDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButton4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
