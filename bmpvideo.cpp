#include "bmpvideo.h"
#include <stdlib.h>

CVideo::CVideo()
{
}
CVideo::~CVideo()
{
}
// Verzeichnis mit dir /B > video.txt auslesen
// und in das gleiche Verzeichnis mit den Bildern
// geben aus der Datei video.txt "video.txt" löschen
CBmpVideo::CBmpVideo(const char* DatNam) : CVideo()
{
	DatHdl = fopen(DatNam,"r");
	interleave = 1;
	count = 0;
	pics = 0;
}

CBmpVideo::~CBmpVideo()
{
	fclose(DatHdl);
}

void CBmpVideo::Reset()
{
	fseek(DatHdl,0,SEEK_SET);
	count = 0;
	pics = 0;
}

int CBmpVideo::GetBmp(Bitmap& bmp)
{
	char BmpNam[200];

	if(fscanf(DatHdl,"%s",BmpNam)>0)
	{
		if(!count) 
		{
			bmp.ReadBMP(BmpNam);
			count++;
			pics++;
			count %= interleave;
			return pics;
		}
		
		count++;
		count %= interleave;

		return 0;
	}
	else
		return -1;
}

int CBmpVideo::LoadInfos()
{
	Bitmap bmp;
	char BmpNam[200];
	if(fscanf(DatHdl,"%s",BmpNam)>0)
	{
		bmp.ReadBMP(BmpNam);
		bmphdr.biWidth=bmp.GetDimX();
		bmphdr.biHeight=bmp.GetDimY();
		Reset();
		return 1;
	}

	return 0;
}
	
int CBmpVideo::GetHeight()
{
	return bmphdr.biHeight;
}

int CBmpVideo::GetWidth()
{
	return bmphdr.biWidth;
}

// lädt ein Bitmap und ermittelt aus dem der Zahl die am Ende
// des Dateinames steht die nächste Zahl, wobei die Bilder
// fortlaufend nummeriert sein muessen
CSingleBmpVideo::CSingleBmpVideo(const char* DatName)
{
	char Zahl[20];
	char Name[255];
	int len,pos1,pos2;

	Bitmap temp;
	len = LengthString(DatName);
	CopyString(DatName,Name,0,len);

	while(len>0 && (Name[len]>'9' || Name[len]<'0')) len--;
	pos2 = len;
	while(len>0 && (Name[len]<='9' && Name[len]>='0')) len--;
	pos1 = len;

	CopyString(Name,Datei,0,pos1+1);
	CopyString(Name,Zahl,pos1+1,pos2+1);

	picnr = atoi(Zahl);

	temp.ReadBMP(Name);
	bmphdr.biWidth = temp.GetDimX();
	bmphdr.biHeight = temp.GetDimY();
}

int CSingleBmpVideo::CopyString(const char* Src,char* Dst,int a,int z,int at)
{
	int pos;
	for(pos=a;pos<z;pos++,at++)
	{
		Dst[at] = Src[pos];
	}
	Dst[at]=0;
	return pos;
}

int CSingleBmpVideo::LengthString(const char* Src)
{
	int length = 0;
	while(Src[length]) length++;
	return length;
}

CSingleBmpVideo::~CSingleBmpVideo()
{
}

int CSingleBmpVideo::LoadInfos()
{
	return 1;
}

void CSingleBmpVideo::Reset()
{
	count = picnr;
}

int CSingleBmpVideo::GetHeight()
{
	return bmphdr.biHeight;
}

int CSingleBmpVideo::GetWidth()
{
	return bmphdr.biWidth;
}

int CSingleBmpVideo::GetBmp(Bitmap &bmp)
{
	char Name[255];
	sprintf(Name,"%s%d%s",Datei,picnr,".bmp");
	if(bmp.ReadBMP(Name)) return -1;
	return 	picnr++;
}
// unkomprimierte AVI Files einlesen, starres Format
// schneller hack, also keine gewähr, daß es immer funktioniert
CAviVideo::CAviVideo(const char* DatNam) : CVideo()
{
	picbuf = NULL;
	DatHdl = fopen(DatNam,"rb");
}

CAviVideo::~CAviVideo()
{
	if(DatHdl!=NULL) fclose(DatHdl);
	if(picbuf!=NULL) delete picbuf;
}

int CAviVideo::LoadInfos()
{
	int iID,len,nxtlst;
	if(DatHdl==NULL) return 0;
	fread(&iID,4,1,DatHdl);
	if(iID!=RIFF) return 0;
	fread(&DatLen,4,1,DatHdl);
	fread(&iID,4,1,DatHdl);
	if(iID!=AVI_) return 0;
	fread(&iID,4,1,DatHdl);
	if(iID!=LIST) return 0;
	fread(&len,4,1,DatHdl);
	nxtlst = len + ftell(DatHdl);
	fread(&iID,4,1,DatHdl);
	if(iID!=HDRL) return 0;
	fread(&iID,4,1,DatHdl);
	if(iID!=AVIH) return 0;
	fread(&len,4,1,DatHdl);
	fread(&avimnhdr,len,1,DatHdl);
	fread(&iID,4,1,DatHdl);
	if(iID!=LIST) return 0;
	fread(&len,4,1,DatHdl);
	fread(&iID,4,1,DatHdl);
	if(iID!=STRL) return 0;
	fread(&iID,4,1,DatHdl);
	if(iID!=STRH) return 0;
	fread(&len,4,1,DatHdl);
	fseek(DatHdl,ftell(DatHdl)+len,SEEK_SET);
	fread(&iID,4,1,DatHdl);
	if(iID!=STRF) return 0;
	fread(&len,4,1,DatHdl);
	fread(&bmphdr,len,1,DatHdl);
	fseek(DatHdl,nxtlst,SEEK_SET);
	fread(&iID,4,1,DatHdl);
	if(iID!=JUNK||iID!=JUNQ) return 0;
	fread(&len,4,1,DatHdl);
	fseek(DatHdl,ftell(DatHdl)+len,SEEK_SET);
	fread(&iID,4,1,DatHdl);
	if(iID!=LIST) return 0;
	fread(&len,4,1,DatHdl);
	fread(&iID,4,1,DatHdl);
	if(iID!=MOVI) return 0;
	fread(&iID,4,1,DatHdl);
	if(iID!=OODB) return 0;
	fread(&piclen,4,1,DatHdl);
	Start = ftell(DatHdl);

	picbuf = new unsigned char[piclen];

	return 1;
}

int CAviVideo::GetHeight()
{
	return avimnhdr.dwHeight;
}

void CAviVideo::Reset()
{
	fseek(DatHdl,Start,SEEK_SET);
}

int CAviVideo::GetWidth()
{
	return avimnhdr.dwWidth;
}

int CAviVideo::GetBmp(Bitmap& bmp)
{
	int CountX;
	int CountY;
	unsigned char* tmp = picbuf;

	bmp.NeuesBild(GetWidth(),GetHeight());
	if(fread(tmp,piclen,1,DatHdl))
	{
		for(CountY=0;CountY<GetHeight();CountY++)
		{
			for(CountX=0;CountX<GetWidth();CountX++)
			{
				bmp.SetRedColor(CountX,GetHeight()-CountY-1,(unsigned char)(*tmp++));
				bmp.SetGreenColor(CountX,GetHeight()-CountY-1,(unsigned char)(*tmp++));
				bmp.SetBlueColor(CountX,GetHeight()-CountY-1,(unsigned char)(*tmp++));
			}
		}

		fread(&CountX,4,1,DatHdl);
		fread(&CountY,4,1,DatHdl);
		
		return 1;
		
	}

	return -1;
}
