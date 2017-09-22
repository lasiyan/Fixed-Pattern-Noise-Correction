#include "StdAfx.h"
#include "Files.h"

CFiles::~CFiles(void){}
CFiles::CFiles(){}

// Input Data 
CFiles::CFiles(CString _fileName, int _width, int _height, int _imageSize, int _fileSize,  int _pixelBit)
{
	strFileName = _fileName;
	nWidth = _width;
	nHeight = _height;
	nImageSize = _imageSize;
	nFileSize = _fileSize;
	nPixelBit = _pixelBit;

	if(nPixelBit == 8) 
	{
		szHeaders = new BYTE[ 14 + 40 + sizeof(RGBQUAD) ];	// Need to File Open
		ZeroMemory(szHeaders, 14 + 40 + sizeof(RGBQUAD));
	}
	else
	{
		szHeaders = new BYTE[ 14 + 40 ];	// Need to File Open
		ZeroMemory(szHeaders, 14 + 40);
	}
	
	szPixelData = new BYTE[ nFileSize ];
	ZeroMemory(szPixelData, nFileSize);

	szResultData = new BYTE[ nImageSize ];
	ZeroMemory(szResultData, nImageSize);

	nWidthByte = (nPixelBit / 8) * nWidth;
}

BYTE* CFiles::Trans24bitTo8BitGray(BYTE* szElseData)
{
	int BCPP = nWidthByte / nWidth;	// Byte Count per Pixel
	int gray;

	sz8BitGray = new BYTE[ nImageSize ];
	ZeroMemory(sz8BitGray, nImageSize);

	for(int j = 0; j < nHeight; j++)
	{
		for(int i = 0; i < nWidthByte; i += 3)
		{
			gray = (szElseData[j * nWidthByte + i] * 0.0722)
				 + (szElseData[j * nWidthByte + i+1] * 0.7152)
				 + (szElseData[j * nWidthByte + i+2] * 0.2126);	// B G R
			sz8BitGray[ j * nWidth + (i / 3) ] = gray;
		}
	}
	
	return sz8BitGray;
}
BYTE* CFiles::get8bitData()
{
	return sz8BitGray;
}


CString CFiles::getFileName()
{
	return strFileName;
}
void CFiles::setFileName(CString _fileName)
{
	strFileName = _fileName;
}

int CFiles::getWidth()
{
	return nWidth;
}
void CFiles::setWidth(int _width)
{
	nWidth = _width;
}

int CFiles::getWidthByte()
{
	return nWidthByte;
}
void CFiles::setWidthByte(int _widthbyte)
{
	nWidthByte = _widthbyte;
}

int CFiles::getHeight()
{
	return nHeight;
}
void CFiles::setHeight(int _height)
{
	nHeight = _height;
}

int CFiles::getImageSize()
{
	return nImageSize;
}
void CFiles::setImageSize(int _imageSize)
{
	nImageSize = _imageSize;
}

int CFiles::getFileSize()
{
	return nFileSize;
}
void CFiles::setFileSize(int _fileSize)
{
	nFileSize = _fileSize;
}

int CFiles::getPixelBit()
{
	return nPixelBit;
}
void CFiles::setPixelBit(int _pixelBit)
{
	nPixelBit = _pixelBit;
}

BYTE* CFiles::getHeaders()
{
	return szHeaders;
}
void CFiles::setHeaders(BYTE* _fileData)
{
	szHeaders = _fileData;
}

BYTE* CFiles::getPixelData()
{
	return szPixelData;
}
void CFiles::setPixelData(BYTE* _fileData)
{
	szPixelData = _fileData;
}

BYTE* CFiles::getResultData()
{
	return szResultData;
}
void CFiles::setResultData(BYTE* _fileData)
{
	szResultData = _fileData;
}
