#pragma once
#include "MyImage.h"
#include "SobelEdgeDetect.h"
#include "CustomDetection.h"

class CActivProcess
{
private:
	int nCmboxCurSel;

	CSobelEdgeDetect sobel;

	CCustomDetection custom;

	BOOL LoadFile(CMyImage*);
	BOOL SaveFile(CMyImage*);
	CString MakeFileName(CString);

	BYTE** szGrayIamge;
	BYTE** Make8BitGray(CMyImage*);
	CMyImage* pResult;

public:
	CActivProcess(int _cb)
	{
		nCmboxCurSel = _cb;
	}
	~CActivProcess(void);

	BOOL Execute(CMyImage*);
};

