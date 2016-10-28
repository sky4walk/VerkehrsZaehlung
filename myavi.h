#ifndef MYAVI
#define MYAVI

#include <stdio.h>
#include <vector>

#define BI_RGB                  0L
#define BI_RLE8                 1L
#define BI_RLE4                 2L
#define AVIF_HASINDEX			0x00000010	// Index at end of file
#define AVIF_MUSTUSEINDEX		0x00000020
#define AVIF_ISINTERLEAVED		0x00000100
#define AVIF_TRUSTCKTYPE		0x00000800	// Use CKType to find key frames
#define AVIF_WASCAPTUREFILE		0x00010000
#define AVIF_COPYRIGHTED		0x00020000
#define AVIIF_LIST              0x00000001L // chunk is a 'LIST'M
#define AVIIF_KEYFRAME          0x00000010L // this frame is a key frame.M
#define AVIIF_NOTIME            0x00000100L // this frame doesn't take any timeM
#define AVIIF_COMPUSE           0x0FFF0000L // these bits are for compressor useM
#define WAVE_FORMAT_PCM         1
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
#define MRLE mmioFOURCC('M','R','L','E')

typedef struct mytagRGBQUAD 
{
        unsigned char    rgbBlue;
        unsigned char    rgbGreen;
        unsigned char    rgbRed;
        unsigned char    rgbReserved;
} myRGBQUAD;

typedef struct mytagBITMAPINFOHEADER
{
        unsigned int		biSize;
        int			biWidth;
        int			biHeight;
        unsigned short      biPlanes;
        unsigned short      biBitCount;
        unsigned int        biCompression;
        unsigned int        biSizeImage;
        unsigned int        biXPelsPerMeter;
        int		    biYPelsPerMeter;
        unsigned int        biClrUsed;
        unsigned int        biClrImportant;
} myBITMAPINFOHEADER;

typedef struct tWAVEFORMATEX
{
    unsigned short        wFormatTag;         /* format type */
    unsigned short        nChannels;          /* number of channels (i.e. mono, stereo...) */
    unsigned int	      nSamplesPerSec;     /* sample rate */
    unsigned int		  nAvgBytesPerSec;    /* for buffer estimation */
    unsigned short        nBlockAlign;        /* block size of data */
    unsigned short        wBitsPerSample;     /* number of bits per sample of mono data */
    unsigned short        cbSize;             /* the count in bytes of the size of */
				    /* extra information (after cbSize) */
} WAVEFORMATEX;

typedef struct mytagRECT
{
    int    left;
    int    top;
    int    right;
    int    bottom;
} myRECT;

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


typedef struct
{
    unsigned int		ckid;
    unsigned int		dwFlags;
    unsigned int		dwChunkOffset;		// Position of chunk
    unsigned int		dwChunkLength;		// Length of chunk
} AVIINDEXENTRY;

class CAviException 
{
public:
	CAviException (void ) : m_pcErrString ("UNKNOWN")  {}
	CAviException (const char * pcReason) : m_pcErrString (pcReason){}
	const char * GetReason (void ) const { return m_pcErrString ;}
private:
  const char *	m_pcErrString ;
};


class IRiffObject
{
protected:
  int				m_iID;
public:
  virtual ~IRiffObject (void ) {};
  virtual bool				Write (FILE * pxFile )=0;
  virtual bool				Read (FILE * pxFile ) =0;
  virtual unsigned int		GetLength (void ) const = 0;
};

const unsigned int MAIN_RIFF_OBJECT_HEADER_SIZE = 12 ;

class CMainRiffObject : public IRiffObject 
{
protected :
  unsigned int				m_uiFileLength;
  std::vector<IRiffObject*>	m_xChildren;
public:
  CMainRiffObject (void ) ;
  ~CMainRiffObject (void );
  void  AddObject (IRiffObject * pxObject);
  virtual bool   Write (FILE * pxFile );
  virtual bool   Read (FILE * pxFile );
  virtual unsigned int		GetLength (void ) const;
};

const unsigned int RIFF_CHUNK_HEADER_LENGTH = 8;

class CRiffChunk : public IRiffObject 
{
protected:
  void		*m_pData;  
  unsigned int	m_uiDataLength ; 
public:
  CRiffChunk (void );
  CRiffChunk (int iID ,unsigned int uiDataLength,void * pData);
  virtual ~CRiffChunk (void );
  virtual bool				Write (FILE * pxFile );
  virtual bool				Read (FILE * pxFile );
  virtual unsigned int		GetLength (void ) const;
};

const unsigned int RIFF_LIST_HEADER_LENGTH = 12;

class CRiffList : public CRiffChunk 
{
protected:
  std::vector<IRiffObject*>		m_xChildren;
public:
  CRiffList (void );
  CRiffList (int iID);
  virtual ~CRiffList (void );
  virtual bool				Write (FILE * pxFile );
  virtual bool				Read (FILE * pxFile );
  virtual unsigned int		GetLength (void ) const;
  unsigned int				GetOffset (IRiffObject * child);
  void						AddObject (IRiffObject * pxObject);
};

class CAviReader 
{
private:
  FILE	*				m_pxFile;
  unsigned int			m_uiFileLength;
  CMainRiffObject*		m_pxMainObject;
  CRiffList*			m_pxMoviList;
  CRiffChunk*			m_pxIndexChunk;
  CRiffList*			m_pxVideoStreamList;
  AVIStreamHeader*		m_pxVideoStreamHeader;
  myBITMAPINFOHEADER*	m_pxVideoStreamFormat;
  CRiffList*			m_pxAudioStreamList;
  AVIStreamHeader*		m_pxAudioStreamHeader;
  WAVEFORMATEX*			m_pxAudioStreamFormat;
  CRiffList*			m_pxHeaderList;
  MainAVIHeader*		m_pxMainHeader;
public:
  CAviReader (void ) ;
  ~CAviReader (void );
  bool		Read (const char * pcName );
  bool      OpenFile(const char *pcName);
  void		CloseFile (void);
  int		GetWidth (void ) const ;
  int		GetHeight (void ) const ;
  int		GetNumFrames (void ) const ;
  int		GetNumComponents (void ) const;
  bool		HasAudio (void ) ;
  bool		GetAll (void * memory ); 
  bool		GetFrame (int iNumber ,void * memory);
  bool		CollectFileInformation (void );
  bool		ReadFrame (int iNumber,void * memory );
  bool		ReadAll (void * memory );
private:
  int       m_iWidth;
  int       m_iHeight;
  int       m_iNumFrames;
  void		FindHeaderList (void ) ;
  void		FindMainHeader (void ) ;
  void		FindMoviList (void);
  void		FindIndexChunk (void);
  void		FindStreamLists (void);
};

class CAviWriter
{
private:
	FILE*				m_pxFile;
	CMainRiffObject*	m_pxMainObject ;
	int					m_iWidth;
	int					m_iHeight;
	int					m_iNumComponents;
	int					m_iNumTotalFrames;
public:
	CAviWriter (void );
	~CAviWriter (void );
	bool					StartWriting (const char * pcFileName);
	void					EndWriting (void );
	void					Write (int iNumFrames ,int iFramesPerSecond,
								   int iVideoWidth ,int iVideoHeight,
                                   int iNumComponents,unsigned char * pucVideoData,
								   bool bCompressRLE = false,
								   unsigned char * pucAudioData = 0);
};

#endif //MYAVI