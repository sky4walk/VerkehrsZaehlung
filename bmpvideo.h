#include "bitmap.h"

#ifndef BMPVIDEO
#define BMPVIDEO

#include <stdio.h>

#define mmioFOURCC(ch0,ch1,ch2,ch3) ((unsigned int)(unsigned char)(ch0)|((unsigned int)(unsigned char)(ch1)<<8)|((unsigned int)(unsigned char)(ch2)<<16)|((unsigned int)(unsigned char)(ch3)<<24 ))
#define RIFF mmioFOURCC('R','I','F','F')
#define AVI_ mmioFOURCC('A','V','I',' ')
#define LIST mmioFOURCC('L','I','S','T')
#define HDRL mmioFOURCC('h','d','r','l')
#define STRL mmioFOURCC('s','t','r','l')
#define STRH mmioFOURCC('s','t','r','h')
#define STRF mmioFOURCC('s','t','r','f')
#define MOVI mmioFOURCC('m','o','v','i')
#define AVIH mmioFOURCC('a','v','i','h')
#define OODB mmioFOURCC('0','0','d','b')
#define O1WB mmioFOURCC('0','0','w','b')
#define OODC mmioFOURCC('0','0','d','c')
#define AUDS mmioFOURCC('a','u','d','s')
#define VIDS mmioFOURCC('v','i','d','s')
#define DIB_ mmioFOURCC('D','I','B',' ')
#define IDX1 mmioFOURCC('i','d','x','1')
#define JUNK mmioFOURCC('J','U','N','K')
#define JUNQ mmioFOURCC('J','U','N','Q')
#define MRLE mmioFOURCC('M','R','L','E')

typedef struct 
{
    unsigned int 		fccType;
    unsigned int 		fccHandler;
    unsigned int 		dwFlags;	/* Contains AVITF_* flags */
	unsigned short		wPriority;
    unsigned short 		wLanguage;
    unsigned int 		dwInitialFrames;
    unsigned int 		dwScale;	
    unsigned int		dwRate;	/* dwRate / dwScale == samples/second */
    unsigned int 		dwStart;
    unsigned int		dwLength; /* In units above... */
    unsigned int		dwSuggestedBufferSize;
    unsigned int		dwQuality;
    unsigned int		dwSampleSize;
    myRECT				rcFrame;
} AVIStreamHeader;

typedef struct
{
    unsigned int		dwMicroSecPerFrame;	// frame display rate (or 0L)
    unsigned int		dwMaxBytesPerSec;	// max. transfer rate
    unsigned int		dwPaddingGranularity;	// pad to multiples of this
    unsigned int		dwFlags;		// the ever-present flags
    unsigned int		dwTotalFrames;		// # frames in file
    unsigned int		dwInitialFrames;
    unsigned int		dwStreams;
    unsigned int		dwSuggestedBufferSize;
    unsigned int		dwWidth;
    unsigned int		dwHeight;
    unsigned int		dwReserved[4];
} MainAVIHeader;

class CVideo
{
public:
	CVideo();
	virtual ~CVideo();
	virtual int GetBmp(Bitmap &bmp) = 0;
	virtual int LoadInfos() = 0;
	virtual int GetHeight() = 0;
	virtual int GetWidth() = 0;
	virtual void Reset() = 0;
protected:
	FILE* DatHdl;
	myBITMAPINFOHEADER	bmphdr;
};

class CBmpVideo : public CVideo
{
public:
	CBmpVideo(const char* DatName);
	~CBmpVideo();
	int GetBmp(Bitmap &bmp);
	void Reset();
	int LoadInfos();
	int GetHeight();
	int GetWidth();
protected:
	FILE* DatHdl;
	int interleave;
	int count;
	int pics;
};

class CSingleBmpVideo : public CVideo
{
public:
	CSingleBmpVideo(const char* DatName);
	~CSingleBmpVideo();
	void Reset();
	int GetBmp(Bitmap &bmp);
	int LoadInfos();
	int GetHeight();
	int GetWidth();
protected:
	int CopyString(const char* Src,char* Dst,int a,int z,int at=0);
	int LengthString(const char* Src);
	FILE* DatHdl;
	int picnr;
	int count;
	myBITMAPINFOHEADER	bmphdr;
	char Datei[255];
};

class CAviVideo : public CVideo
{
public:
	CAviVideo(const char* DatName);
	~CAviVideo();
	int GetBmp(Bitmap &bmp);
	int LoadInfos();
	int GetHeight();
	int GetWidth();
	void Reset();
protected:
	FILE* DatHdl;
	MainAVIHeader		avimnhdr;
	AVIStreamHeader		avistrhdr;
	myBITMAPINFOHEADER	bmphdr;
	int Start;
	int DatLen;
	int piclen;
	unsigned char* picbuf;
};

#endif BMPVIDEO