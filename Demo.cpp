#include <windows.h>
#include <stdio.h>
//#include <bitmap.h>
#define  TITLE "Demo"
#define szAppName "Menu"
#define ID_STATIC_FPS 1002
#define MID_QUIT 1
#define MID_LOAD 2

LPBITMAPINFOHEADER	m_lpBMIH;
char*				m_buf;
int					wx = 550;
int					wy = 550;
//Bitmap				bitm;


int		PASCAL WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd,UINT Message,WPARAM wParam,LPARAM lParam);
int		DoWMCommand(WORD wParam, HWND hWnd);
void	Refresh(HWND hWnd);
void	Laden(HWND hWnd);
int ReadPGM(char* pcFileName);

int PASCAL WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int nCmdShow)
{
	WNDCLASS    wndClass;
	MSG         msg;
	HWND		hWnd;
	HDC			pDC;
	int			ret;

	m_lpBMIH = (LPBITMAPINFOHEADER)new char[sizeof(BITMAPINFOHEADER)];
	m_lpBMIH->biSize			= sizeof(BITMAPINFOHEADER);
	m_lpBMIH->biWidth			= 0;
	m_lpBMIH->biHeight			= 0;
	m_lpBMIH->biPlanes			= 1;
	m_lpBMIH->biBitCount		= 24;
	m_lpBMIH->biCompression		= BI_RGB;
	m_lpBMIH->biSizeImage		= 0;
	m_lpBMIH->biXPelsPerMeter	= 0;
	m_lpBMIH->biYPelsPerMeter	= 0;
	m_lpBMIH->biClrUsed			= 0;
	m_lpBMIH->biClrImportant	= 0;
	
	m_buf = NULL;

 	if(!hPrevInstance)
	{
		wndClass.style          = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc    = WndProc;
		wndClass.cbClsExtra     = 0;
		wndClass.cbWndExtra     = 0;
		wndClass.hInstance      = hInstance;
		wndClass.hIcon          = LoadIcon(hInstance,IDI_APPLICATION);
		wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
		wndClass.hbrBackground  = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
		wndClass.lpszMenuName   = szAppName;
		wndClass.lpszClassName  = szAppName;

		if (!RegisterClass(&wndClass)) return FALSE;

		hWnd = CreateWindow(szAppName,TITLE,WS_OVERLAPPEDWINDOW,0,0,wx,wy,NULL,NULL,hInstance,NULL);
	}

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	Laden(hWnd);

	while(1)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))
		{
			if( !GetMessage(&msg,NULL,0,0))
				return msg.wParam;
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}
		else
		{
			if(m_buf!=NULL)
			{
				pDC = GetDC(hWnd);
				ret = SetStretchBltMode(pDC,COLORONCOLOR);
				ret = StretchDIBits(pDC,0,0,wx,wy,0,0,m_lpBMIH->biWidth,m_lpBMIH->biHeight,
					m_buf,(LPBITMAPINFO)m_lpBMIH,DIB_RGB_COLORS,SRCCOPY);
				ReleaseDC(hWnd,pDC);
			}
		}
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT Message,WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT	ps;

	switch(Message)
	{
			case WM_COMMAND:
					return DoWMCommand(wParam,hWnd);

			case WM_PAINT:
					hdc = BeginPaint(hWnd, &ps);
					EndPaint(hWnd,&ps);
					break;

			case WM_DESTROY:
					delete m_lpBMIH;
					delete m_buf;
					PostQuitMessage(0);
					break;
			default:
					return DefWindowProc(hWnd,Message,wParam,lParam);
	}
	return 0;
}

void Refresh(HWND hWnd)
{
	RECT Fenster;

	GetClientRect(hWnd,&Fenster);
	InvalidateRect(hWnd,&Fenster,FALSE);
	UpdateWindow(hWnd);
}

int DoWMCommand(WORD wParam, HWND hWnd)
{
	switch(wParam)
	{
			case MID_QUIT:
					DestroyWindow(hWnd);
					break;
			case MID_LOAD:
					Laden(hWnd);
					break;
			default:
					return 0;
	}
	return 1;
}

void Laden(HWND hWnd)
{
	char stringhelp[128];
	char szFile[256];
	char szFileTitle[256];
	int picbit = 3;
	int ibit;
	int iCountY;
	int iCountX;

	OPENFILENAME ofn;

	szFile[0] = '\0';
	memset(&ofn,0,sizeof(OPENFILENAME));
	ofn.lStructSize		= sizeof(OPENFILENAME);
	ofn.lpstrFilter		= "Bitmap(*.PGM)\0*.pgm\0";
	ofn.nFilterIndex	= 1;
	ofn.lpstrFile		= szFile;
	ofn.nMaxFile		= sizeof(szFile);
	ofn.lpstrFileTitle	= szFileTitle;
	ofn.nMaxFileTitle	= sizeof(szFileTitle);
	ofn.lpstrInitialDir = "\0";
	ofn.Flags			=  OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	if(GetOpenFileName(&ofn)) 
	{
		strcpy(stringhelp,TITLE);
		strcat(stringhelp," -  ");
		strcat(stringhelp,(const char*)ofn.lpstrFileTitle);
		SetWindowText(hWnd,stringhelp);

//		bitm.ReadBMP(ofn.lpstrFile);
//		bitm.ReadPGM(ofn.lpstrFile);
//		m_lpBMIH->biWidth			= bitm.GetDimX();
//		m_lpBMIH->biHeight			= bitm.GetDimY();
//		m_lpBMIH->biSizeImage		= m_lpBMIH->biWidth*m_lpBMIH->biHeight;

		ReadPGM(ofn.lpstrFile);
	}
}

int ReadPGM(char* pcFileName)
{
	char s[10];
	char t[10];
	char c;
	int x,y,iCountX,iCountY;
	int m_iBpp;

	FILE* fp;
    fp = fopen(pcFileName,"rb");

	fscanf(fp,"%s",s);
	if (s[0]!='P') return 0;
	c=fgetc(fp);
	c=fgetc(fp);
	while(c=='#')  
	{ 
		if(c=='#') 
			while(c!=10)
		{
			c=fgetc(fp);
		}
		c=fgetc(fp); 
	}
 
	fscanf(fp,"%s",s);
	sprintf(t,"%c%s",c,s);
	x = atoi(t);
	fscanf(fp,"%s",s);
	y = atoi(s);
	fscanf(fp,"%s",s);
	m_iBpp = atoi(s);

	m_lpBMIH->biWidth			= x;
	m_lpBMIH->biHeight			= y;
	m_lpBMIH->biSizeImage		= m_lpBMIH->biWidth*m_lpBMIH->biHeight;

	if(m_buf!=NULL) delete m_buf;
		m_buf = new char[m_lpBMIH->biSizeImage*3];

	for(iCountY=0;iCountY<m_lpBMIH->biHeight;iCountY++)
	{
		for(iCountX=0;iCountX<m_lpBMIH->biWidth;iCountX++)
		{
			char pix = fgetc(fp);
			m_buf[3*(iCountY * m_lpBMIH->biWidth + iCountX)+0] = pix;
			m_buf[3*(iCountY * m_lpBMIH->biWidth + iCountX)+1] = pix;
			m_buf[3*(iCountY * m_lpBMIH->biWidth + iCountX)+2] = pix;
		}
	}

	fclose(fp);
	return 1;
}