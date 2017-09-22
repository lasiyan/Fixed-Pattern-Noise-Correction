#pragma once

class CFiles
{
public:
	CFiles(CString, int, int, int, int,  int);	// input File (Raw file)
	CFiles();	// Default
	~CFiles(void);

private:
	// input
	CString strFileName;
	int nWidth;
	int nWidthByte;
	int nHeight;
	int nImageSize;	
	int nFileSize;
	// File options
	int nPixelBit;

	// File Data
	BYTE* szHeaders;		// to open Raw file
	BYTE* szPixelData;	// After Interpolation
	BYTE* szResultData;		// Result File(BMP)

	BYTE* sz8BitGray;
public:
	CString getFileName();
	void setFileName(CString);

	int getWidth();
	void setWidth(int);

	int getWidthByte();
	void setWidthByte(int);

	int getHeight();
	void setHeight(int);

	int getImageSize();
	void setImageSize(int);

	int getFileSize();
	void setFileSize(int);

	int getPixelBit();
	void setPixelBit(int);

	BYTE* getHeaders();
	void setHeaders(BYTE*);

	BYTE* getPixelData();
	void setPixelData(BYTE*);

	BYTE* getResultData();
	void setResultData(BYTE*);


	BYTE* Trans24bitTo8BitGray(BYTE*);
	BYTE* CFiles::get8bitData();
};
