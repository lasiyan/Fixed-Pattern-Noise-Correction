#include "StdAfx.h"
#include "ActivProcess.h"

CActivProcess::~CActivProcess(void){}

BOOL CActivProcess::Execute(CMyImage *pFile)
{
	// 1. Load File
	if(!LoadFile(pFile))
	{
		AfxMessageBox(_T("Load File Error"));
		return FALSE;
	}

	// If Input Image is 24bit Ture Color RGB
	// Transfer to Grayscale 8bit image
	if(pFile->GetBitCount() == 24)
	{
		szGrayIamge = Make8BitGray(pFile);
	}
	else szGrayIamge = pFile->GetPixels2D();


	// 2. Start Sobel or Custom Detection
	if(nCmboxCurSel == 0)	// Sobel
	{
		pResult = sobel.DoDetection(pFile, szGrayIamge);
	}
	else if(nCmboxCurSel == 1)	// Custom
	{
		pResult = custom.DoDetection(pFile, szGrayIamge);
	}
	else
	{
		AfxMessageBox(_T("else"));
		exit(0);
	}

	// return gray image
	if(pFile->GetBitCount() == 24)
	{
		delete[] szGrayIamge[0];
		delete[] szGrayIamge;
	}
	delete pFile;

	
	// 3. Save File
	if(!SaveFile(pResult))
	{
		AfxMessageBox(_T("Save File Error"));
		return FALSE;
	}
	
	delete(pResult);
	return TRUE;
}

BOOL CActivProcess::LoadFile(CMyImage *pFile)
{
	FILE* fp;

	CT2A ascii(pFile->GetFileName(), CP_UTF8);	// CString to const char*
	if((fopen_s(&fp, ascii.m_psz, "rb")) != 0)
	{
		AfxMessageBox(_T("fopen_s() Error"));
		return FALSE;
	}

	if(pFile->GetBitCount() == 8)
	{
		fseek(fp, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256, SEEK_SET);
	}
	if(pFile->GetBitCount() > 8)
	{
		fseek(fp, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER), SEEK_SET);
	}

	fread(pFile->GetPixels(), (pFile->GetBitCount() / 8), pFile->GetImageSize(), fp);
	fclose(fp);

	return TRUE;
}

BOOL CActivProcess::SaveFile(CMyImage *pResult)
{
	FILE* fp2;

	CString strNewFileName = MakeFileName(pResult->GetFileName());
	CT2A ascii(strNewFileName, CP_UTF8);	// CString to const char*
	if((fopen_s(&fp2, ascii.m_psz, "wb")) != 0)
	{
		AfxMessageBox(_T("fopen_s() Error"));
		return FALSE;
	}

	pResult->MakeBitmap();

	// Write Bitmap Headers
	fwrite(&pResult->bfh, sizeof(BITMAPFILEHEADER), 1, fp2);	
	fwrite(&pResult->bih, sizeof(BITMAPINFOHEADER), 1, fp2);
	fwrite(&pResult->rgb, sizeof(RGBQUAD), 256, fp2);

	fwrite(pResult->GetPixels(), 1, pResult->GetImageSize(), fp2);
	fclose(fp2);

	return TRUE;
}

CString CActivProcess::MakeFileName(CString _strFileName)
{
	int nPos;
	CString originFileName = _strFileName;
	CString strNewPath;
	nPos = originFileName.ReverseFind('.');

	strNewPath = originFileName.Left(nPos) + _T("_result.bmp");

	return strNewPath;
}


BYTE** CActivProcess::Make8BitGray(CMyImage* pFile)
{
	szGrayIamge = new BYTE*[pFile->GetHeight()];
	szGrayIamge[0] = new BYTE[pFile->GetImageSize()];
	for (int i = 1; i < pFile->GetHeight(); i++)
	{
		szGrayIamge[i] = szGrayIamge[i - 1] + pFile->GetWidth();
	}
	memset(szGrayIamge[0], 0, pFile->GetImageSize()); // Init Pixels

	szGrayIamge[0] = pFile->RGBto8BitGray(szGrayIamge[0], pFile->GetPixels());		

	return szGrayIamge;
}
