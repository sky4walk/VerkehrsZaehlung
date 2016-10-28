#include "myavi.h"

CMainRiffObject::CMainRiffObject() 
{
	m_uiFileLength = 0;
}

CMainRiffObject::~CMainRiffObject()
{
	std::vector<IRiffObject*>::iterator it = m_xChildren.begin ();

	for (;it != m_xChildren.end ();++it)
	{
		delete *it;
	}
}

void CMainRiffObject::AddObject (IRiffObject * pxObject)
{
	m_xChildren.push_back (pxObject);
}

bool CMainRiffObject::Read (FILE *pxFile)
{
	int id;
	unsigned int uiFileLen;

	fread(&id,1,4,pxFile);
	if (id != RIFF)	return false;
	fread (&uiFileLen,1,4,pxFile);
	fread (&id,1,4,pxFile);
	if (id != AVI_)	return false;

	while (ftell (pxFile) < uiFileLen )
	{
		int iID;
		fread (&iID,1,4,pxFile);
		fseek(pxFile,ftell(pxFile)-4,SEEK_SET);

		if(iID == LIST)
		{
			CRiffList *pxList = new CRiffList;

			if (!pxList->Read (pxFile))
			{
				return false;
			}
			AddObject (pxList);
		}
		else if(iID == HDRL)
		{
			fread(&iID,1,4,pxFile);
		}
		else if(iID == AVIH)
		{
			fread(&iID,1,4,pxFile);
		}
		else if(iID == STRL)
		{
			fread(&iID,1,4,pxFile);
		}
		else if(iID == STRH)
		{
			fread(&iID,1,4,pxFile);
		}
		else if(iID == STRF)
		{
			fread(&iID,1,4,pxFile);
		}
		else if(iID == MOVI)
		{
			fread(&iID,1,4,pxFile);
		}
		else if(iID == OODB)
		{
			fread(&iID,1,4,pxFile);
		}
		else if(iID == O1WB)
		{
			fread(&iID,1,4,pxFile);
		}
		else
		{
			CRiffChunk * pxChunk = new CRiffChunk ;

			if(!pxChunk->Read(pxFile))
			{
				return false;
			}
			AddObject(pxChunk);
		}
	}
	return true;
}

bool CMainRiffObject::Write (FILE * pxFile )
{
	int iRiffID = mmioFOURCC('R','I','F','F');
	int iAviID =  mmioFOURCC('A','V','I',' ');
	m_uiFileLength = GetLength ();
	unsigned int uiLen = m_uiFileLength - 8 ;

	fwrite (&iRiffID,1,4,pxFile);
	fwrite (&uiLen,1,4,pxFile);
	fwrite (&iAviID,1,4,pxFile);

	std::vector<IRiffObject*>::iterator it = m_xChildren.begin ();

	for(;it!= m_xChildren.end ();++it)
	{
		IRiffObject *obj = *it;

		if (! obj->Write (pxFile))
		{
			return false;
		}
	}
	return true;
}

unsigned int CMainRiffObject::GetLength (void ) const 
{
	unsigned int uiRes = 0;
	std::vector<IRiffObject*>::const_iterator it = m_xChildren.begin ();

	for (;it != m_xChildren.end ();++it)
	{
		const IRiffObject * obj = *it;

		uiRes+= obj->GetLength ();
	}

	uiRes+= MAIN_RIFF_OBJECT_HEADER_SIZE ;

	return uiRes;
}

CRiffChunk::CRiffChunk (void )
{
	m_iID = 0;
	m_pData = 0;
	m_uiDataLength = 0;
}

CRiffChunk::CRiffChunk (int iID ,unsigned int uiDataLength,void * pData)
{
	m_iID = iID ;
	m_pData = (void *)new unsigned char [uiDataLength ];
	memcpy (m_pData,pData,uiDataLength);
	m_uiDataLength = uiDataLength ;
}


CRiffChunk::~CRiffChunk (void )
{
	if (m_pData )
	{
		delete [] m_pData ;
	}
}

bool	CRiffChunk::Write (FILE * pxFile )
{
	unsigned int uiLength = GetLength ();

	fwrite (&m_iID,1,4,pxFile);
	fwrite (&m_uiDataLength,1,4,pxFile);
		
	if (!fwrite (m_pData,1,m_uiDataLength,pxFile))
	{
		return false;
	}

	return true;
}

bool CRiffChunk::Read(FILE* pxFile )
{
	unsigned int uiLength =0;
	int hdrl1 = mmioFOURCC('h','d','r','l');
	int mov   = mmioFOURCC('m','o','v','i');

	fread(&m_iID,1,4,pxFile);
	fread(&uiLength,1,4,pxFile);

	m_uiDataLength = uiLength - RIFF_CHUNK_HEADER_LENGTH;
	m_pData = new unsigned char [m_uiDataLength];
	
	if(!fread(m_pData,1,m_uiDataLength,pxFile))
	{
		return false;
	}
	return true;
}

unsigned int CRiffChunk::GetLength (void ) const
{
	return m_uiDataLength + RIFF_CHUNK_HEADER_LENGTH;
}

CRiffList::CRiffList (void ) : CRiffChunk ()
{
}

CRiffList::CRiffList (int iID) : CRiffChunk ()
{
	m_iID = iID;
}

CRiffList::~CRiffList (void )
{
	std::vector<IRiffObject*>::iterator it = m_xChildren.begin ();

	for (;it != m_xChildren.end ();++it)
	{
		delete *it;
	}
}

bool CRiffList::Write (FILE * pxFile )
{
	unsigned int uiLength = GetLength () - RIFF_LIST_HEADER_LENGTH + 4 ; 
	int iListID = mmioFOURCC('L','I','S','T');

	fwrite (&iListID,1,4,pxFile);
	fwrite (&uiLength,1,4,pxFile);
	fwrite (&m_iID,1,4,pxFile);

	std::vector<IRiffObject*>::iterator it=m_xChildren.begin ();

	for (;it != m_xChildren.end ();++it)
	{
		IRiffObject * pxObj= *it;

		if (!pxObj->Write (pxFile))
		{
			return false;
		}
	}
	
	return true;
}

bool CRiffList::Read (FILE * pxFile )
{
	unsigned int uiLength;
	unsigned int iListID;

	fread(&iListID,1,4,pxFile);
	fread(&uiLength,1,4,pxFile);
	fread(&m_iID,1,4,pxFile);

	m_uiDataLength = uiLength + RIFF_CHUNK_HEADER_LENGTH - 4;
/*
	m_pData = new unsigned char [m_uiDataLength];
	
	if(!fread(m_pData,1,m_uiDataLength,pxFile))
	{
		return false;
	}
*/
	return true;
}

void CRiffList::AddObject(IRiffObject * pxObject)
{
	m_xChildren.push_back (pxObject);
}

unsigned int CRiffList::GetLength (void ) const 
{
	unsigned int uiRes =0;
	std::vector<IRiffObject*>::const_iterator it = m_xChildren.begin ();

	for (;it!= m_xChildren.end ();++it)
	{
		const IRiffObject * obj = *it;
		uiRes += obj->GetLength ();
	}

	return uiRes + RIFF_LIST_HEADER_LENGTH;
}

unsigned int  CRiffList::GetOffset (IRiffObject * child)
{
	unsigned int uiRes =4;

	std::vector<IRiffObject*>::const_iterator it = m_xChildren.begin ();

	for (;it != m_xChildren.end ();++it)
	{
		const IRiffObject * obj = *it ;
		if (obj == child )
		{
			return uiRes ;
		}
		uiRes += obj->GetLength ();
	}
	throw CAviException ("CRiffList::GetOffset : child not present");
	return 0;
}

CAviReader::CAviReader()
{
	m_pxFile       = 0;
	m_iWidth       = -1 ;
	m_iHeight      = -1 ;
	m_iNumFrames   = 0;
	m_uiFileLength = 0;
}

CAviReader::~CAviReader()
{
	if (m_pxFile )
	{
		fclose (m_pxFile );
	}
}

int	CAviReader::GetWidth (void ) const 
{
	if (!m_pxFile )
	{
		throw CAviException ();
	}
	return m_iWidth ;
}
int	CAviReader::GetHeight (void ) const 
{
	if (!m_pxFile )
	{
		throw CAviException();
	}
	return m_iHeight;
}
int CAviReader::GetNumFrames (void ) const 
{
	if (!m_pxFile )
	{
		throw CAviException ();
	}
	return m_iNumFrames ;
}

bool CAviReader::OpenFile (const char * pcName )
{
	if (!pcName )
	{
		throw CAviException ("NULL POINTER");
	}
	
	m_pxFile = fopen (pcName,"rb");

	if (!m_pxFile ) 
	{
		return false;
	}

	fseek (m_pxFile,0,SEEK_END);
	m_uiFileLength = ftell (m_pxFile );
	fseek (m_pxFile,0,SEEK_SET);

	if (! m_uiFileLength )
	{
		fclose (m_pxFile );
		m_pxFile = 0;
		return false;
	}

	if (!CollectFileInformation ())
	{
		return false;
	}

	m_pxMainObject = new CMainRiffObject;
	m_pxMainObject->Read(m_pxFile);

	return true;
}

void CAviReader::CloseFile (void )
{
	if (m_pxFile )
	{
		fclose (m_pxFile );
		m_pxFile = 0;
	}
}

bool CAviReader::ReadAll (void * memory )
{
	return false;	
}

bool CAviReader::ReadFrame (int iNumber,void * memory )
{
 	return false;
}

bool CAviReader::CollectFileInformation (void )
{
	return true;
}

int CompressRLE8 (unsigned char * pucOut,unsigned char * pucIn ,int iSize)
{
	int iVal = 0;
	int iCount=0,iCur;
	bool start=true;
	unsigned char * pucCurOut = pucOut;
	unsigned char * pucCurIn = pucIn;


	while (pucCurIn < pucIn + iSize)
	{
		iCur = *pucCurIn;
	
		if (iCur!= iVal || iCount >= 254 )
		{
			// flush 
			*pucCurOut++ = iCount;
			*pucCurOut++ = iVal ;
			iVal = *pucCurIn++;
			iCount = 1;
			start = false;
		}
		else
		{
			iCount++;
			pucCurIn++;
		}
	}

	*pucCurOut++=0;
	*pucCurOut++=1;

	return (pucCurOut - pucOut);
}

CAviWriter::CAviWriter (void )
{
	m_pxFile = 0;
	m_pxMainObject = 0;
}
CAviWriter::~CAviWriter (void )
{
	if (m_pxFile )
	{
		fclose (m_pxFile);
	}
	if (m_pxMainObject )
	{
		delete m_pxMainObject ;
	}
}

bool CAviWriter::StartWriting (const char * pcFileName)
{	
	m_pxFile = fopen (pcFileName,"wb");

	if (!m_pxFile )
	{
		return false;
	}

	return true;
}

void CAviWriter::EndWriting (void )
{
	
	
	int size = m_pxMainObject->GetLength ();
	int real = ftell (m_pxFile );
	if (real != size)
	{
		throw CAviException ("BAD SIZE");
	}

	fclose (m_pxFile);
	m_pxFile = 0;
}

void CAviWriter::Write (int iNumFrames ,int iFramesPerSecond,int iVideoWidth ,int iVideoHeight ,
                        int iNumComponents,unsigned char * pucVideoData,bool bCompressRLE,
								unsigned char * pucAudioData )
{
	unsigned int uiRate ,uiScale,uiLength,uiBufferSize;
	uiScale			= 1;
	uiRate			= iFramesPerSecond * uiScale;
	uiLength		= iNumFrames / iFramesPerSecond;
	uiBufferSize	= iVideoWidth * iVideoHeight * iFramesPerSecond  ;
	unsigned int uiVideoDataLength; 

	if(1)
	{
		bCompressRLE = false;
	}

	m_iWidth			= iVideoWidth;
	m_iHeight			= iVideoHeight;
	m_iNumComponents	= iNumComponents;
	m_iNumTotalFrames	= iNumFrames;
	uiVideoDataLength	= m_iNumTotalFrames * m_iWidth * m_iHeight * m_iNumComponents ;
	m_pxMainObject		= new CMainRiffObject ;

	CRiffList * pxHeaderList = new CRiffList (mmioFOURCC('h','d','r','l'));
	m_pxMainObject->AddObject (pxHeaderList);

	MainAVIHeader xMainHeader ;
	memset (&xMainHeader,0,sizeof (MainAVIHeader ));
	
	if (! pucAudioData)
	{
		xMainHeader.dwStreams = 1;
	}
	else 
	{
		xMainHeader.dwStreams = 2;
	}
	xMainHeader.dwSuggestedBufferSize	= 20000000;
	xMainHeader.dwWidth					= iVideoWidth;
	xMainHeader.dwHeight				= iVideoHeight ;
	xMainHeader.dwPaddingGranularity	= 0;
	xMainHeader.dwInitialFrames			= 0;
	xMainHeader.dwMicroSecPerFrame		= (1.0f / (float ) iFramesPerSecond ) * 1000 * 1000;
	xMainHeader.dwFlags					= AVIF_HASINDEX | AVIF_MUSTUSEINDEX | AVIF_TRUSTCKTYPE;
	xMainHeader.dwMaxBytesPerSec		= 10000000;
	xMainHeader.dwTotalFrames			= iNumFrames ;
	
	CRiffChunk * pxMainAviHeader = new CRiffChunk (mmioFOURCC('a','v','i','h'),sizeof (MainAVIHeader),&xMainHeader);
	
	pxHeaderList->AddObject (pxMainAviHeader);

	if(1)
	{
		CRiffList * pxVidStreamList = new CRiffList (mmioFOURCC('s','t','r','l'));
		pxHeaderList->AddObject (pxVidStreamList);

		AVIStreamHeader  xVidStreamHeader ;
		memset (&xVidStreamHeader,0,sizeof (AVIStreamHeader ));
	
		xVidStreamHeader.fccType = mmioFOURCC('v','i','d','s');
		if (!bCompressRLE )
		{
			xVidStreamHeader.fccHandler =  mmioFOURCC('D','I','B',' ');
		}
		else 
		{
			xVidStreamHeader.fccHandler =  mmioFOURCC('M','R','L','E');
		}
		xVidStreamHeader.dwScale				= uiScale;
		xVidStreamHeader.dwRate					= uiRate;
		xVidStreamHeader.dwLength				= uiLength;
		xVidStreamHeader.dwSuggestedBufferSize	= 10000000;
		xVidStreamHeader.dwQuality				= 100;
		xVidStreamHeader.dwSampleSize			= 0;
		xVidStreamHeader.wPriority				= -1;
		xVidStreamHeader.rcFrame.left			= 0;
		xVidStreamHeader.rcFrame.top			= m_iHeight;
		xVidStreamHeader.rcFrame.right			= m_iWidth;
		xVidStreamHeader.rcFrame.bottom			= 0;
		xVidStreamHeader.wLanguage				= -1;
		xVidStreamHeader.dwInitialFrames		= 0;
	
		CRiffChunk * pxVidStreamHeader = new CRiffChunk (mmioFOURCC('s','t','r','h'),
									sizeof (AVIStreamHeader),&xVidStreamHeader);

		pxVidStreamList->AddObject (pxVidStreamHeader);

		CRiffChunk * pxVidStreamFormat = 0;
		unsigned char  tmpBuffer [2048];
		memset (tmpBuffer,0,sizeof (tmpBuffer));
	
		myBITMAPINFOHEADER * pxBIheader = (myBITMAPINFOHEADER*) tmpBuffer;
		pxBIheader->biSize				= sizeof (myBITMAPINFOHEADER);
		pxBIheader->biPlanes			= 1 ;
		pxBIheader->biWidth				= m_iWidth;
		pxBIheader->biHeight			= m_iHeight;
		pxBIheader->biBitCount			= 8 * m_iNumComponents ;
		
		if (!bCompressRLE )
		{
			pxBIheader->biSizeImage   = m_iWidth * m_iHeight * m_iNumComponents;
			pxBIheader->biCompression = BI_RGB;
		}
		else 
		{
			pxBIheader->biSizeImage   = 0;
			pxBIheader->biCompression = BI_RLE8;
		}
		pxBIheader->biXPelsPerMeter = 128;
		pxBIheader->biYPelsPerMeter = 128;
		pxBIheader->biClrImportant  = 0;
		pxBIheader->biClrUsed       = 256;
	
		if (m_iNumComponents == 1)
		{
			for (int i=0;i<256;i++)
			{
				myRGBQUAD * pxRgb = &((myRGBQUAD*)(tmpBuffer + sizeof(myBITMAPINFOHEADER)))[i];
			
				pxRgb->rgbBlue = i;
				pxRgb->rgbRed = i;
				pxRgb->rgbGreen = i;
			}
			pxVidStreamFormat = new CRiffChunk (mmioFOURCC('s','t','r','f'),
											sizeof (myBITMAPINFOHEADER) + 4 * 256,
											tmpBuffer);
		}
		else 
		{
			pxVidStreamFormat = new CRiffChunk (mmioFOURCC('s','t','r','f')
									,sizeof (myBITMAPINFOHEADER),tmpBuffer);
		}
		pxVidStreamList->AddObject (pxVidStreamFormat);
	}
	
	if (pucAudioData)
	{
		CRiffList * pxAudioStreamList = new CRiffList (mmioFOURCC ('s','t','r','l'));
		pxHeaderList->AddObject (pxAudioStreamList );
	
		// Audio Stream Header
		AVIStreamHeader  xAudioStreamHeader;
		memset (&xAudioStreamHeader,0,sizeof (AVIStreamHeader));
	
		xAudioStreamHeader.fccType = mmioFOURCC ('a','u','d','s');
		xAudioStreamHeader.wPriority = -1;
		xAudioStreamHeader.dwInitialFrames = 1;
		xAudioStreamHeader.dwQuality = 1;
		xAudioStreamHeader.dwLength = uiLength;
		xAudioStreamHeader.dwScale = uiScale;
		xAudioStreamHeader.dwRate = uiRate;
		xAudioStreamHeader.dwSampleSize = 44100 * 2;

		CRiffChunk * pxAudioHeaderChunk = new CRiffChunk (mmioFOURCC ('s','t','r','h'),
											sizeof (AVIStreamHeader) , &xAudioStreamHeader);

		pxAudioStreamList->AddObject (pxAudioHeaderChunk );

		WAVEFORMATEX xWaveFormat ;
		memset (&xWaveFormat ,0,sizeof (WAVEFORMATEX));

		xWaveFormat.cbSize = 0;
		xWaveFormat.nChannels = 1;
		xWaveFormat.nSamplesPerSec = 44100;
		xWaveFormat.wBitsPerSample = 16;
		xWaveFormat.wFormatTag = WAVE_FORMAT_PCM;
		xWaveFormat.nAvgBytesPerSec = 44100 * 2;
	
		CRiffChunk * pxAudioStreamFormat = new CRiffChunk (mmioFOURCC ('s','t','r','f'),
											sizeof (WAVEFORMATEX),&xWaveFormat);

		pxAudioStreamList->AddObject (pxAudioStreamFormat);

	}

	/*
	char junk [2048];
	memset (junk,0,sizeof (junk));

	CRiffChunk * pxJunk = new CRiffChunk (mmioFOURCC ('J','U','N','K'),
							2048 - m_pxMainObject->GetLength () - 8,junk);

	m_pxMainObject->AddObject (pxJunk);
	*/
	
	// Video and Sound data list 
	CRiffList	*pxMoviList = new CRiffList (mmioFOURCC('m','o','v','i'));
	m_pxMainObject->AddObject (pxMoviList);

	// Video data 
	int i;

	// Index Chunk
	unsigned int uiNumIndices = iNumFrames;
	if (pucAudioData)
	{
		uiNumIndices++;
	}
	AVIINDEXENTRY * pxIndices = new AVIINDEXENTRY [uiNumIndices];


	if (!bCompressRLE )
	{
		for (i=0;i<iNumFrames;i++)
		{
			CRiffChunk * pxVidData = new CRiffChunk (
				mmioFOURCC('0','0','d','b'),
				m_iWidth * m_iHeight * m_iNumComponents ,
				pucVideoData + m_iWidth * m_iHeight * m_iNumComponents * i );
	
			pxMoviList->AddObject (pxVidData);

			AVIINDEXENTRY * pxCur = pxIndices+ i;

			pxCur->dwChunkOffset = 4 + (m_iWidth * m_iHeight * m_iNumComponents + 8) * i;
			pxCur->dwChunkLength = m_iWidth * m_iHeight * m_iNumComponents;
			pxCur->ckid = mmioFOURCC ('0','0','d','b');
			pxCur->dwFlags = AVIIF_KEYFRAME ;
		}
	}
	else 
	{
		unsigned char * pucRLEBuffer = new unsigned char [m_iWidth * m_iHeight *2 ]; // RLE can get bigger than uncompressed !
		for (i=0;i<iNumFrames;i++)
		{
			unsigned int uiLength =0;
			uiLength = CompressRLE8 (pucRLEBuffer,	
									pucVideoData + m_iWidth * m_iHeight * m_iNumComponents * i,
									m_iWidth * m_iHeight);

			
			CRiffChunk * pxVidData = new CRiffChunk (mmioFOURCC ('0','0','d','c'),uiLength,pucRLEBuffer );
			pxMoviList->AddObject (pxVidData);
			AVIINDEXENTRY * pxCur = pxIndices+ i;

			pxCur->dwChunkOffset	= pxMoviList->GetOffset (pxVidData);
			pxCur->dwChunkLength	= uiLength;
			pxCur->ckid				= mmioFOURCC ('0','0','d','c');
			pxCur->dwFlags			= AVIIF_KEYFRAME ;
		}
		delete [] pucRLEBuffer ;
	}

	// Audio data 

	if (pucAudioData)
	{
		CRiffChunk * pxAudioData = new CRiffChunk 
			(mmioFOURCC ('0','1','w','b' ) ,iNumFrames / iFramesPerSecond * 41000 * 2 ,
			pucAudioData);

		pxMoviList->AddObject (pxAudioData);
	
		AVIINDEXENTRY * pxCur = pxIndices+ iNumFrames;

		pxCur->dwChunkOffset	= pxMoviList->GetOffset (pxAudioData);;
		pxCur->dwChunkLength	= iNumFrames / iFramesPerSecond * 41000 * 2;
		pxCur->ckid				= mmioFOURCC ('0','1','w','b');
		pxCur->dwFlags			= 0;
	}

	CRiffChunk *pxIndexChunk = new CRiffChunk (mmioFOURCC('i','d','x','1'),
												uiNumIndices * sizeof (AVIINDEXENTRY),
												pxIndices);

	m_pxMainObject->AddObject (pxIndexChunk );

	if (!m_pxMainObject->Write (m_pxFile))
	{
		throw CAviException ("COULD NOT WRITE");
	}
}

