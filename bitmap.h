// (C) 2001 by 
// Andre Betz andre.betz@gmx.de

// Bitmap-Klasse
#ifndef BITMAP
#define BITMAP

#include <stdio.h>
#include "Matrix.h"

typedef struct mytagBITMAPFILEHEADER 
{
        unsigned short	bfType;
        unsigned int	bfSize;
        unsigned short	bfReserved1;
        unsigned short	bfReserved2;
        unsigned int	bfOffBits;
} myBITMAPFILEHEADER;

typedef struct mytagBITMAPINFOHEADER
{
        unsigned int		biSize;
        int					biWidth;
        int					biHeight;
        unsigned short      biPlanes;
        unsigned short      biBitCount;
        unsigned int        biCompression;
        unsigned int        biSizeImage;
        unsigned int        biXPelsPerMeter;
        int					biYPelsPerMeter;
        unsigned int        biClrUsed;
        unsigned int        biClrImportant;
} myBITMAPINFOHEADER;

typedef struct mytagRECT
{
    int    left;
    int    top;
    int    right;
    int    bottom;
} myRECT;

class Bitmap : Matrix<unsigned char>
{
public:
  Bitmap();
  Bitmap(const Bitmap& bmp);
  Bitmap(const char* Filename);
  Bitmap(int iWidth, int iHeight);
  ~Bitmap();
  void NeuesBild(int iWidth,int iHeight);
  int ReadBMP(const char* pcFileName);
  int WriteBPM(const char* pcFileName);
  int ReadPGM(const char* pcFileName);
  int WritePGM(const char* pcFileName);
  int GetDimX() const;
  int GetDimY() const;
  unsigned char GetGreyColor(int iXPos,int iYPos);
  unsigned char GetRedColor(int iXPos,int iYPos);
  unsigned char GetGreenColor(int iXPos,int iYPos);
  unsigned char GetBlueColor(int iXPos,int iYPos);
  void SetGreyColor(int iXPos,int iYPos,unsigned char ucCol);
  void SetRedColor(int iXPos,int iYPos,unsigned char ucCol);
  void SetGreenColor(int iXPos,int iYPos,unsigned char ucCol);
  void SetBlueColor(int iXPos,int iYPos,unsigned char ucCol);
  Bitmap& operator=(const Bitmap& bmp);
  Bitmap GetGreyAoi(int iOffsetX,int iOffsetY,int iSizeX,int iSizeY);
  void SetGreyAoi(Bitmap &bmp,int iOffsetX,int iOffsetY,int iSizeX,int iSizeY);
  Bitmap Scale(int iXSize,int iYSize);
  int IsNull();
protected:
  void copy(const Bitmap &bmp);
  void set_pixel(unsigned char* buffer,int byte,int* colortable);
  int ReadShort(FILE* fp,int* ret);
  int ReadLong(FILE* fp,int* ret);
  unsigned char* m_Data;          
  unsigned char* m_pucData;
  int            m_iWidth;
  int            m_iHeight;
  int			 m_iBpp;
  myBITMAPFILEHEADER bmpflhdr;
  myBITMAPINFOHEADER bmphdr;
};

#endif