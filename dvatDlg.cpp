// dvatDlg.cpp : implementation file
//
// (C) by Andre Betz 2001
// andre.betz@gmx.de
#include <math.h>
#include "stdafx.h"
#include "dvat.h"
#include "dvatDlg.h"
#include "globals.h"
#include "Matrix.h"
#include "sobel.h"
#include "laplace.h"
#include "Schwellwert.h"
#include "houghtrafo.h"
#include "bmpvideo.h"
#include "spreiz.h"
#include "Options.h"
#define TIMER_NUM 1
#define TIMER_DELAY 50

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
//	DDX_Control(pDX, IDC_COUNT, m_Count);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDvatDlg dialog

CDvatDlg::CDvatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDvatDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDvatDlg)
	m_Count = 0;
	m_Dist = 0;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CDvatDlg::~CDvatDlg()
{
	OnButton2();
}

void CDvatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDvatDlg)
	DDX_Text(pDX, IDC_COUNT, m_Count);
	DDX_Text(pDX, IDC_DIST, m_Dist);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDvatDlg, CDialog)
	//{{AFX_MSG_MAP(CDvatDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_WM_TIMER()
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDvatDlg message handlers

BOOL CDvatDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	Schranke_x1 = 96;
	Schranke_y1 = 90;
	Schranke_dx = 70;
	Schranke_dy = 7;
	DistWert	= 1000.0;
	interleave  = 0;
	debug       = 0;
	Toleranz    = 4;
	vid         = NULL;
	pV          = NULL;
	timer       = false;
	dbgfl       = NULL;
	m_Count     = 0;
	Spreiz		= true;
	Laplace		= false;
	Sobel       = false;
	Blur        = false;
	Train       = true;
	AutoTrain	= true;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDvatDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDvatDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CDvatDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Bild in den DirectX Puffer schreiben
void CDvatDlg::ZeigMal(CViewer* pV,Bitmap& bmp,int dx,int dy) 
{
	int x,y;
	int res;
	int OK = 0;
//	CViewer* pV = new CViewer();

	BYTE* p = pV->Lock();

	if(pV->m_nBPP==24)
	{
		res = pV->m_Pitch - dx * pV->m_nBPP / 8;

		for(y=0;y<dy;y++)
		{
			for(x=0;x<dx;x++)
			{
				*p++ = bmp.GetRedColor(x,y);
				*p++ = bmp.GetGreenColor(x,y);
				*p++ = bmp.GetBlueColor(x,y);
			}
			for(x=0;x<res;x++) p++;
		}
		OK = 1;
	}
	if(pV->m_nBPP==32)
	{
		res = pV->m_Pitch - dx * pV->m_nBPP / 8;

		for(y=0;y<dy;y++)
		{
			for(x=0;x<dx;x++)
			{
				*p++ = bmp.GetRedColor(x,y);
				*p++ = bmp.GetGreenColor(x,y);
				*p++ = bmp.GetBlueColor(x,y);
				*p++ = 0; //bmp.GetGreyColor(x,y);
			}
			for(x=0;x<res;x++) p++;
		}
		OK = 1;
	}
	pV->Unlock();

	if(OK)
		pV->Draw();
	else
		MessageBox("Geht in nur in 24Bit Farbtiefe");
}

// Hauptroutine
int CDvatDlg::Next() 
{
	int iInt;
	Bitmap Anzeig;

	if((iInt=vid->GetBmp(bmp1))!=-1)
	{
		if(iInt)
		{
			Anzeig = bmp1;
			// Bildvorverarbeitung
			if(Spreiz)  bmp1 = spflt.filter(bmp1);
			if(Blur)    bmp1 = gs.GetBlur(bmp1);
			if(Laplace) bmp1 = lapflt.Filter(bmp1);
			if(Sobel)   
			{
				Bitmap tmpbmp1;
				Bitmap tmpbmp2;
				sobflt.GetEdges(bmp1,tmpbmp1,tmpbmp2);
				bmp1 = tmpbmp1;
			}
			// Ausschnitt holen
			Vec2 = bmp1.GetGreyAoi(Schranke_x1,Schranke_y1,Schranke_dx,Schranke_dy);

			// Mittelwert über gemerkte Ausschnitte
			if(Train)
			{
				hist.Input(Vec2);
				Strasse2 = ht.Mittelwert(hist);
				Train = false;
			}

			// Abstand zum Mittelwertbild erzeugen
			m_Dist = (int)ht.Distanz(Strasse2,Vec2);

			// Debuginformation importierbar in Excel und darstellbar
			if(debug) fprintf(dbgfl,"%d\n",m_Dist);

			// Abstand analysieren
			if((state==0)&&(m_Dist>=DistWert))
			{
				state = 1;
				m_Count++;
			}
			if((state<Toleranz+1)&&(m_Dist<DistWert)&&(state>0))
			{
				state++;
			}
			if((state==Toleranz+1)&&(m_Dist<DistWert))
			{
				Train = AutoTrain;
				state = 0;
			}
			
			// Daten und Bild ausgeben
			UpdateData(FALSE);
			ht.GetLine(Anzeig,Vec1,Schranke_x1,Schranke_y1,Schranke_x1+Schranke_dx,Schranke_y1,256);
//			einzige Funktion, die Systemabhängig ist
			ZeigMal(pV,Anzeig,Anzeig.GetDimX(),Anzeig.GetDimY());
		}
		return 1;
	}
	return 0;
}

void CDvatDlg::OnButton2() 
{
	if(timer)        KillTimer(TIMER_NUM);
	if(debug&&dbgfl) fclose(dbgfl);
	if(vid)          delete vid;
	if(pV)           delete pV;
	vid   = NULL;
	pV	  = NULL;
	dbgfl = NULL;
	timer = false;
	hist.Clear();
}

void CDvatDlg::OnButton1() 
{
	OnButton2();
	m_Count = 0;
	state = 0;

	UpdateData(FALSE);

	CFileDialog fdlg(1,NULL,NULL,OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST,
		"EinzelBitmaps (*.bmp)|*.bmp|BitmapVideo (*.txt)|*.txt|AVI-Video (*.avi)|*.avi||",NULL);
	
	if(fdlg.DoModal()==IDOK)
	{
		pV = new CViewer();
		CString fln = fdlg.GetFileName();
		CString ext = fdlg.GetFileExt();
		int len = fln.GetLength();
		const char* temp = (LPCTSTR)fln;

		if(ext=="txt"||ext=="TXT")
			vid = new CBmpVideo(temp);
		else if(ext=="avi"||ext=="AVI")
			vid = new CAviVideo(temp);
		else
			vid = new CSingleBmpVideo(temp);

		if(vid->LoadInfos())	
		{
//		Ausgabe beim erstenmal erzeugen
			pV->Create(vid->GetWidth(),vid->GetHeight());			
		}
		else
			return;

		if(debug) dbgfl = fopen("debug.txt","w");

		SetTimer(TIMER_NUM,TIMER_DELAY,NULL);
		timer = true;
	}	
}

void CDvatDlg::OnTimer(UINT nIDEvent) 
{
	if(!Next()) OnButton2();
	CDialog::OnTimer(nIDEvent);
}

void CDvatDlg::OnButton3() 
{
	OnButton2();
	COptions optdlg;
	optdlg.m_Debug       = debug;
	optdlg.m_Distanz     = DistWert;
//	optdlg.m_Interleave  = interleave;
	optdlg.m_Schranke_x  = Schranke_x1;
	optdlg.m_Schranke_y  = Schranke_y1;
	optdlg.m_Schranke_dx = Schranke_dx;
	optdlg.m_Schranke_dy = Schranke_dy;
	optdlg.m_Toleranz    = Toleranz;
	optdlg.m_Spreiz		 = Spreiz;
	optdlg.m_Laplace	 = Laplace;
	optdlg.m_Sobel		 = Sobel;
	optdlg.m_Blur		 = Blur;
	optdlg.m_AutoTrain	 = AutoTrain;

	if(optdlg.DoModal()==IDOK)
	{
		debug		= optdlg.m_Debug;
		DistWert	= optdlg.m_Distanz;
//		interleave	= optdlg.m_Interleave;
		Schranke_x1 = optdlg.m_Schranke_x;
		Schranke_y1 = optdlg.m_Schranke_y;
		Schranke_dx = optdlg.m_Schranke_dx;
		Schranke_dy = optdlg.m_Schranke_dy;
		Toleranz    = optdlg.m_Toleranz;
		Spreiz      = optdlg.m_Spreiz;
		Laplace	    = optdlg.m_Laplace;
		Sobel       = optdlg.m_Sobel;
		Blur        = optdlg.m_Blur;
		AutoTrain   = optdlg.m_AutoTrain;
	}
}

void CDvatDlg::OnButton4() 
{
	Train = true;
}